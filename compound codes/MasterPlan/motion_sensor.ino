#include <chrono>
#include <Arduino.h>

auto MOTIONSTART = std::chrono::steady_clock::now();
boolean MOTIONDETECT = 0;
const auto MOTIONTIMELIMIT = std::chrono::seconds(1);

void detectMotion(){
  boolean pyroelectric_val = digitalRead(motion_pin);
  if (pyroelectric_val){
    MOTIONSTART = std::chrono::steady_clock::now();
    if (!MOTIONDETECT){
      MOTIONDETECT = 1;
      floodLight(1);
    }

  }
  
  if (MOTIONDETECT) {
    auto nowtime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(nowtime - MOTIONSTART);
    if (duration > MOTIONTIMELIMIT){
      MOTIONDETECT = 0;
      manualOff();
    }
  }
}

  //floodLight(10);
    // mylcd.print("MOTION!");
    // theaterChase(strip.Color(250, 250, 250), 50);      // White, half brightness
    // theaterChase(strip.Color(250,   0,   0), 50);      // Red, half brightness
    // theaterChase(strip.Color(  0,   0, 250), 50);     // Blue, half brightness
//     manualOff();

//   }

// }

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
  //delay(waitsec * 1000);
  // Serial.println("10 second delay compleate! :)");
  // strip.clear();
  // strip.show();
  // Serial.print("all lights are off");
}

void manualOff(){
 for (int i=0; i<strip.numPixels(); i++) {
strip.setPixelColor(i, strip.Color(0, 0, 0));
mylcd.clear();
 }  
 strip.show();
}