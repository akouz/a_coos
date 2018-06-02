/*
* Library   COOS - COoperative Operating System
* Author    A.Kouznetsov
* Rev       1.1 dated 02/06/2018
* Target    Arduino

Redistribution and use in source and binary forms, with or without modification, are permitted.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//##########################################################
// Inc
//##########################################################

#include  "coos.h"

//##########################################################
// Var  
//##########################################################

Coos coos;

//##########################################################
// Func
//##########################################################

// =================================
// Constructor
// =================================
Coos::Coos(void)
{
  uint i;
  uptime = 0;
  msec = 0;
  ms = 0;
  task_cnt = 0;
  for (i=0; i<COOS_MAX_TASKS; i++)
  {
    tsk_p[i] = NULL;                   // task is not registered
    task_delay[i] = COOS_STOP;         // all unregistered tasks stopped
  }
}
// =================================
// Register a task 
// =================================
void Coos::register_task(void (*tsk)(void))
{
  if (task_cnt < COOS_MAX_TASKS)
  {
    tsk_p[task_cnt++] = tsk;
  }
}
// =================================
// Update time
// =================================
// supposed to happen more often than every millisecond,
// but can be late if a task takes long time to execute
void Coos::update_time(void)
{
  while (ms != (uchar)millis()) // catch up time if late
  {      
    ms++;  
    for (int i=0; i<task_cnt; i++)
    {
      if (task_delay[i] > 0)  // positive delays 
      {
        task_delay[i]--;
      }
    }
    if (++msec >= 1000) // if 1 sec passed
    {
      uptime++;         // count seconds since start
      msec = 0;
    }
  }  
}
// =================================
// Scheduler
// =================================
void Coos::run_scheduler(void)
{
  int   res;
  void (*tsk)(void);
  update_time(); 
  // --------------------------
  // Init tasks               
  // --------------------------
  for (task_no=0; task_no<task_cnt; task_no++)
  {
    if (tsk_p[task_no] != NULL)            // if task was registered
    {
      res = setjmp(main_context);
      if (res == 0)
      {
        tsk = tsk_p[task_no];
        tsk();                             // invoke task
      }
      else
      {
        task_delay[task_no] = --res;      // task returns the required delay
      }
    }  
    update_time(); 
  }
  // --------------------------
  // Scheduler loop          
  // --------------------------
  task_no = 0;
  while(1) 
  {
    if (task_delay[task_no] == 0)
    {
      res = setjmp(main_context);           // set return point and get delay value from the task 
      if (res == 0)                         // after setting return point
      {
        longjmp(task_context[task_no], 1);  // invoke task 
      }
      else                                  // after returning from task 
      {
        task_delay[task_no] = --res;        // set task delay (negative delay - task stopped) 
      }
      update_time(); 
    }
    task_cnt = (task_cnt > COOS_MAX_TASKS)? COOS_MAX_TASKS : task_cnt;
    if (++task_no > task_cnt)               // next task
    {
      task_no = 0;                          // round-robin
    }
    update_time(); 
  }
}
/* EOF */
