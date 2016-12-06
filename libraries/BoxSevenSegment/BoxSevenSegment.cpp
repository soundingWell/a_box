#include "BoxSevenSegment.h"

// Set the displays brightness. Should receive byte with the value
// to set the brightness to
// 0--------127--------255
void BoxSevenSegment::setBrightness(byte value) {
  s7s_->write(0x7A);  // Set brightness command byte
  s7s_->write(value);  // brightness data byte
}

void BoxSevenSegment::clearDisplay() {
	s7s_->write(0x76);  // Clear display command
}

void BoxSevenSegment::setColon() {
	s7s_->write(0x77);
	s7s_->write(0b00010000);
}

// Write the time to the display. 
// Format is hh : mm
void BoxSevenSegment::writeTime(const int seconds, const int minutes, const int hours) {
	setColon();
	if (hours > 0) {
		sprintf(temp_string_, "%02d%02d", hours, minutes);
	} else {
		sprintf(temp_string_, "%02d%02d", minutes, seconds);
	}
  
  s7s_->print(temp_string_);
}