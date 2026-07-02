#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BuzzerESP32.h>
LiquidCrystal_I2C mylcd(0x27,16,2);
#include <ESP32Servo.h>
Servo myservo;
#include "MFRC522_I2C.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define BUZZER_PIN   25
BuzzerESP32 buzzer(BUZZER_PIN);

// IIC pins default to GPIO21 and GPIO22 of ESP32
// 0x28 is the i2c address of SDA, if doesn't match，please check your address with i2c.
MFRC522_I2C mfrc522(0x28, -1); //Pass Wire object and address
#define servoPin  13
#define btnPin 16
boolean btnFlag = 0;

#define motion_pin 14
#define LED_PIN    26                                // Which pin on the Arduino is connected to the NeoPixels?
#define LED_COUNT 4
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); 

String password = "";

void setup() {
  Serial.begin(9600);           // initialize and PC's serial communication
  mylcd.init();
  mylcd.backlight();
  Wire.begin();                   // initialize I2C
  mfrc522.PCD_Init();             // initialize MFRC522
  ShowReaderDetails();            // dispaly PCD - MFRC522 read carder
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
  btnFlag = 0; 
  password = "";

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

    pinMode(motion_pin, INPUT);//motion pin
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);                   // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
#endif
  strip.begin();                                     // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                                      // Turn OFF all pixels ASAP
  strip.setBrightness(250);     
}

void loop() {
  //
   doorCloseRequest();
   readCard();
  
}

