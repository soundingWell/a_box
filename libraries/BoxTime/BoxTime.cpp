#include "BoxTime.h"

bool BoxTime::isTimeUp() {
	if (seconds_ <= 0 && minutes_ <= 0 && hours_ <= 0) {
		return true;
	}

	return false;
}

// TODO: Make this return if something has gone wrong. 
void BoxTime::changeTime(int seconds=0, int minutes=0, int hours=0) {
  seconds_ += seconds;
  minutes_ += minutes;
  hours_ += hours;

  if (seconds_ < 0 && (hours_ > 0 || minutes_ > 0)) {
    seconds_ = 59;
    minutes_ -= 1;
  } else if (seconds_ > 59) {
    minutes += 1;
    seconds_ == 0;
  }

  if (minutes_ < 0 && hours_ > 0) {
    minutes_ = 59;
    hours_ -= 1;
  } else if (minutes > 59) {
    minutes_ = 0;
    hours_ += 1;
  }

  // No reason for negative numbers. 
  hours_ = max(hours_, 0);
  minutes_ = max(minutes_, 0);
  seconds_ = max(seconds_, 0);
}