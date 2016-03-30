#include <8051.h>

//MACRO		
//#define USE_TIMER	
//#define USE_UART	
//#difine USE_IR		

void board_init(void)
{
#ifdef USE_TIMER
	timer_init();
#endif

#ifdef USE_UART
	uart_init();
#endif

#ifdef USE_IR
	ir_init();
#endif
}

/* init timer */
//#define timer0_count
//#define timer0_gate
//#define timer0_model 1

//#define timer1_count
//#define timer1_gate
//#define timer1_model 1

#ifdef USE_TIMER
void timer_init(void)
{
	/* timer0 */
#ifdef TIMER0_COUNT
	TMOD = TMOD | T0_CT;
#endif

#ifdef TIMER0_GATE
	TMOD = TMOD | T0_GATE;
#endif

#if (TIMER0_MODEL == 1) || (TIMER0_MODEL == 3) 
	TMOD = TMOD | T0_M0;
#endif

#if (TIMER0_MODEL == 2) || (TIMER0_MODEL == 3) 
	TMOD = TMOD | T0_M1;
#endif

	/* timer1 */
#ifdef TIMER1_COUNT
	TMOD = TMOD | T1_CT;
#endif

#ifdef TIMER1_GATE
	TMOD = TMOD | T1_GATE;
#endif

#if (TIMER1_MODEL == 1) || (TIMER1_MODEL == 3) 
	TMOD = TMOD | T1_M0;
#endif

#if (TIMER1_MODEL == 2) || (TIMER1_MODEL == 3) 
	TMOD = TMOD | T1_M1;
#endif

}
#endif

/* init uart */ 
//#define FOSC 12000000
//#define SMODX2
//#define BAUD 9600 

//#define UART_REN
//#define UART_MODE 0 
//#define UART_MODE_1
//#define UART_MODE 2 
//#define UART_MODE 3 
#ifdef USE_UART
void uart_init(void)
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

#ifdef TIMER1_MODEL
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
#endif


/* init interrupt */
//#define ISR_INT0
//#define ISR_INT0_EDGE
//#define ISR_INT0_LEVER 
//#define ISR_INT0_PR 0

//#define ISR_INT1
//#define ISR_INT1_EDGE
//#define ISR_INT1_LEVER 
//#define ISR_INT1_PR 0

//#define ISR_TIMER0
//#define ISR_TIMER0_PR 0

//#define ISR_TIMER1
//#define ISR_TIMER1_PR 0

//#define ISR_UART
//#define ISR_UART_PR 0
/* sfr IPH can not access by bit */
#define PX0H 0x01
#define PT0H 0x02
#define PX1H 0x04
#define PT1H 0x08
#define PSH  0x10

#ifdef USE_IR 
void ir_init()
{
	EA = 1;

	/* ir 0 int0 */
#ifdef ISR_INT0
	EX0 = 1;
	
	/* trigger */
#ifdef ISR_INT0_EDGE
	IT0 = 1;
#endif

#ifdef ISR_INT0_LEVER
	IT0 = 0;
#endif
	/* priority */
#if (ISR_INT0_PR == 1)||(ISR_INT0_PR == 3)
	PX0 = 1;
#endif

#if (ISR_INT0_PR == 2)||(ISR_INT0_PR == 3)
	IPH = IPH | PX0H;
#endif	
#endif

	/* ir 1 timer0 */
#ifdef ISR_TIMER0
	ET0 = 1;

	/* priority */
#if (ISR_TIMER0_PR == 1)||(ISR_TIMER0_PR == 3)
	PT0 = 1;
#endif

#if (ISR_TIMER0_PR == 2)||(ISR_TIMER0_PR == 3)
	IPH = IPH | PT0H;
#endif
#endif	

	/* ir 2 int1 */
#ifdef ISR_INT1
	EX1 = 1;

	/* trigger */ 
#ifdef ISR_INT1_EDGE
	IT1 = 1;
#endif
	
#ifdef ISR_INT1_LEVER
	IT1 = 0;
#endif

	/* priority */
#if (ISR_INT1_PR == 1)||(ISR_INT1_PR == 3)
	PX1 = 1;
#endif

#if (ISR_INT1_PR == 2)||(ISR_INT1_PR == 3)
	IPH = IPH | PX1H;
#endif	
#endif

	/* ir 3 timer1 */
#ifdef ISR_TIMER1
	ET1 = 1;

	/* priority */
#if (ISR_TIMER1_PR == 1)||(ISR_TIMER1_PR == 3)
	PT1 = 1;
#endif

#if (ISR_TIMER1_PR == 2)||(ISR_TIMER1_PR == 3)
	IPH = IPH | PT1H;
#endif
#endif	

	/* ir 4 uart */
#ifdef ISR_UART
	ES1 = 1;

	/* priority */
#if (ISR_UART_PR == 1)||(ISR_UART_PR == 3)
	PS = 1;
#endif

#if (ISR_UART_PR == 2)||(ISR_UART_PR == 3)
	IPH = IPH | PSH;
#endif
#endif
}
#endif
