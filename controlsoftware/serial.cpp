#include "serial.h"
#include "messages.h"
#include "com.h"

#define MESSAGE_BUFFER_SIZE 100

/**
 * Serial Data reader
 *
 * @param[out] *message Sensor message that was read in.
 *
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
 * Serial Data Parser
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
 * Parse a pressure message from on board computer.
 *
 * @param[in, out] *message Pointer to the message to be parsed.
 */
void
parsePressureMessage(struct daqSensors *message){
	float methane = 0, lox = 0, helium = 0, chamber = 0;
	methane = (float)message->PT_methane;
	lox = (float)message->PT_LOX;
	helium = (float)message->PT_helium;
	chamber = (float)message->PT_chamber;

	methane = (methane/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	message->PT_methane = (int16_t)((methane/4.0f)*PRESSURE_METHANE_MAX_PRESSURE)-PRESSURE_METHANE_BIAS;
	lox = (lox/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	message->PT_LOX = (int16_t)((lox/4.0f)*PRESSURE_LOX_MAX_PRESSURE)-PRESSURE_LOX_BIAS;
	message->PT_helium = (int16_t)((helium/PRESSURE_DIVISION_CONSTANT)*PRESSURE_HELIUM_MAX_PRESSURE)-PRESSURE_HELIUM_BIAS;
	message->PT_chamber = (int16_t)((chamber/PRESSURE_DIVISION_CONSTANT)*PRESSURE_HELIUM_MAX_PRESSURE)-PRESSURE_HELIUM_BIAS;
	
	return;
}

/**
 * UART Init
 * Initializes rs485 serial connection on ttyUSB0
 * @return
 	0: Device opened successfully
 	-1: Device could not be opened
 	-2: tcgetattr failed before configuration
	-3: tcgetattr failed after configuration
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
