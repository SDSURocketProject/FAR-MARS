#include "serial.h"

/**
 * Serial Data reader
 *
 * @param pointed to char[] to put data in
 * @return int return code. 0: ran correctly, -1: error reading, -2: read nothing
 */
int
readMessage(char *message){
	int n, idx = 0;
	char in;
	static char header[] = {'A', 'B', 'C'};
	while (1){
		n = read(fd, (void*)&in, 1);
		if (n == 0){ /* if no byte is read in */
			return -2;
		}else if (n < 0){ /* if read returns an error */
			return -1;
		}
		if (in == header[idx]){
			idx++;
			if (idx == 3){
				break;
			}
		}
	}
	n = read(fd, message, 11);
	if (n == 0){ /* if no byte is read in */
		return -2;
	}else if (n < 0){ /* if read returns an error */
		return -1;
	}
	return 1;
}

/**
 * Serial Data Parser
 *
 * @param[in] message pointer to message to parse
 * @param[out] output pointer to float array to put values in
 * @param[out] timestamp pointer to uint32 to put timestamp in
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
 * UART Init
 * Initializes rs485 serial connection on ttyUSB0
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
