## rev 1.3

This revision always uses ticks of 1 ms in average

## Usage

Place __coos.h__ file into the same folder where the sketch is. In the sketch include __coos.h__ as:
```C
#include "coos.h"
```
Alternatively, it can be used as an Arduino library. Once installed, there is no need to copy __coos.h__ file into every project any more. To install it as library, locate your Arduino installation folder and find libraries folder. Typically it is: 
```
C:\Program Files (x86)\Arduino\libraries
```
Add folder coos: 
```
C:\Program Files (x86)\Arduino\libraries\coos
```
Copy files __coos.h__ and __library.properties__ there. In your sketch include coos library as:
```C
#include <coos.h>
```
Required number of coos tasks declared in your sketch as follows:
```C
Coos <6> coos; // number 6 in the angle brackets specifies number of user tasks
```
