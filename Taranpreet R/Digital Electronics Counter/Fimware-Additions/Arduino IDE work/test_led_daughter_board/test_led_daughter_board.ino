void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_PA5, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_PA5, HIGH);
  delay(500);

  digitalWrite(PIN_PA5, LOW);
  delay(500);
}
