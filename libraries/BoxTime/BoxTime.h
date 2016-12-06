#ifndef BoxTime_h
#define BoxTime_h

#include "Arduino.h"

class BoxTime {
 public:
  BoxTime(int millis, int seconds, int minutes, int hours) {
  	millis_ = millis;
  	seconds_ = seconds;
  	minutes_ = minutes;
  	hours_ = hours;
  }

  BoxTime() {
  	millis_ = 0;
  	seconds_ = 0;
  	minutes_ = 0;
  	hours_ = 0;
  }

  void changeTime(int seconds=0, int minutes=0, int hours=0);

  // Return true is we're out of time.
  bool isTimeUp();
  
  // millis_ actually counts up, not down.
  uint64_t millis_;
  int seconds_;
  int minutes_;
  int hours_;
};

#endif
