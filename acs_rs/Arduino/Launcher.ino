int igniter_in = 2;
int ch4_mpv_in = 3;
int lox_mpv_in = 4;
int launch_in = 5;
int igniter_out = 6;
int ch4_mpv_out = 7;
int lox_mpv_out = 8;
int readlaunch;
int readign;
int readlox;
int readch4;

void setup() { 
  pinMode(lox_mpv_out, OUTPUT);
  pinMode(ch4_mpv_out, OUTPUT);
  pinMode(igniter_out, OUTPUT);
  pinMode(igniter_in, INPUT);
  pinMode(ch4_mpv_in, INPUT);
  pinMode(lox_mpv_in, INPUT);
  pinMode(launch_in, INPUT);
  digitalWrite(igniter_out, HIGH);
  digitalWrite(ch4_mpv_out, HIGH);
  digitalWrite(lox_mpv_out, HIGH);
}


void loop() {
  readlaunch = digitalRead(launch_in);
  readign = digitalRead(igniter_in);
  readlox = digitalRead(lox_mpv_in);
  readch4 = digitalRead(ch4_mpv_in);
  if(readlaunch){
      digitalWrite(igniter_out, LOW);
      delay(1000);
      digitalWrite(ch4_mpv_out, LOW);
      delay(250);
      digitalWrite(lox_mpv_out, LOW);
      while(readlaunch){
        digitalWrite(igniter_out, LOW);
        digitalWrite(ch4_mpv_out, LOW);
        digitalWrite(lox_mpv_out, LOW);
        readlaunch = digitalRead(launch_in);
      }
    }
  else{
      digitalWrite(igniter_out, HIGH);
      digitalWrite(ch4_mpv_out, HIGH);
      digitalWrite(lox_mpv_out, HIGH);
  }
  switch(readign){
    case 0:
      digitalWrite(igniter_out, HIGH);
      break;
    case 1:
      digitalWrite(igniter_out, LOW);
      break;
  }
  switch(readlox){
    case 0:
      digitalWrite(lox_mpv_out, HIGH);
      break;
    case 1:
      digitalWrite(lox_mpv_out, LOW);
      break;
  }
  switch(readch4){
    case 0:
      digitalWrite(ch4_mpv_out, HIGH);
      break;
    case 1:
      digitalWrite(ch4_mpv_out, LOW);
      break;
  }
}
