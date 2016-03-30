#include "board.h"

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

uint8 Scan_key()
{
	uint8 timeout = 50;
	uint8 KeyValue = 0;

	if (GPIO_KEY != NO_KEY_PRESS) {

		Delay1ms(10);
		if (GPIO_KEY != NO_KEY_PRESS) {

			GPIO_KEY = 0X0f;
			switch (GPIO_KEY) 
			{
				case(0X07):	break;
				case(0X0b):	KeyValue=4;break;
				case(0X0d): 	KeyValue=8;break;
				case(0X0e):	KeyValue=12;break;
			}

			GPIO_KEY = 0Xf0;
			switch (GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue+3;break;
				case(0Xb0):	KeyValue=KeyValue+2;break;
				case(0Xd0): 	KeyValue=KeyValue+1;break;
				case(0Xe0):	break;

			}

			while((timeout > 0) && (GPIO_KEY != 0xf0)) {
				Delay1ms(10);
				timeout--;
			}
			return KeyValue;
		}
	}
	return NO_KEY_PRESS;
}

