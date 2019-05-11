#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000l
#endif

#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit)))

int
main(void) {
	DDRD &= ~(1 << PD2); /* digital_1 = input */
	DDRD &= ~(1 << PD3); /* digital_2 = input */
	DDRD &= ~(1 << PD4); /* digital_3 = input */
	DDRD &= ~(1 << PD5); /* digital_4 = input */
	DDRD &= ~(1 << PD6); /* digital_5 = input */
	DDRD &= ~(1 << PD7); /* digital_6 = input */

	DDRB |=  (1 << PB0); /* d_out_1   = output */
	DDRB |=  (1 << PB1); /* d_out_2   = output */
	DDRB |=  (1 << PB2); /* d_out_3   = output */
	DDRB |=  (1 << PB3); /* ign_out   = output */

	PORTB |= (1 << PB0); /* d_out_1   = high */
	PORTB |= (1 << PB1); /* d_out_2   = high */
	PORTB |= (1 << PB2); /* d_out_3   = high */
	PORTB |= (1 << PB3); /* ign_out   = high */

	while (1) {
		if (BIT_IS_SET(PIND, PD7)){ /* if readlaunch */
			PORTB &= ~(1 << PB3); /* igniter low */
			_delay_(1000);
			PORTB &= ~(1 << PB0); /* ch4 low */
			_delay_(250);
			PORTB &= ~(1 << PB1); /* lox low */
			while (BIT_IS_SET(PIND, PD2)){ }
			continue;
		}
		
		/* d_out_1 = !digital_1 */
		if (BIT_IS_SET(PIND, PD2)) {
			PORTB &= ~(1 << PB0);
		} else {
			PORTB |=  (1 << PB0);
		}
		
		/* d_out_2 = !digital_2 */
		if (BIT_IS_SET(PIND, PD3)) {
			PORTB &= ~(1 << PB1);
		} else {
			PORTB |=  (1 << PB1);
		}

		/* d_out_3 = !digital_3 */
		if (BIT_IS_SET(PIND, PD4)) {
			PORTB &= ~(1 << PB2);
		} else {
			PORTB |=  (1 << PB2);
		}

		/* ign_out = !digital_4 */
		if (BIT_IS_SET(PIND, PD5)) {
			PORTB &= ~(1 << PB3);
		} else {
			PORTB |=  (1 << PB3);
		}
	}
}
