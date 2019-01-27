#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <cstring>
#include <warning.h>

static int fd;

int read_data(char *data[]);
int uart_init(void);
