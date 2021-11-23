const int P1 = PB0;
const int P2 = PB1;
const int P3 = PB2;
const int P4 = PB3;
const int P5 = PB4;
const int P6 = PB5;
const int P7 = PB6;
const int P8 = PB7;
const int P9 = PB8;
const int P10 = PB9;

const int ACT1 = PA0;
const int ACT2 = PA1;
const int ACT3 = PA2;
const int ACT4 = PA3;
const int ACT5 = PA4;
const int ACT6 = PA5;
const int ACT7 = PA6;
const int ACT8 = PA7;
const int ACT9 = PA8;
const int ACT10 = PA9;

const int TS6 = PA13;

static int activity_count = 1;
int round_count = 0;
static bool turn_off_leds = false;

#define TIMEOUT 2000


#define LOOP_RUN 100000

void setup() {
  // put your setup code here, to run once:

  // Initialized output pins for LEDs
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  pinMode(P4, OUTPUT);
  pinMode(P5, OUTPUT);
  pinMode(P6, OUTPUT);
  pinMode(P7, OUTPUT);
  pinMode(P8, OUTPUT);
  pinMode(P9, OUTPUT);
  pinMode(P10, OUTPUT);

  // Initialize input_pullup pins for buttons press
  pinMode(ACT1, INPUT_PULLUP);
  pinMode(ACT2, INPUT_PULLUP);
  pinMode(ACT3, INPUT_PULLUP);
  pinMode(ACT4, INPUT_PULLUP);
  pinMode(ACT5, INPUT_PULLUP);
  pinMode(ACT6, INPUT_PULLUP);
  pinMode(ACT7, INPUT_PULLUP);
  pinMode(ACT8, INPUT_PULLUP);
  pinMode(ACT9, INPUT_PULLUP);
  pinMode(ACT10, INPUT_PULLUP);

  pinMode(TS6, INPUT_PULLUP);

  // Attach interrupts to button input pins
  attachInterrupt(digitalPinToInterrupt(ACT1), toggle_led1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT2), toggle_led2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT3), toggle_led3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT4), toggle_led4, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT5), toggle_led5, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT6), toggle_led6, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT7), toggle_led7, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT8), toggle_led8, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT9), toggle_led9, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACT10), toggle_led10, CHANGE);

  //attachInterrupt(digitalPinToInterrupt(TS6), change_round, RISING);

  Serial.begin(9600);




}



void loop() {
  // put your main code here, to run repeatedly:

  //activity_count;
  //round_count;
  /*static bool state = false;

    if(readResponse())
    {
    state = !state;
    digitalWrite(P3, state);
    }*/

  //Serial.println(round_count);
  /*Serial.println(round_count);*/

  if (Serial.available())
  {
    if (Serial.peek() == 'n')
    {
      Serial.read();
      activity_count = 1;
      round_count = 0;
      turn_off_leds = true;
    }
  }

  if (digitalRead(TS6) == LOW)
  {
    while (digitalRead(TS6) == LOW);

    activity_count = 1;
    round_count++;
    turn_off_leds = true;
    Serial.print("r");
  }

  if (turn_off_leds == true)
  {
    turn_off_leds = false;

    digitalWrite(P1, LOW);
    digitalWrite(P2, LOW);
    digitalWrite(P3, LOW);
    digitalWrite(P4, LOW);
    digitalWrite(P5, LOW);
    digitalWrite(P6, LOW);
    digitalWrite(P7, LOW);
    digitalWrite(P8, LOW);
    digitalWrite(P9, LOW);
    digitalWrite(P10, LOW);
  }

  /*Serial.println("Activity: ");
    Serial.println(activity_count);*/

}

void toggle_led1()
{
  static bool state = false;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT1) == HIGH)
  {

    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P1, state);
    }
  }
}

void toggle_led2()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT2) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P2, state);
    }
  }
}


void toggle_led3()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT3) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P3, state);
    }
  }
}

void toggle_led4()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT4) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P4, state);
    }
  }
}

void toggle_led5()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT5) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (Serial.available())
    {
      while (Serial.available())
      {
        char c = Serial.read();
        //res += c;
        Serial.print(c);
      }
    }

    /*if (readResponse)
      {
      //activity_count++;
      state = !state;
      digitalWrite(P5, state);
      }*/
  }
}

void toggle_led6()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT6) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P6, state);
    }
  }
}

void toggle_led7()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT7) == HIGH)
  {

    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P7, state);
    }
  }
}

void toggle_led8()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT8) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P8, state);
    }
  }
}

void toggle_led9()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT9) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P9, state);
    }
  }
}

void toggle_led10()
{
  static bool state;

  for (int i = 0; i <= 32000; i++);

  if (digitalRead(ACT10) == HIGH)
  {
    if (activity_count >= (10 + round_count * 1))
    {
      activity_count = 0;
      round_count++;
      turn_off_leds = true;
    }

    Serial.println(String(activity_count));

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      //activity_count++;
      state = !state;
      digitalWrite(P10, state);
    }
  }
}

bool readResponse()
{
  String res = "";

  delay(100);

  /*while (Serial.available())
    {
    char c = Serial.read();
    res += c;
    }*/

  if (Serial.available())
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //res += c;
      Serial.print(c);
    }
    return true;
  }

  /*if ((res == "ACK") and (res.length() == 3))
    {
    res = "";
    //activity_count++;
    return true;
    } else if (res.length() > 3)
    {
    res = "";
    }*/

  /*if ((res == "ACK"))
    {
    res = "";
    //activity_count++;
    return true;
    }*/



  return false;
}
