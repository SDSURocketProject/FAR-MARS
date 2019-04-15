#include "arduino.h"

/// PORT B ///

B0,B1,B2,B3		B4,B5,XX,XX

B0 = DIO8
B1 = DIO9
B2 = DIO10
B3 = DIO11
B4 = DIO12
B5 = DIO13
 
/// PORT C ///

C0 = AIO0
C1 = AIO1
C2 = AIO2
C3 = AIO3
C4 = AIO4
C5 = AIO5

/// PORT D ///

D0,D1,D2,D3		D4,D5,D6,D7

D0 = DIO0
D1 = DIO1
D2 = DIO2
D3 = DIO3
D4 = DIO4
D5 = DIO5
D6 = DIO6
D7 = DIO7


void pinMode(int pin, int pinmode){
	uint8_t mode = 0x1;
	if (pinmode == OUTPUT){
		if (pin < 8){
			DDRD |= mode << pin;
		} else {
			DDRB |= mode << pin-8;
		}
	} else{
		if (pin < 8){
			DDRD ^= mode << pin;
		} else {
			DDRB ^= mode << pin-8;
		}
	}
}

void digitalWrite(int pin, int state){
	if (pin < 8){
		if (state == HIGH){
			PORTD |= 0x1 << pin;
		} else {
			PORTD ^= 0x1 << pin-8;
		}
	} else {
		if (state == HIGH){
			PORTB |= 0x1 << pin;
		} else {
			PORTB ^= 0x1 << pin-8;
		}
	}
}

int digitalRead(int pin){
	if (pin < 8){
		return PIND &= (0x1 << pin);
	}
	return PINB &= (0x1 << pin-8);
}
