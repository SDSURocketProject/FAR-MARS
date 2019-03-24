

#ifndef COM_H_
#define COM_H_

#include <stdint.h>

#define ESCAPE_SOM 0x30 // Byte signifying start of message
#define ESCAPE_EOM 0x03 // Byte signifying end of message
#define ESCAPE_FLAG '~' // Byte signifying the following byte should have a special interpretation, don't use null for the escape flag

uint16_t CRCCCITT(uint8_t *data, uint32_t length);
int escapeBuffer(uint8_t *in, uint32_t inSize, uint8_t *out, uint32_t outSize);
int unEscapeBuffer(uint8_t *in, uint32_t inSize, uint8_t *out, uint32_t outSize);

#define COM_ASSERT(x)

// Configure the value of each return code for each project
enum escapeReturns {
	COM_BUFFER_SIZE = -1,
	COM_NO_EOM = -2,
	COM_NULL_POINTER = -3,
};

#endif // COM_H_