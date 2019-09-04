#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <termios.h>
#include <unistd.h>

#include "com.h"

struct daqSensors {
	uint32_t timestamp;
	int32_t TC_uaf;
	uint8_t HALL_methane, HALL_lox;
	uint16_t BATT_voltage;
	int16_t PT_methane, PT_lox, PT_helium, PT_chamber, PT_heliumReg;
} __attribute__((packed));

struct daqParsed {
	uint32_t timestamp;
	float TC_uaf;
	uint8_t HALL_methane, HALL_lox;
	float BATT_voltage;
	int16_t PT_methane, PT_lox, PT_helium, PT_chamber, PT_heliumReg;
};

enum obc_boards {
	alpha_board,
	beta_board,
};

//void parseMessage(char*, float*, uint32_t*);
void parsePressureMessage(struct daqSensors*, struct daqParsed*, int);
int readMessage(struct daqSensors*);
float tc_conv(float);
int uart_init(void);


static int fd;
static int rate = 0;

#define MESSAGE_BUFFER_SIZE 100
#define PRESSURE_DIVISION_CONSTANT 4095.0f
#define PRESSURE_METHANE_MAX_PRESSURE 3000.0f
#define PRESSURE_LOX_MAX_PRESSURE 3000.0f
#define PRESSURE_HELIUM_MAX_PRESSURE 5800.0f
#define PRESSURE_CHAMBER_MAX_PRESSURE 5800.0f
#define BATTERY_DIVISION_CONSTANT 4095.0f
#define BATTERY_MULTIPLICATION_CONSTANT 4.959f*11.0f
#define THERMO_DIVISION_CONSTANT 65535.0f

#define PRESSURE_METHANE_BIAS_ALPHA 0.0f
#define PRESSURE_LOX_BIAS_ALPHA 380.0f
#define PRESSURE_HELIUM_BIAS_ALPHA 0.0f
#define PRESSURE_CHAMBER_BIAS_ALPHA 0.0f

#define PRESSURE_METHANE_BIAS_BETA 0.0f
#define PRESSURE_LOX_BIAS_BETA 380.0f
#define PRESSURE_HELIUM_BIAS_BETA 0.0f
#define PRESSURE_CHAMBER_BIAS_BETA 0.0f

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
