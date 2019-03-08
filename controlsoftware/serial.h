#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <termios.h>
#include <unistd.h>

void parseMessage(char *message, float *output, uint32_t *timestamp);
int readMessage(char *message);
int uart_init(void);

static int fd;
static int rate = 0;

#define PRESSURE_DIVISION_CONSTANT 4095.0f
#define PRESSURE_METHANE_MAX_PRESSURE 1500.0f
#define PRESSURE_LOX_MAX_PRESSURE 1500.0f
#define PRESSURE_HELIUM_MAX_PRESSURE 5800.0f
#define PRESSURE_METHANE_BIAS 30.0f
#define PRESSURE_LOX_BIAS 41.0f
#define PRESSURE_HELIUM_BIAS 0.0f

enum reading {
	METHANE_READING = 0,
	LOX_READING = 1,
	HELIUM_READING = 2,
};

