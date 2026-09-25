
// A passive buzzer only makes a tone when driven with an oscillating waveform.
// Holding buzPin with digitalWrite jerks the piezo once per edge -> the "blinker
// tick" and choked squeal. Drive it through BuzzerESP32 (the same blocking
// playTone path the song player uses) and warble two audible pitches for an alarm.
const uint16_t GAS_TONE_HIGH = (uint16_t)880;  // Hz (A5), high warble pitch
const uint16_t GAS_TONE_LOW  = (uint16_t)698;  // Hz (F5), low warble pitch
 const uint32_t GAS_TONE_MS   = 250;  // length of each warble half-step
boolean gasSirenHigh = 0;

void gasSirenStep(){
  gasSirenHigh = !gasSirenHigh;
  buzzer.playTone(gasSirenHigh ? GAS_TONE_HIGH : GAS_TONE_LOW, GAS_TONE_MS);
  Serial.println("noise has been played or should have been played");
  Serial.print("Tone Requested: ");
  Serial.println(gasSirenHigh ? GAS_TONE_HIGH : GAS_TONE_LOW);
  Serial.print("GAS_TONE_MS: ");
  Serial.println(GAS_TONE_MS);
}

void detectGas(){
  boolean gasVal = digitalRead(gasPin);  // active-low: 0 == dangerous gas detected
  Serial.println(gasVal);

  if(gasVal == 0)  // dangerous gas present
  {
    if(!GASDANGER)  // rising edge: seize the LCD exactly once and lock out other tools
    {
      GASDANGER = 1;
      mylcd.clear();
      mylcd.setCursor(0, 0);
      mylcd.print("dangerous");
    }
    gasSirenStep();  // warble the alarm through the buzzer library
  }
  else  // air is clear
  {
    if(GASDANGER)  // falling edge: silence the siren and release the lock exactly once
    {
      GASDANGER = 0;
      buzzer.stop();
      gasSirenHigh = 0;
      mylcd.clear();
      mylcd.setCursor(0, 0);
      mylcd.print("safety");
    }
  }
}

 