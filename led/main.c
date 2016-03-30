#include "board.h"
#include "timer.h"

void TaskA(void);
void TaskB(void);
void TaskC(void);

void (* const TaskFuction[3])(void) = {TaskA,TaskB,TaskC};
uint16 FuncAddr[3];
volatile uint16 RunFunc;

void main(void)
{
	init_timer0();

	/* copy Task .code address to ram */
	FuncAddr[0] = (uint16)(TaskA);
	FuncAddr[1] = (uint16)(TaskB);
	FuncAddr[2] = (uint16)(TaskC);

	P0 = LED_INIT;

	while(1) {
		NOP;
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

#pragma nooverlay
void TaskA(void) 
{
	uint8 i;

	while(1) {
		for(i = 0;i < 8;i++) {
			P0 = P0 >> 1;
			if (P0 == 0) 
				P0 = P0 | 0x80;
			Delay1ms(200);
		} 	
	}
}

#pragma nooverlay
void TaskB(void)
{
	uint8 i;	

	while(1) {
		for(i = 0;i < 8;i++) {
			P0 = P0 << 1;
			if(P0 == 0)P0 = P0 | 0x01;
			Delay1ms(200);
		}
	}
}

#pragma nooverlay
void TaskC(void)
{
	uint8 temp;

	while(1) {
		temp = P0;

		P0 = 0x00;
		Delay1ms(200);
		P0 = temp;	
		Delay1ms(200);
	}
}



