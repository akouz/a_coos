# a_coos
#### rev 1.6 

Very simple COoperative Operating System for Arduino based on the standard __setjmp__ library.

Kernel uses about 1K bytes. Highly portable, it has no assembler code and it is independent from hardware. System ticks 1 ms based on __millis()__. Should run on any Arduino board. Tested with the following boards:
  * Arfuino Uno, Arduino Pro Mini and Seeeduino (ATmega328P) 
  * Arduino Leonardo (ATmega32U4)
  * Arduino MKR1000 (SAMD21)
  * XMC1100 Boot Kit and XMC 2Go (XMC1100) 
  * RAK Creator Pro (RTL8711) 
  * NodeMCU and Wemos Lolin (ESP8266) 
  * Coos does not work with ESP32 because of [problems in the ESP32 __setjmp__ library.](https://github.com/espressif/arduino-esp32/issues/1689)

Coos made as C++ template. Library consists of a single file coos.h. 

## Warnings: 
  * __COOS_DELAY(x)__ must be used in the task itself; it cannot be used in functions called from task.
  * Variables used by a task should be declared as static, otherwise their value will be lost after __COOS_DELAY(x)__ call.
  * For ATmega microcontrollers, tick can be selected either 1 ms in average, or 1.024 ms. Uptime, daysec, hour and minute calculated correctly disregard of tick selected. Other microcontrollers always have an accurate tick of 1 ms.
  * Actual number of tasks should be less or equal to the declared.

## Usage

Place __coos.h__ file into the same folder where the sketch is. In the sketch include __coos.h__ as:
```C
#include "coos.h"
```
Alternatively, it can be used as an Arduino library. Once installed, there is no need to copy __coos.h__ file into every project any more. To install it as library, locate your Arduino libraries folder. Typically it is: 
```
C:\Users\user\Documents\Arduino\libraries\
```
Add folder coos: 
```
C:\Users\user\Documents\Arduino\libraries\coos\
```
Copy files __coos.h__, __library.properties__, __keywords.txt__ and folder __examples__ there. In your sketch include coos library as:
```C
#include <coos.h>
```
Required number of coos tasks and coos tick should be declared in your sketch as follows:
```C
Coos <6, 0> coos; // number 6 in the angle brackets specifies number of user tasks; 0 selects 1 ms tick
```
Instance name __coos__ must be used, othervise macro __COOS_DELAY(x)__ cannot operate correctly.


### When 1 ms tick selected
```C
Coos <6, 0> coos; 
```

60,000 ticks  in 60 sec:
```
== COOS demo ==
tick 1 ms average
............................................................ uptime = 60 sec 
............................................................ uptime = 120 sec 
............................................................ uptime = 180 sec 
............................................................ uptime = 240 sec 
............................................................ uptime = 300 sec 
```

### When 1.024 ms tick selected
```C
Coos <6, 1> coos; 
```
60,000 ticks  in aprrox 61 sec:
```
== COOS demo ==
tick 1.024 ms
............................................................ uptime = 61 sec 
............................................................ uptime = 122 sec 
............................................................ uptime = 184 sec 
............................................................ uptime = 245 sec 
............................................................ uptime = 307 sec 
```
