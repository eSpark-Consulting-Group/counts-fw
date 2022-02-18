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

const int PWR_btn = PB10;
const int LF_OnOff = PB11;
const int BP_OnOff = PB12;
const int TBD1 = PB13;
const int TBD2 = PB14;

const int START = PB15;
const int PAUSE = PA13;
const int STOP = PA14;

const int CLICK1 = PC14;
const int CLICK2 = PC15;



void setup() {
  // put your setup code here, to run once:
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

  pinMode(PWR_btn, INPUT_PULLUP);
  pinMode(LF_OnOff, INPUT_PULLUP);
  pinMode(BP_OnOff, INPUT_PULLUP);
  pinMode(TBD1, INPUT_PULLUP);
  pinMode(TBD2, INPUT_PULLUP);

  pinMode(CLICK1, INPUT_PULLUP);
  pinMode(CLICK2, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Button 1");
  Serial.println(digitalRead(ACT1));

  Serial.println("Button 2");
  Serial.println(digitalRead(ACT2));

  Serial.println("Button 3");
  Serial.println(digitalRead(ACT3));

  Serial.println("Button 4");
  Serial.println(digitalRead(ACT4));

  Serial.println("Button 5");
  Serial.println(digitalRead(ACT5));

  Serial.println("Button 6");
  Serial.println(digitalRead(ACT6));

  Serial.println("Button 7");
  Serial.println(digitalRead(ACT7));

  Serial.println("Button 8");
  Serial.println(digitalRead(ACT8));

  Serial.println("Button 9");
  Serial.println(digitalRead(ACT9));

  Serial.println("Button 10");
  Serial.println(digitalRead(ACT10));

  Serial.println("PWR_btn");
  Serial.println(digitalRead(PWR_btn));

  Serial.println("LF_OnOff");
  Serial.println(digitalRead(LF_OnOff));

  Serial.println("BP_OnOff");
  Serial.println(digitalRead(BP_OnOff));

  Serial.println("TBD1");
  Serial.println(digitalRead(TBD1));

  Serial.println("TBD2");
  Serial.println(digitalRead(TBD2));


  delay(100);

}
