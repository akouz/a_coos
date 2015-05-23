/*
* Sketch    coos_test.ino
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
#include "coos.h"

int led = 13;

// -------------------------------------------------------
// Task 0 blinks led, 0.5 sec ON - 1.5 sec OFF
// -------------------------------------------------------
void coos_task0(void)
{
  while(1)
  {
    digitalWrite(led, HIGH); 
    COOS_DELAY(500);          // 500 ms = 0.5 sec
    digitalWrite(led, LOW); 
    COOS_DELAY(1500);
  }
}
// -------------------------------------------------------
// Task 1 sets led ON every 1.733 sec
// -------------------------------------------------------
void coos_task1(void)
{
  COOS_DELAY(500);    
  while(1)
  {
    digitalWrite(led, HIGH); 
    COOS_DELAY(1733);    
  }
}
// -------------------------------------------------------
// Setup
// -------------------------------------------------------
void setup()
{
  pinMode(led, OUTPUT);
  coos.register_task(coos_task0);
  coos.register_task(coos_task1);
}

// -------------------------------------------------------
// Main loop 
// -------------------------------------------------------
void loop()
{
  coos.run_scheduler();  // Coos scheduler is an endless loop itself
}
/* EOF */
