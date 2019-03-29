#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "messages.h"
#include "com.h"

void parseMessage(char *message, float *output, uint32_t *timestamp);
void parsePressureMessage(struct sensorMessage *message);
int readMessage(struct sensorMessage *message);
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

enum pressures {
	METHANE_READING,
	LOX_READING,
	HELIUM_READING,
	CHAMBER_READING
};

enum halls {
	CH4_VNT,
	LOX_VNT
};

