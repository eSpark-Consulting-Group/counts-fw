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

static int activity_count = 0;
static int round_count = 0;
static bool turn_off_leds = false;

#define TIMEOUT 5000


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
  attachInterrupt(digitalPinToInterrupt(ACT1), toggle_led1, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT2), toggle_led2, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT3), toggle_led3, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT4), toggle_led4, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT5), toggle_led5, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT6), toggle_led6, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT7), toggle_led7, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT8), toggle_led8, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT9), toggle_led9, FALLING);
  attachInterrupt(digitalPinToInterrupt(ACT10), toggle_led10, FALLING);

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
    if (Serial.peek() == 'N')
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
    Serial.print("R");
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

  //Serial.println(round_count);

  /*Serial.println("Activity: ");
    Serial.println(activity_count);*/

}

void toggle_led1()
{
  static bool state = false;

  //for (unsigned long i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT1) == LOW);

  if (digitalRead(ACT1) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("1");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "1");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P1, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}

void toggle_led2()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT2) == LOW);

  if (digitalRead(ACT2) == HIGH)
  {
    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("2");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "2");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P2, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}


void toggle_led3()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT3) == LOW);

  if (digitalRead(ACT3) == HIGH)
  {
    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("3");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "3");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P3, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}

void toggle_led4()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT4) == LOW);

  if (digitalRead(ACT4) == HIGH)
  {
    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("4");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "4");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P4, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}

void toggle_led5()
{
  static bool state;
  String res = "";

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT5) == LOW);

  if (digitalRead(ACT5) == HIGH)
  {
    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("5");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "5");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (Serial.available())
    {
      while (Serial.available())
      {
        char c = Serial.read();
        res += c;
      }

      if ((res == "ACK"))
      {
        res = "";
        activity_count++;
        state = !state;
        digitalWrite(P5, true);
      }

    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}

void toggle_led6()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT6) == LOW);

  if (digitalRead(ACT6) == HIGH)
  {
    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("6");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "6");
    }

    /*unsigned long time_millis = millis();
      while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));*/

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P6, true);
    }

    unsigned long time_millis2 = millis();
    while ((millis() - time_millis2) <= TIMEOUT);
  }
}

void toggle_led7()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT7) == LOW);

  if (digitalRead(ACT7) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("7");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "7");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P7, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}

void toggle_led8()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT8) == LOW);

  if (digitalRead(ACT8) == HIGH)
  {
    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("8");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "8");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P8, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}

void toggle_led9()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT9) == LOW);

  if (digitalRead(ACT9) == HIGH)
  {
    if (activity_count >= 10)
    {
      activity_count = 0;
      round_count++;
      //turn_off_leds = true;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("9");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count) + "9");
    };

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P9, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}

void toggle_led10()
{
  static bool state;

  //for (int i = 0; i <= LOOP_RUN; i++);

  while (digitalRead(ACT10) == LOW);

  turn_off_leds = true;

  if (digitalRead(ACT10) == HIGH)
  {
    if (activity_count > 10)
    {
      activity_count = 0;
      round_count++;
    }

    /*if (activity_count == 0)
      state = false;*/

    /*while (Serial.available())
      {
      Serial.read();
      }*/

    if (round_count < 1)
    {
      Serial.print("10");
    } else if (round_count >= 1)
    {
      Serial.print(String(round_count + 1) + "0");
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      state = !state;
      digitalWrite(P10, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/
  }
}

bool readResponse()
{
  String res = "";


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
      res += c;
      //Serial.print(c);
    }
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

  if ((res == "ACK"))
  {
    res = "";
    return true;
  }



  return false;
}
