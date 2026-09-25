#include <Arduino.h>



// NOTE: ReadyMail is first enabled and included in wi_fi.ino (compiled first) so
// that its types are visible to Arduino's auto-generated function prototypes.
// The lines below are kept for clarity; the #include is guarded (#ifndef
// READYMAIL_H) so it is a harmless no-op here, and re-defining these empty
// macros is also harmless.
#define ENABLE_SMTP
#define ENABLE_DEBUG
#include <ReadyMail.h>



// Sender SMTP settings (dreamhost - caddog)
// Change if using a different provider
#define SMTP_HOST "smtp.dreamhost.com"
#define SMTP_PORT 587

// Sender email, app password, and name
#define AUTHOR_EMAIL "blackhole@caddog.net"
#define AUTHOR_APP_PASS "garbelygook"
#define AUTHOR_NAME "ESP32"

//Recipient's email
#define RECIPIENT_EMAIL "somebody@outlook.com"
#define RECIPIENT_NAME "RECIPIENT_NAME"

//WiFiClientSecure ssl_client;


// Define a pointer instance for the client
SMTPClient smtp(ssl_client, 
  [](bool &success) { 
    // This callback is triggered by ReadyMail AFTER plain-text EHLO/STARTTLS commands.
    // It signals the SSL client wrapper to actively execute the TLS handshake.
    success = ssl_client.connectSSL(); 
  }, 
  true // Tells ReadyMail to expect and run a STARTTLS handshake sequence
);

void send_test_mail(){
    ssl_client.setClient(&basic_client, false); // Link the raw socket; keep SSL off initially
    ssl_client.setInsecure();

  // Pass the status callback (defined below) and ssl=false so the socket starts
  // in plain text; ReadyMail then issues STARTTLS and runs the TLS handshake
  // callback to upgrade the connection on port 587.
  smtp.connect(SMTP_HOST, SMTP_PORT, smtpStatusCallback, false);

  if (smtp.isConnected()) {
    smtp.authenticate(AUTHOR_EMAIL, AUTHOR_APP_PASS, readymail_auth_password);
    if (smtp.isAuthenticated()) {
      SMTPMessage msg;

      msg.headers.add(rfc822_from, String(AUTHOR_NAME) + " <" + AUTHOR_EMAIL + ">");
      msg.headers.add(rfc822_to, String(RECIPIENT_NAME) + " <" + RECIPIENT_EMAIL + ">");
      msg.headers.add(rfc822_subject, "Hello from the ESP32");
      //msg.text.body("This is a plain text message.");
      msg.html.body("<html><body><h1>Hello!</h1></body></html>");
      

      const int gmtOffset_sec = -6 * 60 * 60; //offset time in seconds
      const int daylightOffset_sec = 0; //daylight saving time offset in seconds

      configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
      // Set timestamp for the email
      while (time(nullptr) < 100000) delay(100);
      msg.timestamp = time(nullptr);

      if (smtp.send(msg)) {
        Serial.println("Email Sent Successfully!");
      } else {
        Serial.println("Email Send Failed.");
      }
      
      // Clean connection close (ReadyMail sends the SMTP QUIT command)
      smtp.logout();
    } else {
      Serial.println("Authentication Failed.");
    }
  } else {
    Serial.println("Could not connect to SMTP Host.");
  }
}







// Optional: Callback to monitor email status logs
void smtpStatusCallback(SMTPStatus status) {
  Serial.printf("ReadyMail Log: %s\n", status.text.c_str());
}