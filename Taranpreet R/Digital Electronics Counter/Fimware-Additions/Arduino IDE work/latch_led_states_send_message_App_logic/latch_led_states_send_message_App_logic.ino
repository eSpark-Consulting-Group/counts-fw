#include "STM32LowPower.h"

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

const int PBR = PB13;
const int PBS = PB15;

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

const int PBST = PA14;

const int orange = PC13;

static int activity_count = 0;
static int tens_count = 0;
static bool turn_off_leds = false;
char start_check = 'M'; // Enable
char stop_check = 'K';
bool bluetooth_flag = 0;
const char tens_count_charcaters [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

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

  pinMode(orange, OUTPUT);

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

  pinMode(PBR, INPUT_PULLUP);
  pinMode(PBS, INPUT_PULLUP);
  pinMode(PBST, INPUT_PULLUP);

  //pinMode(TS6, INPUT_PULLUP);

  // Attach interrupts to button input pins
  // attachInterrupt(digitalPinToInterrupt(ACT1), toggle_led1, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT2), toggle_led2, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT3), toggle_led3, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT4), toggle_led4, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT5), toggle_led5, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT6), toggle_led6, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT7), toggle_led7, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT8), toggle_led8, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT9), toggle_led9, FALLING);
  // attachInterrupt(digitalPinToInterrupt(ACT10), toggle_led10, FALLING);

  attachInterrupt(digitalPinToInterrupt(PBS), start_ISR, FALLING);

  //attachInterrupt(digitalPinToInterrupt(TS6), change_round, RISING);

  LowPower.begin();

  LowPower.attachInterruptWakeup(PBS, wakeup_ISR, FALLING, DEEP_SLEEP_MODE);

  Serial.begin(9600);

}



void loop() {

  if (Serial.available())
  {
    if (Serial.peek() == 'N')
    {
      Serial.read();
      tens_count = 0;
      tens_count = 0;
      turn_off_leds = true;
    }

    if (Serial.peek() == 'M') // Enable Play button when M is received from App
    {
      Serial.read();
      activity_count = 0;
      tens_count = 0;
      turn_off_leds = true;
      start_check = 'M';
      stop_check = 'K';
    }

    if (Serial.peek() == 'S')
    {
      Serial.read();
      stop_check = 'S';
      Serial.println();

    }

    if (Serial.peek() == 'K')
    {
      Serial.read();
      stop_check = 'K';
    }

    if (Serial.peek() == 'B')
    {
      Serial.read();
      bluetooth_flag = 1;
      //Serial.println("bluetooth_flag = 1");
    }

    if (Serial.peek() == 'Z')
    {
      Serial.read();
      bluetooth_flag = 0;
      //Serial.println("bluetooth_flag = 0");
    }

    if (Serial.peek() == 'X')
    {
      Serial.read();
      delay(10);
      //Serial.println("Sleeping, Program completed");
      Serial.end();
      LowPower.deepSleep();
    }


    Serial.read();
  }


  if (digitalRead(PBS) == LOW)
  {
    if (start_check == 'M')
    {
      unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= 1000);
      while (digitalRead(PBS) == LOW);
      if (digitalRead(PBS) == HIGH)
      {
        Serial.print("PL");

        unsigned long time_millis = millis();
        while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

        char buffer[] = {};

        if (Serial.available())
        {

          Serial.readBytes(buffer, 4);
        }

        // Flush all bytes
        while (Serial.available() > 0)
        {
          Serial.read();
        }

        if (strncmp(buffer, "PACK", 4) == 0)
        {

          start_check = 'P';
          if (bluetooth_flag)
          {
            bluetooth_flag = 0;
            //Serial.println("Sleeping, Bluetooth connected");
            Serial.end();
            LowPower.deepSleep();
          }
        }
      }
    }
  }




  if (digitalRead(PBST) == LOW)
  {
    if (stop_check == 'S')
    {
      unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= 1000);
      while (digitalRead(PBST) == LOW);
      if (digitalRead(PBST) == HIGH)
      {
        Serial.print("SA");

        unsigned long time_millis = millis();
        while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

        char buffer;

        if (Serial.available())
        {
          buffer = Serial.read();
        }

        // Flush all bytes
        while (Serial.available())
        {
          Serial.read();
        }

        if (buffer == 'K' || buffer == 'M')
        {
          stop_check = 'K';
        }
      }
    }
  }




  if (digitalRead(PBR) == LOW)
  {
    while (digitalRead(PBR) == LOW);
    //     tens_count = 1;
    //      tens_count++;
    //      turn_off_leds = true;
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

  if (digitalRead(ACT1) == LOW)
  {
    toggle_led1();
  } else if (digitalRead(ACT2) == LOW)
  {
    toggle_led2();
  } else if (digitalRead(ACT3) == LOW)
  {
    toggle_led3();
  } else if (digitalRead(ACT4) == LOW)
  {
    toggle_led4();
  } else if (digitalRead(ACT5) == LOW)
  {
    toggle_led5();
  } else if (digitalRead(ACT6) == LOW)
  {
    toggle_led6();
  } else if (digitalRead(ACT7) == LOW)
  {
    toggle_led7();
  } else if (digitalRead(ACT8) == LOW)
  {
    toggle_led8();
  } else if (digitalRead(ACT9) == LOW)
  {
    toggle_led9();
  } else if (digitalRead(ACT10) == LOW)
  {
    toggle_led10();
  }
}

