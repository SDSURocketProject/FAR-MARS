#include "serial.h"

/**
 * Serial Data reader
 *
 * @param pointed to char[] to put data in
 * @return int return code. 0: ran correctly, -1: error reading, -2: read nothing
 */
int
readMessage(char *message){
	DWORD dwRead;
	BOOL fWaitingOnRead = FALSE;
	OVERLAPPED osReader = {0};

	osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osReader.hEvent == NULL){
		return -1;
	}
	if (!fWaitingOnRead){
		if (!ReadFile(hcom, message, 14, &dwRead, &osReader)){
			return -2;
		}else{
			fWaitingOnRead = TRUE;
		}
	}
	return 0;
}

/**
 * Serial Data Parser
 *
 * @param[in] message pointer to message to parse
 * @param[out] output pointer to float array to put values in
 * @param[out] timestamp pointer to uint32 to put timestamp in
 */
void
parseMessage(char *message, float *output, uint32_t *timestamp){
	//printf("%u\n", (u_int32_t)*(message+1));
	*timestamp = 0;
	//*timestamp = *(u_int32_t*)message+1;
	*timestamp |= *(uint8_t*)(message+1);
	*timestamp |= *(uint8_t*)(message+2)<<8;
	*timestamp |= *(uint8_t*)(message+3)<<16;
	*timestamp |= *(uint8_t*)(message+4)<<24;
	
	float methane = 0, lox = 0, helium = 0;
	methane = (float)*(uint16_t*)(message+5);
	lox = (float)*(uint16_t*)(message+7);
	helium = (float)*(uint16_t*)(message+9);

	methane = (methane/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	output[0] = ((methane/4.0f)*PRESSURE_METHANE_MAX_PRESSURE)-PRESSURE_METHANE_BIAS;
	lox = (lox/PRESSURE_DIVISION_CONSTANT)*5.0f-0.5f;
	output[1] = ((lox/4.0f)*PRESSURE_LOX_MAX_PRESSURE)-PRESSURE_LOX_BIAS;
	output[2] = ((helium/PRESSURE_DIVISION_CONSTANT)*PRESSURE_HELIUM_MAX_PRESSURE)-PRESSURE_HELIUM_BIAS;
	return;
}

/**
 * UART Init
 * Initializes rs485 serial connection on ttyUSB0
 */
int
uart_init(){
	hcom = CreateFile( L"COM1",
						GENERIC_READ,
						0,
						0,
						OPEN_EXISTING,
						FILE_FLAG_OVERLAPPED,
						0);
	if (hcom == INVALID_HANDLE_VALUE){
		return -1;
	}
	return 0;
}
