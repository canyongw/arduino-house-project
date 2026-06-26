#include <Arduino.h>
#define led_y 12    // Define LED pin
#define led_up_speed 10
#define led_dn_speed 10
#define led_hold_short 500
#define led_hold_long 2000
#define led_blink_spacing 500
unsigned long cycle_counter = 0;

void setup()
{
  pinMode(led_y, OUTPUT);  // Set pin as output mode
  Serial.begin(9600);
}

void blinklight()
{
  for (int i = 0; i< 2; i++)
  {
    analogWrite(led_y, 255);
    delay(led_hold_short);
    analogWrite(led_y, 0);
  }
  delay(led_blink_spacing);
  for (int i = 0; i < 2; i++)
  {
    analogWrite(led_y, 255);
    delay(led_hold_long);
    analogWrite(led_y, 0);
  }
  delay(led_blink_spacing);
}

void pulsefun()
{
    for(int i = 0; i < 255; i++)  // For loop: increment variable i until it reaches 255
  {
    analogWrite(led_y, i);  // PWM output to control LED brightness
    delay(led_up_speed);
  }

  for(int i = 255; i > 0; i--)  // For loop: decrement variable i until it reaches 0
  {
    analogWrite(led_y, i);
    delay(led_dn_speed);
  }
}

void loop()
{
  //Serial.print("Loop counter: ");
  //Serial.println(cycle_counter);
  cycle_counter++;
  if(cycle_counter == 200)
  {
    //Serial.println("Calling blinklight() and pulsefun()");
    cycle_counter = 0;
    blinklight();
    pulsefun();
  }
}