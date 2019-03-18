/*
 * Sketch    a_coos.ino - simple demo for cooperative OS named COOS
 * Author    A.Kouznetsov
 * Rev       1.4 dated 17/03/2019

Redistribution and use in source and binary forms, with or without modification, 
are permitted.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE 
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT 
OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "coos.h"

//##############################################################################
// Def
//##############################################################################

enum{
    TICK_1000US   = 0,    // 1 ms in average because of corrections made in millis(),  
                          // see https://www.best-microcontroller-projects.com/arduino-millis.html
    TICK_1024US   = 1     // 1.024 ms
};
#define TICK   TICK_1000US  // select tick

#ifndef BUILTIN_LED
  #define BUILTIN_LED 13
#endif  

//##############################################################################
// Var
//##############################################################################

static int led = BUILTIN_LED;

Coos <4, TICK> coos;    // create coos with up to 4 tasks, tick as selected;
                        // do not create coos with less than 3 tasks             

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
    if (++cnt >= 60)          // every minute if TICK_1000US selected
                              // or approx every 61 sec if TICK_1024US selected   
    {
      cnt = 0;
      Serial.print(" uptime = ");   // coos.uptime counts seconds correctly
      Serial.print(coos.uptime);    // disregard of tick selected
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
  Serial.print("tick ");
  if (TICK == TICK_1000US)
  {
    Serial.println("1 ms average");
  } 
  else
  {
    Serial.println("1.024 ms");
  } 
  pinMode(led, OUTPUT);
  coos.register_task(coos_task0);   // register task 0   
  coos.register_task(coos_task1);   // register task 1
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
