#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <cstring>
#include <warning.h>

static int fd;

float rawToPressure(u_int16_t rawData, int reading);
int read_data(float *data);
int uart_init(void);

#define PRESSURE_DIVISION_CONSTANT 4096.0f
#define PRESSURE_METHANE_MAX_PRESSURE 1500.0f
#define PRESSURE_LOX_MAX_PRESSURE 1500.0f
#define PRESSURE_HELIUM_MAX_PRESSURE 5800.0f

enum reading {
	METHANE_READING = 1,
	LOX_READING = 2,
	HELIUM_READING = 3,
};
