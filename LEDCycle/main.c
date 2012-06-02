#include <msp430fr5739.h>

#define LED_PORTJ (BIT0 | BIT1 | BIT2 | BIT3)
#define LED_PORT3 (BIT4 | BIT5 | BIT6 | BIT7)


void cycle()
{

	P3OUT |= LED_PORT3;
	PJOUT |= LED_PORTJ;

	while (1) {
		PJOUT <<= 0x01;
		P3OUT >>= 0x01;
		if (!(PJOUT && P3OUT)) {
			PJOUT >>= 0x01;
			P3OUT <<= 0x01;
			//Reset
			if (!(PJOUT && P3OUT)) {
				while (!(PJOUT & 0x01) && !(P3OUT & 0x01)) {
					if (!(PJOUT && P3OUT)) {
						PJOUT |= BIT3;
							P3OUT |= BIT7;
					}
					PJOUT >>= 0x01;
					P3OUT <<= 0x01;
					__delay_cycles(30000);
				}
					PJOUT |= 0xFF;
			P3OUT |= 0xFF;
			}
		}
		__delay_cycles(30000);
	}
}

void init_ports()
{
	P3DIR |= LED_PORT3;
	PJDIR |= LED_PORTJ;
}

void main(void) {
	WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
	init_ports();
	cycle();
}
