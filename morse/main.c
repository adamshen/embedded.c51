#include "board.h"

#include "string.h"

#include "key.h"
#include "morsecode.h"
#include "timer.h"
#include "uart.h"

/* function declare */
void reset_buff();
void handle_input(uint8 type);
void init_board();

/* global variable */ 
__idata uint8 buff[6] = BUFF_INIT;
volatile uint8 ClickNum = 0;
morsecode const *p;

/* function */
void main()
{
	uint8 key;
	
	init_board();	

	while(1) {
		if (GPIO_KEY != NO_KEY_PRESS) {
			key = Scan_key();
			/* handle input in func handle_input() */
			handle_input(key);
		}

	}
}


void init_board()
{
	GPIO_KEY = NO_KEY_PRESS;	

	init_uart();
	init_timer0();
}


void reset_buff()
{
	ClickNum = 0;
	strcpy(buff,BUFF_INIT);
} 


void handle_input(uint8 type) 
{
	/* check click times */	
	if (ClickNum > MAX_INPUT) {
		if (type != LETTER || type != WORD)
			reset_buff();
		beer(WARN);
		return;
	}

	if (type == DOT || type ==DASH) {
		beer(type);

		/* the ascii of '\0' is equal to number zero 
	   	   it may cause some trouble */
		buff[ClickNum++] = type + 1; 

		return;
	}

	if (type == LETTER || type == WORD) {
		buff[ClickNum] = '\0';

		/* decoding*/
		for (p = &letter_a;p != NULL;p = p->next) {
			if (strcmp(buff,p->morse_mask) == 0) {
			
				/* send */	
				uart_send_byte(p->output);
				if (type == WORD) uart_send_byte(SPACE);
				reset_buff();
				return;
			}	
		}

		/* not match */
		reset_buff();
		beer(WARN);
	}
}
