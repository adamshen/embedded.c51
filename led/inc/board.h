#include <8051.h>

/* type */
#define uint8 unsigned char
#define uint16 unsigned int

/* gpio */
#define GPIO_LED P0
#define LED_INIT 0x01

/* asm */
#define NOP __asm nop __endasm

/* task switch */
#define TICK_TIMER_SHARING 100

