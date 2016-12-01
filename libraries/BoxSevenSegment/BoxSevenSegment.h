#ifndef BoxSevenSegment_h 
#define BoxSevenSegment_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class BoxSevenSegment {
 public:
 	BoxSevenSegment(SoftwareSerial * s7s) {
 		s7s_ = s7s;
 		s7s_->begin(9600);
 		setBrightness(0xF0);
 		clearDisplay();
 	}
	void setBrightness(byte value);
	void clearDisplay();
	void writeTime(int minutes, int hours);

 private:
	SoftwareSerial * s7s_;
	char temp_string_[100];
};

#endif