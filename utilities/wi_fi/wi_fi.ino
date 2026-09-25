#define SSLCLIENT_HALF_DUPLEX
#define STATIC_IN_BUFFER_SIZE 2048
#define STATIC_OUT_BUFFER_SIZE 512
#include <ESP_SSLClient.h>

#include <WiFiClient.h>


#include <WiFi.h>

// ReadyMail is enabled and included here (the folder-named .ino, which Arduino
// compiles first) so that its types (SMTPStatus, SMTPClient, etc.) are declared
// before Arduino auto-generates function prototypes for the other .ino files.
// Without this, the auto-prototype for smtpStatusCallback(SMTPStatus) in
// Email.ino would reference SMTPStatus before ReadyMail.h is seen.
#define ENABLE_SMTP
#define ENABLE_DEBUG
#include <ReadyMail.h>


WiFiClient basic_client;
ESP_SSLClient ssl_client;

// RC4 ciphertext produced by utilities/cryptology on the author's specific
// ESP32 (chip-locked via eFuse MAC salt). Replace these placeholders with the
// encrypted output printed by that tool. These placeholders are NOT real secrets.
String encryptedSSID = "REPLACE_WITH_CIPHERTEXT";
String encryptedPassword = "REPLACE_WITH_CIPHERTEXT";

void setup() {
  Serial.begin(9600);

  // Derive the device-locked salt from the ESP32 eFuse MAC, then decrypt the
  // stored ciphertext credentials at runtime. RC4 is symmetric, so runRC4()
  // recovers the plaintext when given the same salt used to encrypt.
  String salt = generateSalt();
  String ssid = runRC4(encryptedSSID, salt);
  String password = runRC4(encryptedPassword, salt);

  // WiFi.begin expects const char*, so pass the decrypted Strings via c_str().
  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway (Router IP): ");
  Serial.println(WiFi.gatewayIP()); // Get router's IP address
  send_test_mail();
}

void loop() {
  // Empty loop
}
