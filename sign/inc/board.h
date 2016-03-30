#include <8051.h>

/* asm */
#define NOP __asm nop __endasm

/* type */
#define uint8 unsigned char
#define uint16 unsigned int

/* gpio */
#define MOSIO P3_4
#define R_CLK P3_5
#define S_CLK P3_6

#define IRIN P3_2