void toggle_led1()
{
  static bool state = false;
  char activity[] = {0};

  //for (unsigned long i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT1) == LOW);

  if (digitalRead(ACT1) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count == 0)
    {
      Serial.print("1");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "1");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P1, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}

void toggle_led2()
{
  static bool state;
  char activity[] = {0};


  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT2) == LOW);

  if (digitalRead(ACT2) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("2");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "2");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P2, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}


void toggle_led3()
{
  static bool state;
  char activity[] = {0};


  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT3) == LOW);

  if (digitalRead(ACT3) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("3");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "3");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P3, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}

void toggle_led4()
{
  static bool state;
  char activity[] = {0};


  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT4) == LOW);

  if (digitalRead(ACT4) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("4");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "4");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P4, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}

void toggle_led5()
{
  static bool state;
  char activity[] = {0};

  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT5) == LOW);

  if (digitalRead(ACT5) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("5");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "5");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P5, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}

void toggle_led6()
{
  static bool state;
  char activity[] = {0};

  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT6) == LOW);

  if (digitalRead(ACT6) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("6");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "6");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P6, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}

void toggle_led7()
{
  static bool state;
  char activity[] = {0};

  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT7) == LOW);

  if (digitalRead(ACT7) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("7");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "7");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P7, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }

}

void toggle_led8()
{
  static bool state;
  char activity[] = {0};

  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT8) == LOW);

  if (digitalRead(ACT8) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("8");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "8");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P8, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }


}

void toggle_led9()
{
  static bool state;
  char activity[] = {0};

  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT9) == LOW);

  if (digitalRead(ACT9) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("9");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count], 1);
      strcat(activity, "9");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P9, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}

void toggle_led10()
{
  static bool state;
  char activity[] = {0};

  //for (int i = 0; i <= LOOP_RUN; i++);

  unsigned long time_millis2 = millis();
  while ((millis() - time_millis2) <= 1000);

  while (digitalRead(ACT10) == LOW);

  turn_off_leds = true;

  if (digitalRead(ACT10) == HIGH)
  {

    if (activity_count >= 10)
    {
      activity_count = 0;
      tens_count++;
      //turn_off_leds = true;
    }

    if (tens_count < 1)
    {
      Serial.print("10");
    } else if (tens_count >= 1)
    {
      strncat(activity, &tens_count_charcaters[tens_count + 1], 1);;
      strcat(activity, "0");
      Serial.print(activity);
    }

    unsigned long time_millis = millis();
    while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

    if (readResponse())
    {
      activity_count++;
      digitalWrite(P10, true);
    }

    /*unsigned long time_millis2 = millis();
      while ((millis() - time_millis2) <= TIMEOUT);*/

  }
}



void start_ISR()
{
  if (start_check == 'M')
  {

    Serial.println("Test");

    unsigned long time_millis2 = millis();
    while ((millis() - time_millis2) <= 1000);

    Serial.println("Test1");

    while (digitalRead(PBS) == LOW);

    Serial.println("Test2");

    if (digitalRead(PBS) == HIGH)
    {
      Serial.print("PL");

      unsigned long time_millis = millis();
      while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

      char buffer[] = {};

      if (Serial.available())
      {

        Serial.readBytes(buffer, 4);
      }

      // Flush bytes
      while (Serial.available() > 0)
      {
        Serial.read();
      }

      if (strncmp(buffer, "PACK", 4) == 0)
      {
        start_check = 'P';
      }

    }
  }
}



bool readResponse()
{
  char buffer[] = {0};
  bool status = false;

  if (Serial.available())
  {
    Serial.readBytes(buffer, 3);
  }

  if (strncmp((const char* )buffer, "ACK", 3) == 0)
  {
    status = true;
  } else {
    status = false;
  }

  return status;
}

void wakeup_ISR() {
  Serial.begin(9600);
  Serial.println("I am awake now and have enabled serial!");
}
