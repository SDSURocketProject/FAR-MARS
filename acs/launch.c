/* inputs */
static const int lox_vent_s = 0;
static const int ch4_vent_s = 1;
static const int vents      = 2;
static const int lox_mpv_s  = 3;
static const int ch4_mpv_s  = 4;
static const int mpvs       = 5;
static const int ignition   = 6; 
static const int launch    = 7;

/* outputs */
static const int lox_vent  = 8;
static const int ch4_vent  = 9;
static const int ch4_mpv   = 10;
static const int lox_mpv   = 11;
static const int igniter   = 12;

/* variables that read states of the inputs */
static int read_lox_vent;
static int read_ch4_vent;
static int read_vents;
static int read_lox_mpv;
static int read_ch4_mpv;
static int read_mpvs;
static int read_igniter;
static int read_launch;

void
setup(void){
  /* inputs */
  pinMode(lox_vent_s, INPUT);
  pinMode(ch4_vent_s, INPUT);
  pinMode(vents, INPUT);
  pinMode(lox_mpv_s, INPUT);
  pinMode(ch4_mpv_s, INPUT);
  pinMode(mpvs, INPUT);
  pinMode(ignition, INPUT);
  pinMode(launch, OUTPUT);

  /* outputs */
  pinMode(lox_vent, OUTPUT);
  pinMode(ch4_vent, OUTPUT);
  pinMode(ch4_mpv, OUTPUT);
  pinMode(lox_mpv, OUTPUT);
  pinMode(igniter, OUTPUT);

  /* write outputs to high except for ground */
  digitalWrite(lox_vent, HIGH);
  digitalWrite(ch4_vent, HIGH);
  digitalWrite(ch4_mpv, HIGH);
  digitalWrite(lox_mpv, HIGH);
  digitalWrite(igniter, HIGH);
  digitalWrite(launch, HIGH);
}

void
loop(void){
  /* reading the switches */
  read_lox_vent = digitalRead(lox_vent_s);
  read_ch4_vent = digitalRead(ch4_vent_s);
  read_vents    = digitalRead(vents);
  read_lox_mpv  = digitalRead(lox_mpv_s);
  read_ch4_mpv  = digitalRead(ch4_mpv_s);
  read_mpvs     = digitalRead(mpvs);
  read_igniter  = digitalRead(ignition);
  read_launch   = digitalRead(launch);

  /* read switches and actuate relays */
  if (!read_vents){
    digitalWrite(lox_vent, LOW);
    digitalWrite(ch4_vent, LOW);
  } else if (!read_lox_vent || !read_ch4_vent){
    digitalWrite(lox_vent, read_lox_vent);
    digitalWrite(ch4_vent, read_ch4_vent);
  } else {
    digitalWrite(lox_vent, HIGH);
    digitalWrite(ch4_vent, HIGH);
  }

  if (!read_mpvs){
    digitalWrite(lox_mpv, LOW);
    digitalWrite(ch4_mpv, LOW);
  } else if (launchbool){
    /* remove ability of switches to control mpvs during launch timer */
  } else if (!read_lox_mpv || !read_ch4_mpv){
    digitalWrite(lox_mpv, read_lox_mpv);
    digitalWrite(ch4_mpv, read_ch4_mpv);
  } else {
    digitalWrite(lox_mpv, HIGH);
    digitalWrite(ch4_mpv, HIGH);
  }

  if(!read_launch){
    digitalWrite(igniter, LOW);
    delay(1000);
    digitalWrite(ch4_mpv, LOW);
    delay(250);
    digitalWrite(lox_mpv, LOW);
    while(1){
    }
  }

  if(igniterbool){
  }else if (!read_igniter){
    digitalWrite(igniter, LOW);
  }else{
    digitalWrite(igniter, HIGH);
  }
}
