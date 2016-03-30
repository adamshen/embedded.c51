#include "board.h"

#ifdef USE_UART
void init_uart(void)
{

/* enable receive */
#ifdef UART_REN
	REN = 1;
#endif

/* set uart mode */
#ifdef SMODX2
	PCON = PCON | SMOD;
#endif

#ifdef UART_MODE_0
	SM0 = 0;
	SM1 = 0;

#elif defined(UART_MODE_1)
	SM0 = 0;
	SM1 = 1;

#elif defined(UART_MODE_2)
	SM0 = 1;
	SM1 = 0;

#elif defined(UART_MODE_3)
	SM0 = 1;
	SM1 = 1;
#endif

/* set baud */
#if defined(UART_MODE_1) || defined(UART_MODE_3)

#ifdef USE_TIMER1
#error "timer1 can't be used."
#endif

#ifdef SMODX2
#define BUADC (6*32)
#else 
#define BUADC (12*32)
#endif
	TMOD = TMOD & (~T1_M0);
	TMOD = TMOD | T1_M1;

	TL1 = (256-(FOSC/BUADC/BAUD));
	TH1 = (256-(FOSC/BUADC/BAUD));

	TR1 = 1;
#endif

/* multi slave */
#ifdef UART_MULTI_SLAVE
	SM2 = 1;	
#endif

}

/* send a byte */
void uart_send_byte(unsigned char data)
{
	SBUF = data;
	while(!TI);
	TI = 0;
}

#endif
