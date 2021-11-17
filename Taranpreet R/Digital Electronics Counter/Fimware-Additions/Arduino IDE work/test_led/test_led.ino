const int test_led = PC13;

void setup() {
  // put your setup code here, to run once:
  pinMode(test_led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(test_led, HIGH);
  delay(500);

  digitalWrite(test_led, LOW);
  delay(500);
  
}
