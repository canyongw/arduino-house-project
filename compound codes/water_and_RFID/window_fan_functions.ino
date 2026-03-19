
void moister_check_loop(){
  int water_val = analogRead(waterPin);
  Serial.println(water_val);
  if(is_raining(water_val)) { // if it is "raining"
    window_close();
    led_rain_indicator_on();
    activate_dehydration();
    //delay(200);
  } else {
    window_open();
    led_rain_indicator_off();
    deactivate_dehydration();
    //delay(200);
  }
}

bool is_raining(int water_val){
  if(water_val > 1500) { // if it is "raining"
    return true; // Return true if con
  } else {
    return false; // Return false otherwise
  }
}


void window_close(){
  window_servo.write(0);
}

void window_open(){
  window_servo.write(176);
}

void led_rain_indicator_on(){
  analogWrite(led_y, 255);
}

void led_rain_indicator_off(){
  analogWrite(led_y, 0);
}

void activate_dehydration(){
  digitalWrite(fanPin1, LOW);
  //digitalWrite(fanPin2, LOW);
  analogWrite(fanPin2, 210);
}

void deactivate_dehydration(){
  analogWrite(fanPin2, 0);
}