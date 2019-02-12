#include "serial.h"

/**
 * Serial Data reader
 *
 * @param pointed to char[] to put data in
 * @return int return code. 0: ran correctly, -1: error reading, -2: read nothing
 */
int
read_data(float *data){
	int n = 0, idx = 0, headerCheck = 0;
	unsigned char buf = '\0';
	unsigned char response[14];
	memset(response, '\0', sizeof response);
	while(1)  {
		n = read(fd, &buf, 1);
		if ( buf == (headerCheck+'A')){
			headerCheck++;
			if (headerCheck == 3){
				break;
			}
		}
		else {
			headerCheck = 0;
		}
	}
	if (n<0){
		return -1;
	}else if (n==0){
		return -2;
	}else{

		n = read(fd, response, 11);
		for (int i = 0; i < 3; i++){
			
			int reading;
			if (i == 0){
				reading = METHANE_READING;
			}else if(i == 1){
				reading = LOX_READING;
			}else if (i == 2){
				reading = HELIUM_READING;
			}
			float pressure = rawToPressure(*(u_int16_t *)(response+5+2*i), reading);
			data[i] = pressure;
		}
	}
}

float
rawToPressure(u_int16_t rawData, int reading){
	float pressure;
	switch (reading){
		case METHANE_READING:
			//retVal = ((float)rawData)-PRESSURE_DIVISION_CONSTANT*.1f; /* remove 0.5v bias */
			//retVal = (retVal/PRESSURE_DIVISION_CONSTANT)*PRESSURE_METHANE_MAX_PRESSURE;
			pressure = (float)rawData;
			pressure = (pressure/PRESSURE_DIVISION_CONSTANT)*5-0.5f;
			pressure = (pressure/4.0f)*PRESSURE_METHANE_MAX_PRESSURE;
			printf("doing methane");
			break;
		case LOX_READING:
			pressure = (float)rawData;
			pressure = (pressure/PRESSURE_DIVISION_CONSTANT)*5-0.5f;
			pressure = (pressure/4.0f)*PRESSURE_LOX_MAX_PRESSURE;
			printf("doing lox");
			break;
		case HELIUM_READING:
			pressure = (((float)rawData)/PRESSURE_DIVISION_CONSTANT)*PRESSURE_HELIUM_MAX_PRESSURE;
			break;
		default:
			printf("\tpressure conversion error\t");
			return 0.0f;
	}
	return pressure;
}

int
uart_init(){
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0){
		printf("error opening ttyUSB0: %d\n", fd);
		return fd;
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
		return errno;
	}
	return 0;
}

