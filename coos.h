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
 
#ifndef __COOS_H
#define __COOS_H

//###########################################################
// Inc
//###########################################################

#include <Arduino.h>
#include <setjmp.h>

//###########################################################
// Type                                                   
//###########################################################

#ifndef __UCHAR_DEFINED__
  #define __UCHAR_DEFINED__
  typedef unsigned char uchar;
  typedef signed   char schar;
  typedef unsigned int  uint;
  typedef unsigned long ulong;
  typedef signed   long slong;
#endif

//###########################################################
// Def                                              
//###########################################################

#define COOS_MAX_TASKS       8     // max number of tasks, set as many as required (up to 255)
#define COOS_STOP            -2    // set this value to stop task
#define COOS_DELAY(__delay)  if (!setjmp(coos.task_context[coos.task_no])) {longjmp(coos.main_context, __delay+1);} else

//###########################################################
// Class                                              
//###########################################################

class Coos{
  public:
                Coos(void);                           // constructor
    void        register_task(void (*tsk)(void));     // user tasks must be registered first
    void        run_scheduler(void);                  // COOS task switcher
    jmp_buf     main_context;                         // context of scheduler
    jmp_buf     task_context[COOS_MAX_TASKS];         // list of task contexts
    uchar       task_no;                              // current task No
    int         task_delay[COOS_MAX_TASKS];           // task delay in msec, task stopped if value is negative
    uint        msec;                                 // ms of current sec
    ulong       uptime;                               // sec since start
  private:
    void        (*tsk_p[COOS_MAX_TASKS])(void);       // list of registered tasks
    void        update_time(void);
    uchar       ms;
    uchar       task_cnt;                             // counts registered coos tasks
};
extern Coos coos;

#endif /* __COOS_H */
