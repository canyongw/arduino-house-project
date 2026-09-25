// generateSalt()
// Builds a device-unique value from the ESP32's 64-bit eFuse MAC address and
// returns it as an Arduino String. The returned String is intended for use as
// the SALT value for a future cipher.
String ESP32UniqueID() {
  // Retrieve the 64-bit eFuse MAC address
  uint64_t chipId = ESP.getEfuseMac();

  Serial.println("--- ESP32 Unique Device ID ---");

  // Print the raw 64-bit numerical ID
  Serial.printf("Raw 64-bit ID: %llu\n", chipId);

  // Extract and format the individual MAC address bytes into the salt String
  Serial.print("Formatted MAC ID: ");
  String uniqueID = "";
  for (int i = 0; i < 6; i++) {
    // Extract each byte from the 64-bit integer
    byte macByte = (chipId >> (i * 8)) & 0xFF;

    // Format the byte as two-digit uppercase hex
    char hexByte[3];
    sprintf(hexByte, "%02X", macByte);

    // Separate bytes with ':' just like a standard MAC representation
    if (i > 0) {
      uniqueID += ":";
    }
    uniqueID += hexByte;
  }

  // Echo the formatted value that will be used as the cipher salt
  Serial.println(uniqueID);

  // Return the formatted, device-unique String for use as a cipher salt
  return uniqueID;
}
