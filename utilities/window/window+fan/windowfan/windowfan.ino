#include <ESP32Servo.h>
#define led_y 12
#define fanPin1 19
#define fanPin2 18

#define servoPin 5
#define waterPin 34
Servo myservo;


void setup() {
  Serial.begin(9600);
  pinMode(waterPin, INPUT);

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
  int water_val = analogRead(waterPin);
  Serial.println(water_val);
  if(water_val > 1500) { // if it is "raining"
    myservo.write(0);
    analogWrite(led_y, 255);
     digitalWrite(fanPin1, LOW);
  digitalWrite(fanPin2, LOW);
  analogWrite(fanPin2, 210);
    delay(200);
  }
  else {
    myservo.write(176);
    analogWrite(led_y, 0);
    analogWrite(fanPin2, 0); 
    delay(200);
  }
}