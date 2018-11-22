static const int LOXs = 7;
static const int CH4s = 6;
static const int LAUNCH = 5;
static const int LOX = 2;
static const int CH4 = 4;
static const int IGNITE = 3;
unsigned long time_now = 0;
static int LAUNCHBOOL = 0;

int hasPeriodPassed(int);

void
setup(void){
	pinMode(LOX, OUTPUT);
	pinMode(CH4, OUTPUT);
	pinMode(IGNITE, OUTPUT);
	pinMode(LOXs, INPUT);
	pinMode(CH4s, INPUT);
	pinMode(LAUNCH, INPUT);
	
	digitalWrite(LOX, HIGH);
	digitalWrite(CH4, HIGH);
	digitalWrite(IGNITE, HIGH);
}

void
loop(void){
	int vLAUNCH = digitalRead(LAUNCH);
	int vLOX = digitalRead(LOXs);
	int vCH4 = digitalRead(CH4s);
	
	if (vLAUNCH){
		digitalWrite(IGNITE, LOW);
		time_now = millis();
		if (hasPeriodPassed(1000) || LAUNCHBOOL){
			digitalWrite(CH4, LOW);
			time_now = millis();
			LAUNCHBOOL = 1;
			if (hasPeriodPassed(250)){
				digitalWrite(LOX, LOW);
			}
		}
	}
	else if (! (vLOX || vCH4)){
		digitalWrite(LOX, HIGH);
		digitalWrite(CH4, HIGH);
		digitalWrite(IGNITE, HIGH);
	}
	if (vLOX){
		digitalWrite(LOX, LOW);
	}
	if (vCH4){
		digitalWrite(CH4, LOW);
	}
}

int hasPeriodPassed(int mils){
	return millis() > time_now + mils ? 1 : 0;
}