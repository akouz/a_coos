# a_coos
Very simple COoperative Operating System for Arduino.

Kernel uses about 1K bytes. Highly portable, it has no assembler code and it is independent from hardware. System ticks 1 ms based on millis(). Should run on any Arduino board. Tested on Arduino Pro Mini (ATmega328), RAK Creator Pro (RTL8711) and NodeMCU (ESP8266). Does not work on ESP32 because of problems in setjmp/longjmp libraries in the current ESP32 implementation.

Revision 1.3 made as C++ template. Library consists of a single file coos.h. 

## Warnings: 
  * COOS_DELAY(x) must be used in the task itself; it cannot be used in functions called from task
  * Variables used by a task should be declared as static, otherwise their value will be lost after COOS_DELAY() call

## Usage

Place coos.h file into the same folder where the sketch is. In the sketch include coos.h as:
```C
#include "coos.h"
```
Alternatively, it can be used as an Arduino library. Once installed, there is no need to copy coos.h file into every project any more. To install it as library, locate your Arduino installation folder and find libraries folder. Typically it is: 
```
C:\Program Files (x86)\Arduino\libraries
```
Add folder coos: 
```
C:\Program Files (x86)\Arduino\libraries\coos
```
Copy files coos.h and library.properties there.

In the sketch include coos library as:
```C
#include <coos.h>
```
In rev 1.3 number of tasks declared as follows:
```C
Coos <6> coos; // number 6 in the angle brackets specifies number of user tasks
```

