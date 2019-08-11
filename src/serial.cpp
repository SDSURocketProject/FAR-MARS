#include "serial.h"

/* range: -270.00 to 0.00 C */
float subz_coef[] = {
	0.0000000E+00,
	2.5173462E+01,
	-1.1662878E+00,
	-1.0833638E+00,
	-8.9773540E-01,
	-3.7342377E-01,
	-8.6632643E-02,
	-1.0450598E-02,
	-5.1920577E-04,
	0.0000000E+00
};

/* range: 0.00 to 500.00 C */
float abvz_coef[]{
	 0.000000E+00,
	 2.508355E+01,
	 7.860106E-02,
	-2.503131E-01,
	 8.315270E-02,
	-1.228034E-02,
	 9.804036E-04,
	-4.413030E-05,
	 1.057734E-06,
	-1.052755E-08
};


/**
 * @brief Serial Data Parser
 *
 * @param[in] char* message to parse
 * @param[out] float* array to put values in
 * @param[out] u_int32_t* uint32 to put timestamp in
 */
void
parseMessage(char *message, float *output, u_int32_t *timestamp){
	//printf("%u\n", (u_int32_t)*(message+1));
	*timestamp = 0;
	//*timestamp = *(u_int32_t*)message+1;
	*timestamp |= *(u_int8_t*)(message+1);
	*timestamp |= *(u_int8_t*)(message+2)<<8;
	*timestamp |= *(u_int8_t*)(message+3)<<16;
	*timestamp |= *(u_int8_t*)(message+4)<<24;
	
	float methane = 0, lox = 0, helium = 0;
	methane = (float)*(u_int16_t*)(message+5);
	lox = (float)*(u_int16_t*)(message+7);
	helium = (float)*(u_int16_t*)(message+9);

	methane = (methane/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	output[0] = ((methane/4.0f)*PRESSURE_METHANE_MAX_PRESSURE)-PRESSURE_METHANE_BIAS;
	lox = (lox/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	output[1] = ((lox/4.0f)*PRESSURE_LOX_MAX_PRESSURE)-PRESSURE_LOX_BIAS;
	output[2] = ((helium/PRESSURE_DIVISION_CONSTANT)*PRESSURE_HELIUM_MAX_PRESSURE)-PRESSURE_HELIUM_BIAS;
	return;
}

/**
 * @brief Parse a pressure message from on board computer.
 *
 * @param[in, out] *message Pointer to the message to be parsed.
 */
void
parsePressureMessage(struct daqSensors *message, struct daqParsed *readings){
	float methane = 0, lox = 0, helium = 0, chamber = 0, voltage = 0, uaf = 0;
	methane = (float)message->PT_methane;
	lox = (float)message->PT_LOX;
	helium = (float)message->PT_helium;
	chamber = (float)message->PT_chamber;
	voltage = (float)message->BATT_voltage;
	uaf = (float)message->TC_uaf;

	methane = (methane/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	readings->PT_methane = (int16_t)((methane/4.0f)*PRESSURE_METHANE_MAX_PRESSURE)-PRESSURE_METHANE_BIAS;
	lox = (lox/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	readings->PT_LOX = (int16_t)((lox/4.0f)*PRESSURE_LOX_MAX_PRESSURE)-PRESSURE_LOX_BIAS;
	readings->PT_helium = (int16_t)((helium/PRESSURE_DIVISION_CONSTANT)*PRESSURE_HELIUM_MAX_PRESSURE)-PRESSURE_HELIUM_BIAS;
	readings->PT_chamber = (int16_t)((chamber/PRESSURE_DIVISION_CONSTANT)*PRESSURE_CHAMBER_MAX_PRESSURE)-PRESSURE_CHAMBER_BIAS;
	readings->BATT_voltage = (voltage/BATTERY_DIVISION_CONSTANT)*BATTERY_MULTIPLICATION_CONSTANT;
	readings->TC_uaf = tc_conv(1000.0f*(uaf/THERMO_DIVISION_CONSTANT)*1.024f);
	readings->HALL_methane = message->HALL_methane;
	readings->HALL_lox = message->HALL_lox;
	
	return;
}

/**
 * @brief Serial Data reader
 *
 * @param[out] *message Sensor message that was read in.
 * @return 0: ran correctly, -1: error reading
 */
int
readMessage(struct daqSensors *message){
	char in;
	u_int8_t messageBuffer[MESSAGE_BUFFER_SIZE];
	u_int8_t messageBufferIdx = 0;
	do {
		read(fd, (void*)&in, 1);
		if (messageBufferIdx >= MESSAGE_BUFFER_SIZE) {
			messageBufferIdx = 0;
		}
		messageBuffer[messageBufferIdx++] = in;
	} while (in != ESCAPE_EOM);
	
	messageBufferIdx = 0;
	if (unEscapeBuffer(messageBuffer, MESSAGE_BUFFER_SIZE, (uint8_t *)message, sizeof(struct daqSensors)) < 0) {
		return -1;
	}
	
	return 1;
}

float
tc_conv(float voltage){

	float temp = 0.0f;
	float temp2 =  1.0f;
	int abv = voltage > 1;
	for (int i = 0; i < 9; i++){
		temp +=  (abv ? abvz_coef[i] : subz_coef[i])*temp2;
		temp2 *= voltage;
	}
}

/**
 * @brief UART Init
 * @brief Initializes rs485 serial connection on ttyUSB0
 * @return	0: Device opened successfully
 * @return	-1: Device could not be opened
 * @return	-2: tcgetattr failed before configuration
 * @return	-3: tcgetattr failed after configuration
 */
int
uart_init(){
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0){
		return -1;
	}else{
		printf("ttyUSB0 opened successfully\n");
	}

	struct termios tty;
	struct termios tty_old;
	memset(&tty, 0, sizeof tty);

	if (tcgetattr(fd, &tty) < 0){
		return -2;
	}

	tty_old = tty;

	cfsetospeed(&tty, (speed_t)B38400);
	cfsetispeed(&tty, (speed_t)B38400);

	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
	
	cfmakeraw(&tty);

	tcflush(fd, TCIFLUSH);
	if (tcsetattr(fd, ICANON, &tty) < 0){
		return -3;
	}
	return 0;
}