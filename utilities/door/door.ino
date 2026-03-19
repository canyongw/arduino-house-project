//**********************************************************************************
/*
 * Filename    : RFID
 * Description : RFID reader UID
 * Auther      : http//www.keyestudio.com
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27,16,2);
#include <ESP32Servo.h>
Servo myservo;
#include "MFRC522_I2C.h"
// IIC pins default to GPIO21 and GPIO22 of ESP32
// 0x28 is the i2c address of SDA, if doesn't match，please check your address with i2c.
MFRC522_I2C mfrc522(0x28, -1); //Pass Wire object and address
#define servoPin  13
#define btnPin 16
boolean btnFlag = 0;

String password = "";

void setup() {
  Serial.begin(9600);           // initialize and PC's serial communication
  mylcd.init();
  mylcd.backlight();
  Wire.begin();                   // initialize I2C
  mfrc522.PCD_Init();             // initialize MFRC522
  ShowReaderDetails();            // dispaly PCD - MFRC522 read carder
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));

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

  mylcd.setCursor(0, 0);
  mylcd.print("swipe Card/tag");
}

void loop() {
  //
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    password = "";
    if(btnFlag == 1)
    {
      boolean btnVal = digitalRead(btnPin);
      if(btnVal == 0)  //If door close button is pressed (active-low)
      {
        mylcd.clear();
        Serial.println("close");
        mylcd.setCursor(0, 0);
        mylcd.print("closeing");
        myservo.write(0);
        btnFlag = 0;
      }
    }
    return;
  }

  // select one of door cards. UID and SAK are mfrc522.uid.

  // save UID
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(mfrc522.uid.uidByte[i]);
    password = password + String(mfrc522.uid.uidByte[i]);
  }
  Serial.println("");
  Serial.println(password);
  if(password == "17118515522" || password == "3710541177")  //Card number is correct,open the door
  {
    Serial.println("open");
    mylcd.setCursor(0, 0);
    mylcd.clear();
    mylcd.print("correct card.");
    mylcd.setCursor(0, 1);
    //mylcd.print("PWD: ");
    //mylcd.print(password);
    mylcd.print ("opening door");
     buzzer.playTone(532, 250);
    Serial.print("PWD: ");
    //Serial.println(password);
    myservo.write(180);
    password = "";
    btnFlag = 1;
  }
  else   //Card number error,dispaly error
  {
    password = "";
    mylcd.setCursor(0, 0);
    mylcd.print("error");

  }
  //Serial.println(password);
}

void ShowReaderDetails() {
  //  attain the MFRC522 software
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print("MFRC522 Software Version: 0x");
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown)"));
  Serial.println("");
  // when returning to 0x00 or 0xFF, may fail to transmit communication signals
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
  }
}
//**********************************************************************************