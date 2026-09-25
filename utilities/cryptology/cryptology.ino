#define AUTHOR_PASSWORD "my_super_secret_password"
#define AUTHOR_EMAIL "blackhole@caddog.net"
#define RECIPIENT_EMAIL "somebody@outlook.com"
#define RECIPIENT_NAME "Somebody"
#define SSID "your_wifi_ssid"
#define SSID_PASSWORD "your_wifi_password"

String salt;
String encryptedAuthorPassword;
String encryptedAuthorEmail;
String encryptedSSID;
String encryptedSSIDPassword;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  salt = ESP32UniqueID();
  printEncryptedCredentials();
  printDecryptedCredentials();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printEncryptedCredentials() {
  Serial.print("Encrypted passphrase: ");
  Serial.println(encryptedAuthorPassword = runRC4(AUTHOR_PASSWORD, salt));
  Serial.print("Encrypted Author email: ");
  Serial.println(encryptedAuthorEmail = runRC4(AUTHOR_EMAIL, salt));
  Serial.print("Encrypted SSID: ");
  Serial.println(encryptedSSID = runRC4(SSID, salt));
  Serial.print("Encrypted SSID Password: ");
  Serial.println(encryptedSSIDPassword = runRC4(SSID_PASSWORD, salt));
  Serial.println();
}

void printDecryptedCredentials() {
  Serial.print("Decrypted passphrase: ");
  Serial.println(runRC4(encryptedAuthorPassword, salt));
  Serial.print("Decrypted Author email: ");
  Serial.println(runRC4(encryptedAuthorEmail, salt));
  Serial.print("Decrypted SSID: ");
  Serial.println(runRC4(encryptedSSID, salt));
  Serial.print("Decrypted SSID Password: ");
  Serial.println(runRC4(encryptedSSIDPassword, salt));
}