int round_sw = PIN_A1;
int activity_sw = PIN_A2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(round_sw, INPUT_PULLUP);
  pinMode(activity_sw, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(round_sw), send_round, CHANGE);
  attachInterrupt(digitalPinToInterrupt(activity_sw), send_activity, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*Serial.println("Hello World!");

    delay(1000);*/

}

void send_round()
{
  for (int i = 0; i < 32000; i++);

  if (digitalRead(round_sw) == HIGH)
    Serial.print("0");
}

void send_activity()
{
  for (int i = 0; i < 32000; i++);

  if (digitalRead(activity_sw))
    Serial.print("1");
}
