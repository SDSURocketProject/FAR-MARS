#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "raw_serial.h"

void
uart_init(){
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0){
		printf("error opening ttyUSB0: %d\n", fd);
	}else{
		printf("ttyUSB0 opened successfully\n");
	}

	struct termios tty;
	struct termios tty_old;
	memset(&tty, 0, sizeof tty);

	if (tcgetattr(fd, &tty) < 0){
		printf("error from tcgetattr: %d\n", errno);
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
		printf("error from tcgetattr: %d\n", errno);
	}
}

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

void
readMessage(char *message){
	int n, idx = 0;
	char in;
	static char header[] = {'A', 'B', 'C'};
	while (1){
		n = read(fd, (void*)&in, 1);
		if (n == 0){
			printf("No byte read\n");
			return;
		}else if (n < 0){
			printf("error occured: %d\n", errno);
			return;
		}
		if (in == header[idx]){
			//printf("wrong character read in\n");
			//return;
			idx++;
			if (idx == 3){
				break;
			}
		}
	}
	n = read(fd, message, 11);
	if (n == 0){
		printf("No byte read\n");
		return;
	}else if (n < 0){
		printf("error occured: %d\n", errno);
		return;
	}
	return;
}

int
main(int argc, char* argv[]){
	static char message[11];
	static float pressures[3];
	static u_int32_t timestamp;
	f = fopen("log.txt", "a");
	fprintf(f, "TIME,CH4,LOX,HEL\n");
	uart_init();
	while (1){
		readMessage(message);
		parseMessage(message, pressures, &timestamp);
		printf("%u:\t%f\t%f\t%f\n", timestamp, pressures[0], pressures[1], pressures[2]);
		fprintf(f, "%u,%f,%f,%f\n", timestamp, pressures[0], pressures[1], pressures[2]);
	}
}








