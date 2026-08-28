
#include <BuzzerESP32.h>
#define buzPin 25
#define BUZZER_PIN   25
BuzzerESP32 buzzer(BUZZER_PIN);



#define led_y 12
#define fanPin1 19
#define fanPin2 18

#define windowservoPin 5
#define waterPin 34


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27,16,2);
#include <ESP32Servo.h>
Servo doorservo;

Servo windowservo;

#include "MFRC522_I2C.h" 

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif




// IIC pins default to GPIO21 and GPIO22 of ESP32
// 0x28 is the i2c address of SDA, if doesn't match，please check your address with i2c.
MFRC522_I2C mfrc522(0x28, -1); //Pass Wire object and address
#define doorservoPin  13
#define doorbtnPin 16 //doorbtn is door
boolean doorbtnFlag = 0;

#define tempbtnPin 27
boolean tempbtnFlag = 0;


#define motion_pin 14
#define LED_PIN    26                                // Which pin on the Arduino is connected to the NeoPixels?
#define LED_COUNT 4
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); 

#include <dht11.h>

#define gasPin 23  

boolean dangerDisplayed = 1;
boolean safetyDisplayed = 1;



// Define the pin constants
const int DHT11PIN = 17; // Temperature and humidity sensor pin
dht11 DHT11; // Initialize dht11

String password = "";

void setup() {
  Serial.begin(9600); 
  
  pinMode(gasPin, INPUT);
  
  pinMode(buzPin, OUTPUT);
  
  pinMode(waterPin, INPUT);
  mylcd.init();
  mylcd.backlight();
  Wire.begin();                   // initialize I2C
  mfrc522.PCD_Init();             // initialize MFRC522
  //ShowReaderDetails();            // dispaly PCD - MFRC522 read carder
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));

    // Allow allocation of all timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    doorservo.setPeriodHertz(50);    // standard 50 hz servo
    doorservo.attach(doorservoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object

    windowservo.setPeriodHertz(50);    // standard 50 hz servo
    windowservo.attach(windowservoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object

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

  buzzer.setTimbre(30);
}

void loop() {

   readCard();
   detectMotion();
   detectWater();
   detectGas();
   tempChe