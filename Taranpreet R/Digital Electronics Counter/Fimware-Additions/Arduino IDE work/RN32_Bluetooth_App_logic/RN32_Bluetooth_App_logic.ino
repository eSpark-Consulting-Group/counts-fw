int round_sw = PIN_A1;
int activity_sw = PIN_A2;
static int total_activities = 0;
static int activity_count = 1;

#define LOOP_RUN 100000
#define TIMEOUT 5000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(round_sw, INPUT_PULLUP);
  pinMode(activity_sw, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(round_sw), send_round, CHANGE);
  attachInterrupt(digitalPinToInterrupt(activity_sw), send_activity, CHANGE);

  Serial.print("$$$");
  delay(1000);

  Serial.println("SN,COUNTS");
  delay(1000);

  Serial.println("R,1");
  delay(1000);

  Serial.print("---");

  delay(5000);

  while (Serial.available());
  {
    Serial.read();
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  //String res = "";

  /*if (Serial.available())
    {
    if (Serial.peek() == 'N')
    {
      Serial.read();

      char c = Serial.read();
      res += c;
    }

    total_activities = res.toInt();
    }*/

  /*Serial.println("Hello");
    delay(1000);*/

}

void send_round()
{
  for (int i = 0; i < 32000; i++);

  if (digitalRead(round_sw) == HIGH)
    Serial.print("R");
}

void send_activity()
{
  for (unsigned long i = 0; i < 64000; i++);

  if (digitalRead(activity_sw))
  {
    Serial.print(String(activity_count++));

    //unsigned long time_millis = millis();
    //while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

  }
}

bool readResponse()
{
  String res = "";

  if (Serial.available())
  {
    while (Serial.available())
    {
      char c = Serial.read();
      res += c;
    }

  }


  /*if ((res == "ACK"))
    {
    res = "";
    return true;
    }*/



  return true;
}
