#ifndef BoxSevenSegment_h 
#define BoxSevenSegment_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class BoxSevenSegment {
 public:
 	BoxSevenSegment(SoftwareSerial * s7s) {
 		s7s_ = s7s;
 		s7s_->begin(9600);
 		setBrightness(100);
 		clearDisplay();
 		setColon();
 	}
	void setBrightness(byte value);
	void clearDisplay();
	void setColon();
	void writeTime(const int seconds, const int minutes, const int hours);

 private:
	SoftwareSerial * s7s_;
	char temp_string_[100];
};

#endif