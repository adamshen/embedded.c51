#include <8051.h>

/* asm */
#define NOP __asm nop __endasm

/* tpye */
#define uint8 unsigned char
#define uint16 unsigned int

/* gpio */
#define GPIO_DIG P0

#define LSA P2_2
#define LSB P2_3
#define LSC P2_4

#define DSIO P3_4
#define RST P3_5
#define SCLK P3_6

#define KEY1 P2_6
#define KEY2 P2_7

/* dig */
#define DROP_SHADOW 0x00

/* key */
#define NO_KEY_PRESSED 0
#define KEY1_PRESSED 1
#define KEY2_PRESSED 2

/* ds1302 */ 
#define SECOND 0
#define MINUTE 1
#define HOUR 2
#define DAY 3
#define MONTH 4
#define WEEK 5
#define YEAR 6

#define IN_LINE 0x40
