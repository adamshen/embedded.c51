#include "board.h"

void Delay10ms(uint8 t)
{
	uint8 i, j;

	for (;t > 0;t--) {
		for (i = 38;i > 0;i--) {
			for (j = 130;j > 0;j--);
		}          
	}       
}

void DelayUs2X(uint8 t)
{
	while (--t);
}

void Delay1ms(uint8 t)
{
	while (t--) {
		DelayUs2X(245);
		DelayUs2X(245);
	}
}



