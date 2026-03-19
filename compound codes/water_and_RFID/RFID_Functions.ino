

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

void main_rfid_loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    password = "";
    if(btnFlag == 1)
    {
      boolean btnVal = digitalRead(btnPin);
      if(btnVal == 0)  //If door close button is pressed (active-low)
      {
        lcd_screen.clear();
        Serial.println("close");
        lcd_screen.setCursor(0, 0);
        lcd_screen.print("closing");
        door_close();
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
    test_card_confirmation_beep();
    Serial.println("open");
    lcd_screen.setCursor(0, 0);
    lcd_screen.clear();
    lcd_screen.print("correct card.");
    lcd_screen.setCursor(0, 1);
    //lcd_screen.print("PWD: ");
    //lcd_screen.print(password);
    lcd_screen.print ("opening door");
    //buzzer.playTone(532, 250);
    Serial.print("PWD: ");
    //Serial.println(password);
    password = "";
    door_open();
    btnFlag = 1;
  }
  else   //Card number error,dispaly error
  {
    siren_buzzer();
    password = "";
    lcd_screen.setCursor(0, 0);
    lcd_screen.print("error");

  }
  //Serial.println(password);
}

void door_open() {
  door_servo.write(180);
}

void door_close() {
  door_servo.write(0);
}