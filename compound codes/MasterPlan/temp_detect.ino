

void tempExecute(){


   int Temperature;
   int Humidity;
   //Obtain data
   int chk = DHT11.read(DHT11PIN);
   Temperature = DHT11.temperature;
   Humidity = DHT11.humidity;
   // Display the temperature information at the corresponding position on the LCD
   mylcd.setCursor(0, 0);
   mylcd.print("Temp:");
   mylcd.setCursor(5, 0);
   mylcd.print(Temperature * 1.8 + 32);
   mylcd.setCursor(8, 0);
   mylcd.print("F  ");
   // Display humidity information at the corresponding position on the LCD
   mylcd.setCursor(0, 1);
   mylcd.print("Hum:");
   mylcd.setCursor(5, 1);
   mylcd.print(Humidity);
   mylcd.setCursor(8, 1);
   mylcd.print("%RH");

}


  void tempCheck(){
  // tempbtnFlag = digitalRead(tempbtnPin);
  bool tempCurrentStatus = false;
  
  // Read button (Inverted logic because of INPUT_PULLUP)
  tempCurrentStatus = (digitalRead(tempbtnPin) == LOW);
  //   if (tempCurrentStatus) {
  // Serial.println("btn is pressed-true");
  // }
  // if (tempbtnFlag) {
  // Serial.println("Previous run Flag is true-1");
  // }
    // Check for the exact moment the button is freshly pressed
  if (!tempCurrentStatus && tempbtnFlag) {
    clearlcd(mylcd); // Clears the screen EXACTLY ONCE
    //Serial.println("clear screen hit");
    
  }
  
  // Continually update the screen ONLY while the button stays held down
  if (tempCurrentStatus) {
    tempExecute();
  }

  // Save the current state for the next loop iteration
  tempbtnFlag = tempCurrentStatus;
}


void clearlcd(LiquidCrystal_I2C lcd){
  mylcd.setCursor(0, 0);
  mylcd.print("                ");
  mylcd.setCursor(0,1);
  mylcd.print("                ");
}





  // tempbtnFlag = digitalRead(tempbtnPin);


  // if (tempbtnFlag){

  //   tempbtnFlag = digitalRead(tempbtnPin);

  //   if (tempbtnFlag){

  //     tempExecute();

  //   } else {

  //     mylcd.clear();


  //   }
//  }
    
// }

