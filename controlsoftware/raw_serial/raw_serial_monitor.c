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
	fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0){
		printf("error opening ttyUSB1: %d\n", fd);
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
	}
}

void
read_data(){
	int n = 0, idx = 0;
	char buf = '\0';
	char response[1024];
	memset(response, '\0', sizeof response);
	do{
		n = read(fd, &buf, 1);
		sprintf(&response[idx], "%c", buf);
		idx += n;
	}while(buf != '\r' && n > 0);

	if (n<0){
		printf("Error reading: %d\n", errno);
	}else if (n==0){
		printf("Read nothing");
	}else{
		printf("Response:\n%s\n", response);
	}
}

int
main(int argc, char *argv[]){
	uart_init();
	while(1){
		read_data();
	}
	return 0;
}
