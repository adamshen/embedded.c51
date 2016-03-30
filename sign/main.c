#include "board.h"

#include <string.h>

#include "ir.h"
#include "display.h"
#include "uart.h"

/* ir key march */
uint8 __code ircode[] = {0x86,0xc3,0xc6,0x57,0xc2,0x63,'\0'};

void init_board()
{
	Ir_init();
	init_uart();
}

void main()
{
	uint8 i;
	uint8 sign = 0;
	
	init_board();

	for (i = 0;i < 6;i++) {
		Show_Sign(i);
	}

	while (1) {
		for (i = 0;i < 6;i++) {
			if (irvalue == ircode[i]) {
				sign = i;
				break;
			}
		}
		Show_Sign(sign);	
	}
}	
