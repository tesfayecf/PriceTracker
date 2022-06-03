#ifndef Request 
#define Request

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

String getTimestamp();

#endif
