# a_coos
Very simple COoperative Operating System for Arduino.

Kernel uses about 1K bytes. Highly portable, it has no assembler code and it is independent from hardware. System ticks 1 ms based on millis(). Should run on any Arduino board. Tested on Arduino Pro Mini (ATmega328), RAK Creator Pro (RTL8711) and NodeMCU (ESP8266).

Warnings: 
  * COOS_DELAY(x) must be used in the task itself; it cannot be used in functions called from task
  * Variables used by a task should be declared as static, otherwise their value will be lost after COOS_DELAY() call

