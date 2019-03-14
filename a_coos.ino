/*
 * Sketch    a_coos.ino - simple demo for cooperative OS named COOS
 * Author    A.Kouznetsov
 * Rev       1.3 dated 14/03/2019

Redistribution and use in source and binary forms, with or without modification, 
are permitted.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR 
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "coos.h"

//##############################################################################
// Def
//##############################################################################

#ifndef BUILTIN_LED
  #define BUILTIN_LED 13
#endif  

//##############################################################################
// Var
//##############################################################################

static int led = BUILTIN_LED;

Coos <4> coos;       // create operating system with up to 4 tasks  

//##############################################################################
// Func
//##############################################################################

// ========================================
// Task 0 toggles led every 0.5 sec
// ========================================
void coos_task0(void)
{
  static uchar cnt;
  while(1)
  {
    Serial.print(".");
    digitalWrite(led, LOW); 
    COOS_DELAY(500);          // 500 ms
    digitalWrite(led, HIGH); 
    COOS_DELAY(500);          // 500 ms
    if (++cnt >= 60)          // every minute
    {
      cnt = 0;
      Serial.print(" uptime = ");
      Serial.print(coos.uptime);
      Serial.println(" sec ");
    }
  }
}
// ========================================
// Task 1 sets led OFF every 0.65 sec
// ========================================
void coos_task1(void)
{
  COOS_DELAY(100);    
  while(1)
  {
    COOS_DELAY(650);        // 650 ms
    digitalWrite(led, LOW); 
  }
}
// ========================================
// Setup
// ========================================
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("== COOS demo ==");
  pinMode(led, OUTPUT);
  coos.register_task(coos_task0);    
  coos.register_task(coos_task1);
  coos.start();                     // init registered tasks
}

// ========================================
// Main loop 
// ========================================
void loop()
{  
  coos.run();  // Coos scheduler 
}
/* EOF */
