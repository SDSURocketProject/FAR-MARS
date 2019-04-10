#include <util/delay.h>
#include <avr/io.h>

#define OUTPUT 0x1
#define INPUT 0x0

#define HIGH 0x1
#define LOW 0x0

void pinMode(int, int);
void digitalWrite(int, int);
int  digitalRead(int);
void delay(long);

