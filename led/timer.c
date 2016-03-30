#include "board.h"
#include "stdlib.h"

extern void (* const TaskFuction[3])(void);
extern volatile uint16 RunFunc;
extern uint16 FuncAddr[3];

volatile uint8 random = 123;
volatile uint8 NextTask = 0;
volatile uint8 Ticksum = 0; 

void init_timer0()
{
	/* time0 16bit */
	TMOD = TMOD & 0xf1;
	TMOD = TMOD | 0x01;
	
	/* enable interrupt */
	EA = 1;
	ET0 =1;

	/* run immediately */	
	TR0 = 1;	

}

#define SWTICH_BY_RAND
void OStickISR (void) __interrupt (1) __using (0) 
{

	/* check count */
	if (Ticksum != TICK_TIMER_SHARING) {
		Ticksum ++;	
		return;
	}
	Ticksum = 0;

#ifdef SWTICH_BY_RRS		
	RunFunc = FuncAddr[NextTask++];
	if (NextTask == 3) NextTask =0;	
#elif defined(SWTICH_BY_RAND)
	random = random * random;
	NextTask = random % 3;
	RunFunc = FuncAddr[NextTask];
#endif

	/* copy func addr to stack */
	__asm
	mov sp,__start__stack
	mov r0,#_RunFunc
	mov a,@r0
	push acc
	mov r0,#_RunFunc + 1
	mov a,@r0
	push acc
	reti
	__endasm;

}
