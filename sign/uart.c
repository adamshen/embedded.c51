#include "board.h"
#include "delay.h"

void init_uart()
{
	/* uart model 1 */
	SCON=0x50;

	/* timer1 model 2 */ 		
	TMOD = TMOD | 0x20;
	TMOD = TMOD & 0xef;

	/* double baudrate */
	PCON = 0x80;
	
	/* baudrate 4800 */
	TH1=0xF3;
	TL1=0xF3;
	
	TR1=1;
}

void uart_send_char(uint8 data)
{
	SBUF = data;
	while(!TI);
	TI=0;	
	Delay10ms(50);
}	

