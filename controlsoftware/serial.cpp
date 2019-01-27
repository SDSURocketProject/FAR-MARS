#include "serial.h"

int
read_data(char *data[]){
	int n = 0;
	char buf = '\0';
	char response[7];
	memset(response, '\0', sizeof response);
	for (int i = 0; i < 7; i++){
		n = read(fd, &buf, 1);
		sprintf(&response[i], "%c", buf);
	}

	if (n<0){
		char str[1000];
		sprintf(str, "Error reading: %d\n", errno);
		warning *warningPopup = new warning();
		warningPopup->setWarning(str);
		warningPopup->show();
		return -1;
	}else if (n==0){
		warning *warningPopup = new warning();
		warningPopup->setWarning("Read nothing");
		warningPopup->show();
		return -2;
	}else{
		for (int i = 0; i < 7; i++){
			data[i] = response[ i ];
		}
	}
	return 0;
}

int
uart_init(){
	fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0){
		printf("error opening ttyUSB1: %d\n", fd);
		return fd;
	}else{
		printf("ttyUSB1 opened successfully\n");
	}

	struct termios tty;
	struct termios tty_old;
	memset(&tty, 0, sizeof tty);

	if (tcgetattr(fd, &tty) < 0){
		printf("error from tcgetattr: %d\n", errno);
	}

	tty_old = tty;

	cfsetospeed(&tty, (speed_t)B9600);
	cfsetispeed(&tty, (speed_t)B9600);

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

