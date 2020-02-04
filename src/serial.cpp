#include "serial.h"

/**
 * @brief Parse a pressure message from on board computer.
 *
 * @param[in, out] *message Pointer to the message to be parsed.
 */
void
parsePressureMessage(struct daqSensors *message, struct daqParsed *readings, int board_selection){
	float methane = 0, lox = 0, helium = 0, chamber = 0, voltage = 0, uaf = 0;
	methane = (float)message->PT_methane;
	lox = (float)message->PT_lox;
	helium = (float)message->PT_helium;
	chamber = (float)message->PT_chamber;
	voltage = (float)message->BATT_voltage;
	uaf = (float)message->TC_uaf;

	methane = (methane/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	readings->PT_methane = (int16_t)((methane/4.0f)*PRESSURE_METHANE_MAX_PRESSURE);
	lox = (lox/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	readings->PT_lox = (int16_t)((lox/4.0f)*PRESSURE_LOX_MAX_PRESSURE);
	readings->PT_helium = (int16_t)((helium/PRESSURE_DIVISION_CONSTANT)*PRESSURE_HELIUM_MAX_PRESSURE);
	chamber = (chamber/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	readings->PT_chamber = (int16_t)((chamber/4.0f)*PRESSURE_CHAMBER_MAX_PRESSURE);
	readings->BATT_voltage = (voltage/BATTERY_DIVISION_CONSTANT)*BATTERY_MULTIPLICATION_CONSTANT;
	readings->TC_uaf = (4.959f * (uaf / 4095.0f) - 1.25f) / 0.005f; /* result in degrees C */
	readings->HALL_methane = message->HALL_methane;
	readings->HALL_lox = message->HALL_lox;
	readings->timestamp = message->timestamp;

	switch (board_selection) {
		case alpha_board:
		readings->PT_methane -= PRESSURE_METHANE_BIAS_ALPHA;
		readings->PT_lox -= PRESSURE_LOX_BIAS_ALPHA;
		readings->PT_helium -= PRESSURE_HELIUM_BIAS_ALPHA;
		readings->PT_chamber -= PRESSURE_CHAMBER_BIAS_ALPHA;
		readings->PT_chamber *= PRESSURE_CHAMBER_GAIN_CORR_ALPHA;
		break;

		case beta_board:
		readings->PT_methane -= PRESSURE_METHANE_BIAS_BETA;
		readings->PT_lox -= PRESSURE_LOX_BIAS_BETA;
		readings->PT_helium -= PRESSURE_HELIUM_BIAS_BETA;
		readings->PT_chamber -= PRESSURE_CHAMBER_BIAS_BETA;
		readings->PT_chamber *= PRESSURE_CHAMBER_GAIN_CORR_BETA;
		break;
	}

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
