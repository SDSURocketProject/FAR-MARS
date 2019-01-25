/* inputs */
static const int lox_vent_s = 0;
static const int ch4_vent_s = 1;
static const int vents      = 2;
static const int lox_mpv_s  = 3;
static const int ch4_mpv_s  = 4;
static const int mpvs       = 5;
static const int ignition   = 6; 

/* outputs */
static const int ground    = 7;
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

unsigned long time_now;

static int launchbool = 0;

int hasPeriodPassed(int);

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
	
	/* outputs */
	pinMode(ground, OUTPUT);
	pinMode(lox_vent, OUTPUT);
	pinMode(ch4_vent, OUTPUT);
	pinMode(ch4_mpv, OUTPUT);
	pinMode(lox_mpv, OUTPUT);
	pinMode(igniter, OUTPUT);
	
	/* write outputs to high except for ground */
	digitalWrite(ground, HIGH);
	digitalWrite(lox_vent, HIGH);
	digitalWrite(ch4_vent, HIGH);
	digitalWrite(ch4_mpv, HIGH);
	digitalWrite(lox_mpv, HIGH);
	digitalWrite(igniter, HIGH);

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

	/* read switches and actuate relays */
	if (!read_vents){
		digitalWrite(lox_vent, LOW);
		digitalWrite(ch4_vent, LOW);
	} else if (launchbool){
		/* remove ability of switches to control vents during launch timer */
	} else if (!(read_lox_vent || read_ch4_vent)){
		digitalWrite(lox_vent, !read_lox_vent);
		digitalWrite(ch4_vent, !read_ch4_vent);
	} else {
		digitalWrite(lox_vent, HIGH);
		digitalWrite(ch4_vent, HIGH);
	}
	
	if (!read_mpvs){
		digitalWrite(lox_mpv, LOW);
		digitalWrite(ch4_mpv, LOW);
	} else if (!(read_lox_mpv || read_ch4_mpv)){
		digitalWrite(lox_mpv, !read_lox_mpv);
		digitalWrite(ch4_mpv, !read_ch4_mpv);
	} else {
		digitalWrite(lox_mpv, HIGH);
		digitalWrite(ch4_mpv, HIGH);
	}

	if (!read_igniter){
		digitalWrite(igniter, LOW);
		time_now = millis();
		if (hasPeriodPassed(1000) || launchbool){
			launchbool = 1;
			digitalWrite(ch4_vent, LOW);
			time_now = millis();
			if (hasPeriodPassed(250)){
				digitalWrite(lox_vent, LOW);
			}
		}
	} else {
		launchbool = 0;
		digitalWrite(igniter, HIGH);
	}
}

int
hasPeriodPassed(int mils){
	return millis() > time_now + mils ? 1 : 0;
}
