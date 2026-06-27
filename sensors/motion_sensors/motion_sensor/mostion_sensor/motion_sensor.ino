

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>                              // Required for 16 MHz Adafruit Trinket
#endif

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27,16,2);


#define motion_pin 14

#define LED_PIN    26                                // Which pin on the Arduino is connected to the NeoPixels?
#define LED_COUNT 4                                  // How many NeoPixels are attached to the Arduino?
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Declare our NeoPixel strip object:

void setup() {
  Serial.begin(9600);

  mylcd.init(); // lcd setup
  mylcd.backlight();
  mylcd.setCursor(0, 0);

  pinMode(motion_pin, INPUT);//motion pin
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);                   // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
#endif
  strip.begin();                                     // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                                      // Turn OFF all pixels ASAP
  strip.setBrightness(250);                           // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  boolean pyroelectric_val = digitalRead(motion_pin);
  Serial.print("pyroelectric value  = ");
  Serial.println(pyroelectric_val);
  if (pyroelectric_val){
  //floodLight(10);
    mylcd.print("MOTION!");
   theaterChase(strip.Color(250, 250, 250), 50);      // White, half brightness
  theaterChase(strip.Color(250,   0,   0), 50);      // Red, half brightness
  theaterChase(strip.Color(  0,   0, 250), 50);     // Blue, half brightness
  manualOff();

  }
  delay(200);
 
  
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {           // For each pixel in strip...
    strip.setPixelColor(i, color);                   // Set pixel's color (in RAM)
    strip.show();                                    // Update strip to match
    delay(wait);                                     // Pause for a moment
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {                         // Repeat 10 times...
    for(int b=0; b<3; b++) {                        // 'b' counts from 0 to 2...
      strip.clear();                                // Set all pixels in RAM to 0 (off)
      for(int c=b; c<strip.numPixels(); c += 3) {    // 'c' counts up from 'b' to end of strip in steps of 3...
        strip.setPixelColor(c, color);               // Set pixel 'c' to value 'color'
      }
      strip.show();                                 // Update strip with new contents
      delay(wait);                                  // Pause for a moment
    }
  }
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) {        // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();                                   // Update strip with new contents
    delay(wait);                                   // Pause for a moment
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;                           // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {                        // Repeat 30 times...
    for(int b=0; b<3; b++) {                       // 'b' counts from 0 to 2...
      strip.clear();                               // Set all pixels in RAM to 0 (off)
      for(int c=b; c<strip.numPixels(); c += 3) {  // 'c' counts up from 'b' to end of strip in increments of 3...
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color);             // Set pixel 'c' to value 'color'
      }
      strip.show();                               // Update strip with new contents
      delay(wait);                               // Pause for a moment
      firstPixelHue += 65536 / 90;               // One cycle of color wheel over 90 frames
    }
  }
}


void floodLight (int waitsec){
  strip.clear(); // 
 for (int i=0; i<strip.numPixels(); i++) {
  strip.setPixelColor(i, strip.Color(255, 255, 255));
  Serial.println("lights are on");
}
  strip.show();
  Serial.println("starting 10 second delay");
  delay(waitsec * 1000);
  Serial.println("10 second delay compleate! :)");
  strip.clear();
  strip.show();
  Serial.print("all lights are off");
}

void manualOff(){
 for (int i=0; i<strip.numPixels(); i++) {
strip.setPixelColor(i, strip.Color(0, 0, 0));
mylcd.clear();
 }  
 strip.show();
}










