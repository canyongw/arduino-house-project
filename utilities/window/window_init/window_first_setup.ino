#include <ESP32Servo.h>c:\Users\canyo\OneDrive\Desktop\smarthome\utilities\door\door.ino
#define counter 0

#define servoPin 5
Servo myservo;


void setup() {
  //Serial.begin(9600);
  //pinMode(waterPin, INPUT);

    // Allow allocation of all timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    myservo.setPeriodHertz(50);    // standard 50 hz servo
    myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object
    // using default min/max of 1000us and 2000us
    // different servos may require different min/max settings
    // for an accurate 0 to 180 sweep

  delay(200);
}

void loop() {
  if (counter == 0)
  {
    counter++;
    myservo.write(0);  //closing window
    //myservo.write(176);  //opening window
    delay(200);
  }
}