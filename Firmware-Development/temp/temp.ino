#define TIMEOUT 5000

String res = "";
uint8_t button_state = 0;
uint8_t act_count = 0;

struct data {
  char ind[10] = {'1', '2', '3', '4', '5',
                  '6', '7', '8', '9', '0'};
  char resp;
} payload;

void setup() {
  Serial.begin(9600);
  
  pinMode(PA0, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PA2, INPUT);
  pinMode(PA3, INPUT);
  pinMode(PA4, INPUT);
  pinMode(PA5, INPUT);
  pinMode(PA6, INPUT);
  pinMode(PA7, INPUT);
  pinMode(PA8, INPUT);
  pinMode(PA9, INPUT);
  
  pinMode(PB0, OUTPUT);
  pinMode(PB1, OUTPUT);
  pinMode(PB2, OUTPUT);
  pinMode(PB3, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PB5, OUTPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
  pinMode(PB8, OUTPUT);
  pinMode(PB9, OUTPUT);
  
  digitalWrite(PB0, LOW);
  digitalWrite(PB1, LOW);
  digitalWrite(PB2, LOW);
  digitalWrite(PB3, LOW);
  digitalWrite(PB4, LOW);
  digitalWrite(PB5, LOW);
  digitalWrite(PB6, LOW);
  digitalWrite(PB7, LOW);
  digitalWrite(PB8, LOW);
  digitalWrite(PB9, LOW);
}

void loop() {
  if((digitalRead(PA0) == LOW) && (button_state == 0)) {
    if(button_act(payload.ind[0])) {
      digitalWrite(PB0, HIGH);
      button_state = 1;
    }
  }

  if((digitalRead(PA1) == LOW) && (button_state == 1)) {
    if(button_act(payload.ind[1])) {
      digitalWrite(PB1, HIGH);
      button_state = 2;
    } 
  }

  if((digitalRead(PA2) == LOW) && (button_state == 2)) {
    if(button_act(payload.ind[2])) {
      digitalWrite(PB2, HIGH);
      button_state = 3;
    } 
  }

  if((digitalRead(PA3) == LOW) && (button_state == 3)) {
    if(button_act(payload.ind[3])) {
      digitalWrite(PB3, HIGH);
      button_state = 4;
    } 
  }

  if((digitalRead(PA4) == LOW) && (button_state == 4)) {
    if(button_act(payload.ind[4])) {
      digitalWrite(PB4, HIGH);
      button_state = 5;
    } 
  }

  if((digitalRead(PA5) == LOW) && (button_state == 5)) {
    if(button_act(payload.ind[5])) {
      digitalWrite(PB5, HIGH);
      button_state = 6;
    } 
  }

  if((digitalRead(PA6) == LOW) && (button_state == 6)) {
    if(button_act(payload.ind[6])) {
      digitalWrite(PB6, HIGH);
      button_state = 7;
    } 
  }

  if((digitalRead(PA7) == LOW) && (button_state == 7)) {
    if(button_act(payload.ind[7])) {
      digitalWrite(PB7, HIGH);
      button_state = 8;
    } 
  }

  if((digitalRead(PA8) == LOW) && (button_state == 8)) {
    if(button_act(payload.ind[8])) {
      digitalWrite(PB8, HIGH);
      button_state = 9;
    } 
  }

  if((digitalRead(PA9) == LOW) && (button_state == 9)) {
    if(button_act(payload.ind[9])) {
      digitalWrite(PB9, HIGH);
      button_state = 0;
    } 
  }

  if (Serial.available())
    payload.resp = Serial.read();
  
  if (payload.resp == 'N')
    reset_counter();
  
  
  //else 
    //digitalWrite(PB0, LOW);

  //Serial.println("Faizan");
  //delay(300);
}


bool button_act(char data) {
  bool response = true;
  
  if (act_count >= 10) {
    Serial.print(payload.ind[0]);
  } 

  Serial.print(data); // Button pressed
  


  Serial.read();
  
  uint16_t timer = millis();
  while(!Serial.available()) { // Halt the MCU if ACK is not received from App
     if (millis() - timer >= TIMEOUT) {
       response = false;
       break;
     }
  }

  if(response) {
    while(Serial.available()) {
      payload.resp = Serial.read();
      payload.resp += payload.resp;
    }
    
    if (strcmp(&payload.resp, "ACK")) {
      act_count++;
      payload.resp = '\0';
      return true;
    }
  }
  return false;
  
}

void reset_counter() {
  digitalWrite(PB0, LOW);
  digitalWrite(PB1, LOW);
  digitalWrite(PB2, LOW);
  digitalWrite(PB3, LOW);
  digitalWrite(PB4, LOW);
  digitalWrite(PB5, LOW);
  digitalWrite(PB6, LOW);
  digitalWrite(PB7, LOW);
  digitalWrite(PB8, LOW);
  digitalWrite(PB9, LOW);
  
  payload.resp = '\0'; 
  act_count = 0;
  button_state = 0;
}
