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

struct daqSensors {
	uint32_t timestamp;
	int32_t TC_uaf;
	uint8_t HALL_methane, HALL_LOX;
	uint16_t BATT_voltage;
	int16_t PT_methane, PT_LOX, PT_helium, PT_chamber, PT_heliumReg;
} __attribute__((packed));

void parseMessage(char *message, float *output, uint32_t *timestamp);
void parsePressureMessage(struct daqSensors *message);
int readMessage(struct daqSensors *message);
int uart_init(void);


static int fd;
static int rate = 0;

#define PRESSURE_DIVISION_CONSTANT 4095.0f
#define PRESSURE_METHANE_MAX_PRESSURE 1500.0f
#define PRESSURE_LOX_MAX_PRESSURE 1500.0f
#define PRESSURE_HELIUM_MAX_PRESSURE 5800.0f
#define PRESSURE_CHAMBER_MAX_PRESSURE 5800.0f
#define PRESSURE_METHANE_BIAS 30.0f
#define PRESSURE_LOX_BIAS 41.0f
#define PRESSURE_HELIUM_BIAS 0.0f
#define PRESSURE_CHAMBER_BIAS 0.0f

enum pressures {
	CH4_READING,
	LOX_READING,
	HEL_READING,
	CBR_READING,
	REG_READING
};

enum halls {
	CH4_VNT,
	LOX_VNT
};

enum thermos {
	UAF
};
