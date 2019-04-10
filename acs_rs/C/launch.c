int igniter_in = 2;
int ch4_mpv_in = 3;
int lox_mpv_in = 4;
int launch_in = 5;
int igniter_out = 6;
int ch4_mpv_out = 7;
int lox_mpv_out = 8;
int ign_log = 9;
int ch4_log = 10;
int lox_log = 11;
int readlaunch;
int readign;
int readlox;
int readch4;

void
setup() { 
  pinMode(lox_mpv_out, OUTPUT);
  pinMode(ch4_mpv_out, OUTPUT);
  pinMode(igniter_out, OUTPUT);
  pinMode(ign_log, OUTPUT);
  pinMode(ch4_log, OUTPUT);
  pinMode(lox_log, OUTPUT);
  pinMode(igniter_in, INPUT);
  pinMode(ch4_mpv_in, INPUT);
  pinMode(lox_mpv_in, INPUT);
  pinMode(launch_in, INPUT);
  digitalWrite(igniter_out, HIGH);
  digitalWrite(ch4_mpv_out, HIGH);
  digitalWrite(lox_mpv_out, HIGH);
}

void
loop() {
  readlaunch = digitalRead(launch_in);
  readign = digitalRead(igniter_in);
  readlox = digitalRead(lox_mpv_in);
  readch4 = digitalRead(ch4_mpv_in);
  while (readlaunch){
    digitalWrite(igniter_out, LOW);
    delay(1000);
    digitalWrite(ch4_mpv_out, LOW);
    delay(250);
    digitalWrite(lox_mpv_out, LOW);
    readlaunch = digitalRead(launch_in);
  }
  digitalWrite(igniter_out, HIGH);
  digitalWrite(ch4_mpv_out, HIGH);
  digitalWrite(lox_mpv_out, HIGH);
  
  digitalWrite(igniter_out, readign^1);

  digitalWrite(lox_mpv_out, readlox^1);
  
  digitalWrite(ch4_mpv_out, readch4^1);

  digitalWrite(ign_log, readign^1);

  digitalWrite(lox_log, readlox^1);
  
  digitalWrite(ch4_log, readch4^1);
}