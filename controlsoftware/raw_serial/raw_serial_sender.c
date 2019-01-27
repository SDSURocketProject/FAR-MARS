#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

static int fd;

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
	}
}

void
write_data(){
	for (int i = 0; i < 7; i++){
		u_int8_t val = (u_int8_t)(rand()%100);
		int n_written = write(fd, &val, 1);
		printf("%u", (char)val);
	}
}

int
main(int argc, char *argv[]){
	uart_init();
	time_t t;
	srand((unsigned)time(&t));
	write_data();
	printf("\n");
	return 0;
}
