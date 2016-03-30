#include "board.h"
#include "delay.h"

volatile uint8 irvalue = 0; 

void Ir_init()
{
	IT0 = 1;

	/* enable interrupte */
	EX0 = 1;
	EA = 1;

	/* init io */
	IRIN = 1;
}

void Read_ir(void) __interrupt (0) __using (0)
{
	uint8 i,j;
	uint8 timeout;
	uint8 IrValue[4];

	EX0 = 0;
	

	Delay1ms(1);	
	if (IRIN) {
		EX0 = 1;
		return;	
	}

	/* 9ms low ep */
	timeout = 9;
	while (IRIN == 0) {			
		Delay1ms(1);
		timeout--;
		if (timeout == 0) {
			EX0 =1;
			return;
		}
	}

	/* 4.5ms high ep */
	timeout = 0;
	while (IRIN) {
		Delay1ms(1);
		timeout++;
		if (timeout == 0) {
			EX0 = 1;
			return;
		}
	}

	for (i = 0;i < 3;i++) {				
		for(j = 0;j < 8;j++) {

			/* 560us low ep */  
			timeout = 6;	
			while ((IRIN == 0) && (timeout > 0)) {
				DelayUs2X(50);
				timeout--;
			}
		
			timeout = 30;	
			while ((IRIN == 1) && (timeout > 0)) {
				DelayUs2X(50);
				timeout--;
					if(timeout == 0){
						EX0 = 1;
						return;
					}
			}

			IrValue[i]>>=1;
			if (timeout < 24) {
				IrValue[i]|=0x80;
			}

		}
	}

	irvalue = IrValue[2];		

	EX0 = 1;	
	return;
}
