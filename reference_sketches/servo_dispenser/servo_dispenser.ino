//BEGINNING OF CODE
//Author: Shane Halse
//Email: ShaneHalse@gmail.com
//Date: 02/11/2011
#define fill 155 //the position in degrees to fill the hopper
#define empty 20 //the position in degrees to empty the hopper
#define potPin A0 //this is the pin (must be analog) that the middle of the potentiometer is connected to

#include <Servo.h> //this is a library used to control a servo (for more information see www.arduino.cc for more info)

//variables
Servo mainServo; //declare the main servo
int trigger = 0; //this is used to switch between fill and empty
int potIn = 0; //this is the data read from pin A0 (the potPin)
int count = 1; //used as a time muliplier
void setup()
{
//basic setup
mainServo.attach(3); //tell arduino which pin the servo is on (the white wire from the servo)
//set the pin modes
pinMode(4, OUTPUT); //used to output 5V or High to the potentiometer
pinMode(10, OUTPUT); //used for the led
pinMode(11, OUTPUT); //used for the led

digitalWrite(4, HIGH); //set pin 4 high
digitalWrite(10, LOW); //set pin 10 low
}


void loop()
{

potIn = analogRead(potPin); //read the position the potentiometer is at
//if the trigger value is 0 fill the hopper
if(!trigger)
{
mainServo.write(fill);//move servo to fill position
//this is used to setup the delay
//count = 171 //uncomment this to set the max delay to 3 hours
//the delay below is calculated using potin (which can be 0-1024) as delayinseconds ~= 0 - 64 seconds
for(;count>=0;count--)
{
for(;potIn>0;potIn=potIn-20)
{
//this is to make the LED flash every 100+potIn miliseconds
digitalWrite(11,HIGH); //set led to on
delay(100+potIn);
digitalWrite(11,LOW); //set led to off
delay(100+potIn);
}
}
count = 1;
trigger = 1; //change trigger to 1 to setup empty
digitalWrite(11,LOW); //set led off
}
else if(trigger)
{
mainServo.write(empty); //set the servo to empty position
delay(1000); //delay while servo sets position
trigger = 0; //change trigger to 0 to setup fill
}
}
//END OF CODE

Connect the Arduino to your computer 
click the compile button
Upload the compiled code to the board and it should start working automatically

You can then mount the unit to the wall, place a bowl under the unit and let the fun ensue!

*NOTES* - If you want you can add some sort of button your dog presses to get a treat rather than waiting and you will have just made the famous Skinner box!
