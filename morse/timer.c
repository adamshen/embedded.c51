#include "board.h"

/* extern func */
extern void Delay1ms(uint8 t);

/* globe varialbe */
volatile uint8 frq = 100;
volatile uint8 c = 0;

void init_timer0()
{
	/* time0 16bit */
	TMOD = TMOD & 0xf1;
	TMOD = TMOD | 0x01;
	
	/* enable interrupt */
	EA = 1;
	ET0 =1;
}

void OStickISR (void) __interrupt (1) __using (0) 
{
	TH0 = 0xfe;
	TL0 = frq;

//	BEER = !BEER;	

	if (c == 0) {
		BEER = 0;
		c++;
	}

	if (c == 1) {
		BEER = 1;
		c--;
	}
}

void beer(uint8 cont)
{
	uint8 i;

	if (cont == WARN) {
		frq = 0;
		TR0 = 1;
		for (i = 0;i < 200;i++) {
			frq++;
			Delay1ms(1);
		}
		TR0 = 0;
	}

	if(cont == DOT) {
		frq = 100;
		TR0 = 1;
		Delay1ms(50);
		TR0 = 0;
	}

	if(cont == DASH) {
		frq = 100;
		TR0 = 1;
		Delay1ms(150);
		TR0 = 0;
	}	
}
