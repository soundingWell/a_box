#include <BoxSevenSegment.h>
#include <BoxTime.h>
#include <Servo.h>
#include <SoftwareSerial.h>

// ------ GLOBAL VARIABLES -----
char temp_string_[100]; //Used for sprintf

// 3 possible states: "counting", "waiting", "serving".
String state_;

// Servo angles.
const int fill_angle_ = 155;
const int empty_angle_ = 20;

uint32_t next;
// ------------------------

// ------- PINS ----------
const int big_btn_led_PIN = 3;
const int big_btn_PIN = 4;
const int time_up_btn_PIN = 5;
const int time_down_btn_PIN = 6;
const int softwareTx_PIN = 7;
const int softwareRx_PIN = 8;
const int servo_PIN = 9;
const int built_in_led_PIN = 13;
// ---------------------

// ------- OBJECTS ------
Servo servo;
BoxTime box_time;
SoftwareSerial s7s(softwareTx_PIN, softwareRx_PIN);
BoxSevenSegment b7s(&s7s);
// ----------------------

void setup() {
// -------- GLOBAL --------
  Serial.begin(9600); 
  pinMode(built_in_led_PIN, OUTPUT);
  state_ = "counting";
  box_time.millis_ = millis(); // Start the counter at current time.
  box_time.seconds_ = 10;
  box_time.minutes_ = 0;
  box_time.hours_ = 0;
  
// ------------------------

// ------- 7 SEGEMENT -----
  b7s.clearDisplay();
// ------------------------

// ------ Big Button -----
  pinMode(big_btn_led_PIN, OUTPUT);
  digitalWrite(big_btn_led_PIN, LOW);

  pinMode(big_btn_PIN, INPUT);
  digitalWrite(big_btn_PIN, HIGH);
// ------------------------

// --- Time Buttons ----
  pinMode(time_up_btn_PIN, INPUT); 
  digitalWrite(time_up_btn_PIN, HIGH); 

  pinMode(time_down_btn_PIN, INPUT); 
  digitalWrite(time_down_btn_PIN, HIGH); 
// -----------------------

// -------- Servo --------
  servo.attach(servo_PIN);
  // servo.write(fill_angle_);
  next = millis() + 500;
// -----------------------
}

// Loop waiting for button press.
void waitForPress() {
  // Turn on the LED.
  // digitalWrite(big_btn_led_PIN, HIGH);
  digitalWrite(built_in_led_PIN, HIGH);
  while (true) {
    /*bool did_press = digitalRead(big_btn_PIN);
    if (did_press == 1) {   // Button has been pressed, serve.
      digitalWrite(big_btn_led_PIN, LOW);
      state_ = "serving";
      break;
    }
  }*/
    delay(2000);
    digitalWrite(built_in_led_PIN, LOW);
    delay(2000);
    digitalWrite(built_in_led_PIN, HIGH);
  }
}

// Check if either time change button has been pressed. 
// If yes, update time information.
void checkForTimeChangeInput() {
  bool did_press_time_up = digitalRead(time_up_btn_PIN);
  if (did_press_time_up) {
    box_time.changeTime(0, 5, 0);
  }

  bool did_press_time_down = digitalRead(time_down_btn_PIN);
  if (did_press_time_down) {
    box_time.changeTime(0, -5, 0);
    if (box_time.isTimeUp()) {
      state_ = "waiting";
    }
  }
}

void dispenseFood() {
  servo.write(empty_angle_);
  delay(3000);
  servo.write(fill_angle_); 
    /*
  static bool rising = true;

  if (millis() > next) {
    if (rising) {
      servo.write(180);
      rising = false;
    } else {
      servo.write(0);
      rising = true;
    }
    next += 3000;
  }*/
}

void loop() {
  Serial.print(state_ + '\n');
  if (state_ == "counting") {
    // checkForTimeChangeInput();
    if (state_ == "counting") {  // state could change if there was input.
      if (millis() > (box_time.millis_ + 1000)) {  // A second has passed.
        box_time.changeTime(-1, 0, 0);
        b7s.writeTime(box_time.seconds_, box_time.minutes_, box_time.hours_);

        if (box_time.isTimeUp()) {
          state_ = "waiting";
        }
     
        box_time.millis_ += 1000;
      }
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
