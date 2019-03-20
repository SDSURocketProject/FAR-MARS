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
  Serial.begin(9600);
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
      Serial.println(readlaunch);
      Serial.println("Launch");
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
    if(readign){
      Serial.println("ign");
      digitalWrite(igniter_out, LOW);
    }
  else{
      digitalWrite(igniter_out, HIGH);
  }
  if(readlox){
      Serial.println("lox");
      digitalWrite(lox_mpv_out, LOW);
    }
  else{
      digitalWrite(lox_mpv_out, HIGH);
  }
  if(readch4){
      Serial.println("ch4");
      digitalWrite(ch4_mpv_out, LOW);
    }
  else{
      digitalWrite(ch4_mpv_out, HIGH);
  }
}
