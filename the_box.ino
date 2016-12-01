
#include <Servo.h>
#include <SoftwareSerial.h>

// ------ GLOBAL VARIABLES -----
long millis_;
int seconds_ = 0;
int hours_ = 0;
int minutes_ = 1;
char temp_string_[100]; //Used for sprintf

// 3 possible states: "counting", "waiting", "serving".
String state_;

// Servo angles.
const int fill_angle_ = 155;
const int empty_angle_ = 20;
// ------------------------------

// ------- PINS ----------
const int led_PIN = 3;
const int button_PIN = 4;
const int time_up_btn_PIN = 5;
const int time_down_btn_PIN = 6;
const int softwareTx_PIN = 8;
const int softwareRx_PIN = 7;
const int servo_PIN = 9;
// ---------------------

// ------- OBJECTS ------
SoftwareSerial s7s(softwareRx_PIN, softwareTx_PIN);
Servo servo;
// ----------------------

void setup() {
// -------- GLOBAL --------
state_ = "counting";

// ------- 7 SEGEMENT -----
  //  The default of the s7s is 9600.
  s7s.begin(9600);
  
  setBrightness(0xF0);
  clearDisplay();  // Clears display, resets cursor
  
  millis_ = millis();
// ------------------------

// --- Big Button ---
  pinMode(led_PIN, OUTPUT);
  pinMode(led_PIN, LOW);

  pinMode(button_PIN, INPUT);
  pinMode(button_PIN, HIGH);
// ------------------------

// --- Time Buttons ----
  pinMode(time_up_btn_PIN, INPUT); 
  pinMode(time_up_btn_PIN, HIGH); 

  pinMode(time_down_btn_PIN, INPUT); 
  pinMode(time_down_btn_PIN, HIGH); 
// -----------------------

//  --- Servo ------
  servo.attach(servo_PIN);
  servo.write(fill_angle);
// ----------------
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//   0--------127--------255
void setBrightness(byte value)
{
  s7s.write(0x7A);  // Set brightness command byte
  s7s.write(value);  // brightness data byte
}

void clearDisplay()
{
  s7s.write(0x76);  // Clear display command
}

// Parameters are the time change.
void updateTime(byte seconds=0, byte minutes=0, byte hours=0) {
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
    state_="waiting";
  }
}

// Write the time to the display. 
// Format is hh : mm
void writeTime() {
  sprintf(temp_string_, "02d%02d", hours_, minutes_);
  s7s.print(temp_string_);
}

// Loop waiting for button press.
void waitForPress() {
  // Turn on the LED.
  digitalWrite(led_PIN, HIGH);
  while (true) {
    bool did_press = digitalRead(button_PIN);

    if (did_press == 1) {   // Button has been pressed, serve.
      digitalWrite(led_PIN, LOW);
      state_ = "serving";
      break;
    }
  }
}

// Check if either time change button has been pressed. 
// If yes, update time information.
void checkForTimeChangeInput() {
  bool did_press_time_up = digitalRead(time_up_btn_PIN);
  if (did_press_time_up) {
    updateTime(0, 5, 0);
  }

  bool did_press_time_down = digitalRead(time_down_btn_PIN);
  if (did_press_time_down) {
    updateTime(0, -5, 0);
  }
}

void dispenseFood() {
  servo.write(empty_angle);

  delay(1000);

  servo.write(fill_angle);
  
}

void loop() {
  if (state_ == "counting") {
    checkForTimeChangeInput();
    if (millis() > (millis_ + 1000)) {  // A second has passed.
      updateTime(-1, 0, 0);
      writeTime();
      millis_ += 1000;
    }
    delay(100);
  } else if (state_ == "waiting") {
    // If loop gets called automatically, this will be bad times.
    waitForPress();
    
  } else if (state_ == "serving") {
    // Turn the servo back and forth.
    dispenseFood();
  }
}
