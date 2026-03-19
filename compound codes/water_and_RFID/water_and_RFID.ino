// all of the #includes stuff.############################
#include <Wire.h>//this is wire.h

#include <ESP32Servo.h>//includes servo

#include <LiquidCrystal_I2C.h>//this is the lcd screen.
LiquidCrystal_I2C lcd_screen(0x27,16,2);

#define fanPin1 19//these 2 things are the fan.
#define fanPin2 18

#define led_y 12//this is the led.

#include "MFRC522_I2C.h"//this is the RFID detector.
MFRC522_I2C mfrc522(0x28, -1); //Pass Wire object and address 
String password = "";    

#define waterPin 34//this is the water detector.

#define windowservoPin 5//this is the window servo.
Servo window_servo;

#define doorservoPin  13//this is the door servo.
Servo door_servo;

#define btnPin 16//this is the button (left).
//the setup.

boolean btnFlag = 0; // keeps track if door is open.

void setup() { //the setup################################
  Serial.begin(9600);
  setup_gas_buzzer(); // sets up gas buzzer
  // door access setup ################################
  door_servo.setPeriodHertz(50);    // 50 hz servo
  door_servo.attach(doorservoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object
  door_servo.write(0);
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 
  lcd_screen.init();
  lcd_screen.backlight();
  Wire.begin();                   // initialize I2C
  mfrc522.PCD_Init();             // initialize MFRC522
  ShowReaderDetails();            // dispaly PCD - MFRC522 read carder
  // window ############################################
  window_servo.setPeriodHertz(50);    // standard 50 hz servo
  window_servo.attach(windowservoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object
  pinMode(waterPin, INPUT); // water detector ###
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  // Allow allocation of all timers############
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  lcd_screen.setCursor(0, 0);
  lcd_screen.print("swipe Card/tag");

  delay(200);
}
void loop() { //the loop #################################
  main_rfid_loop();
  moister_check_loop();
  delay(200);
}