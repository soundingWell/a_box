#include "BoxTime.h"

String BoxTime::changeTime(int seconds=0, int minutes=0, int hours=0) {
  seconds_ += seconds;
  minutes_ += minutes;
  hours_ += hours;

  if (seconds_ < 0) {
    seconds_ = 59;
    minutes_ -= 1;
  } else if (seconds_ > 59) {
    minutes += 1;
    seconds_ == 0;
  }

  if (minutes_ < 0) {
    minutes_ = 59;
    hours_ -= 1;
  } else if (minutes > 59) {
    minutes_ = 0;
    hours_ += 1;
  }

  // Timer has run out.
  if (hours_ < 0) {
    return "serving";
  }

  return "waiting";
}