#ifndef BoxTime_h
#define BoxTime_h

#include "Arduino.h"

class BoxTime {
 public:
  BoxTime() {
  	millis_ = 0;
  	seconds_ = 0;
  	minutes_ = 0;
  	hours_ = 0;
  }

  // Returns 'waiting' unless timer has run out. then returns 'serving'.
  String changeTime(int seconds=0, int minutes=0, int hours=0);
  
  long millis_;
  int seconds_;
  int minutes_;
  int hours_;
};

#endif
