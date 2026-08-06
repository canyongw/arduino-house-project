

void detectWater() {
 int water_val = analogRead(waterPin);
  Serial.println(water_val);
  if(water_val > 1500) { // if it is "raining"
    windowservo.write(0);
    analogWrite(led_y, 255);
    digitalWrite(fanPin1, LOW);
    digitalWrite(fanPin2, LOW);
    analogWrite(fanPin2, 210);
  }
  else {
    windowservo.write(176);
    analogWrite(led_y, 0);
    analogWrite(fanPin2, 0); 
    
  }

}