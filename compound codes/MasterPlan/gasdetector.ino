
void detectGas(){
  boolean gasVal = digitalRead(gasPin);  // Read gas sensor value
  //Serial.println(gasVal);

  if(gasVal == 0)  // If dangerous gas detected
  {
    while(dangerDisplayed == 1)  // Update display if needed
    {
      mylcd.clear();
      mylcd.setCursor(0, 0);
      mylcd.print("dangerous");
      dangerDisplayed = 0;
      safetyDisplayed = 1;
    }

      // Sound alarm buzzer (short pulses)
      // digitalWrite(buzPin, HIGH);
      // delay(100);
      // digitalWrite(buzPin, LOW);
      // delay(100);

    buzzer.playTone(525, 500);
    buzzer.playTone(660, 500);
    Serial.println("noise should have been played by now");
  }
  else  // No dangerous gas detected
  {
    buzzer.stop();

    while(safetyDisplayed == 1)  // Update display if needed
    {
      mylcd.clear();
      mylcd.setCursor(0, 0);
      mylcd.print("safety");
      dangerDisplayed = 1;
      safetyDisplayed = 0;
    }
  }
}

