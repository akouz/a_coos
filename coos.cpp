/*
* Library   COOS - COoperative Operating System
* Author    A.Kouznetsov
* Rev       1.0 dated 23/5/2015
* Target    Arduino

Redistribution and use in source and binary forms, with or without modification, are permitted.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include  "coos.h"

//##########################################################
// var  
//##########################################################
uint task_cnt;    // counts registered coos tasks

Coos coos;

//##########################################################
// func
//##########################################################
// -------------------------------------------------------
// Constructor
// -------------------------------------------------------
Coos::Coos(void)
{
  uint i;
  task_cnt = 0;
  for (i=0; i<COOS_MAX_TASKS; i++)
  {
    tsk_p[i] = 0;                      // task is not registered
    task_delay[i] = COOS_STOP;         // all unregistered tasks stopped
  }
  //set timer0 compare interrupt (cannot use overflow interrupt because it is already used by Arduino)
  TCCR0A = 0;  
  TCCR0B = 0;  
  TCNT0  = 0;  
  OCR0A = 0x80;                // does not matter, somwhere in the middle
  TIMSK0 |= (1 << OCIE0A);     // enable timer compare interrupt
}
// -------------------------------------------------------
// Register a task 
// -------------------------------------------------------
void Coos::register_task(void (*tsk)(void))
{
  if (task_cnt < COOS_MAX_TASKS)
  {
    tsk_p[task_cnt++] = tsk;
  }
}
// -------------------------------------------------------
// Scheduler invokes user tasks 
// -------------------------------------------------------
void Coos::run_scheduler(void)
{
  int   res;
  void (*tsk)(void);
  // --------------------------
  // Init tasks               
  // --------------------------
  for (task_no=0; task_no<COOS_MAX_TASKS; task_no++)
  {
    if (tsk_p[task_no] != 0)                // if task was registered
    {
      res = setjmp(main_context);
      if (res == 0)
      {
        tsk = tsk_p[task_no];
        tsk();                             // invoke task
      }
      else
        task_delay[task_no] = --res;      // task returns required delay
    }  
  }
  // --------------------------
  // Scheduler loop          
  // --------------------------
  task_no = 0;
  while(1)
  {
    if (task_delay[task_no] == 0)           // if task is active
    {
      res = setjmp(main_context);           // set return point and get delay value from the task 
      if (res == 0)                         // after setting return point
        longjmp(task_context[task_no], 1);  // invoke task 
      else                                  // after returning from task 
        task_delay[task_no] = --res;        // set task delay (negative delay - task stopped) 
    }
    if (++task_no >= COOS_MAX_TASKS)
    {
      task_no = 0;
    }
  }
}
// -------------------------------------------------------
// Timer0 compare ISR, 1 ms
// -------------------------------------------------------
ISR(TIMER0_COMPA_vect)
{
  uint i;
  for (i=0; i<COOS_MAX_TASKS; i++)
  {
    if (coos.task_delay[i] > 0)
    {
      coos.task_delay[i]--;
    }
  }
}

/* EOF */
