#include "board.h"

uint8 DisplayBuff[8]; 

/* delay */
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

/* key */
uint8 Key_Scan()
{

	uint8 keyValue = NO_KEY_PRESSED; 
	uint8 timeout = 50;

	if (KEY1 == 0 || KEY2 == 0) {

		Delay1ms(10);
		if (KEY1 == 0)
			keyValue = KEY1_PRESSED;
		if (KEY2 == 0)
			keyValue = KEY2_PRESSED;

		while ((timeout > 50) && (KEY1 == 0 || KEY2 == 0)) {
			Delay1ms(10);
			timeout--;
		}
	}

	return keyValue;
}

/* dig */
void Dig_Display()
{
	uint8 i;

	for (i = 0;i < 8;i++) {
		switch (i) 
		{
			case (0):
				LSA=0;LSB=0;LSC=0; break;

			case (1):
				LSA=1;LSB=0;LSC=0; break;

			case (2):
				LSA=0;LSB=1;LSC=0; break;

			case (3):
				LSA=1;LSB=1;LSC=0; break;

			case (4):
				LSA=0;LSB=0;LSC=1; break;

			case (5):
				LSA=1;LSB=0;LSC=1; break;

			case (6):
				LSA=0;LSB=1;LSC=1; break;

			case (7):
				LSA=1;LSB=1;LSC=1; break;
		}	
		GPIO_DIG = DisplayBuff[i];
		DelayUs2X(10);
		GPIO_DIG = DROP_SHADOW;
	}


}
