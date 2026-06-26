#define motion_pin 14

void setup() {
  Serial.begin(9600);
  pinMode(motion_pin, INPUT);
}

void loop() {
  boolean pyroelectric_val = digitalRead(motion_pin);
  Serial.print("pyroelectric value  = ");
  Serial.println(pyroelectric_val);
  if (pyroelectric_val){
    
  }
  delay(200);
}