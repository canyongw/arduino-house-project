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

const char* ssid = "livingwater";
const char* password = "1John316";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

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
