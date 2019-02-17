#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <string>
#include <cstring>

static int fd;
static int rate = 0;

#define PRESSURE_DIVISION_CONSTANT 4095.0f
#define PRESSURE_METHANE_MAX_PRESSURE 1500.0f
#define PRESSURE_LOX_MAX_PRESSURE 1500.0f
#define PRESSURE_HELIUM_MAX_PRESSURE 5800.0f
#define PRESSURE_METHANE_BIAS 12.0f
#define PRESSURE_LOX_BIAS 14.0f
#define PRESSURE_HELIUM_BIAS 0.0f

enum reading {
	METHANE_READING = 0,
	LOX_READING = 1,
	HELIUM_READING = 2,
};

void parseMessage(char *message, float *output, uint32_t *timestamp);
int readMessage(char *message);
int uart_init(void);
