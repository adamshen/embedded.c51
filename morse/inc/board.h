#include <8051.h>

/* tpye */
#define uint8 unsigned char
#define uint16 unsigned int

/* key */
#define GPIO_KEY P1
#define NO_KEY_PRESS 0xf0

/* beer */
#define BEER P3_0
#define WARN 4

/* morse decode */
#define DOT 0
#define DASH 1
#define LETTER 2
#define WORD 3

#define MAX_INPUT 5
#define SPACE 0x20

#define BUFF_INIT "     "

/* uart */
#define USE_UART
#define UART_MODE_1
#define FOSC 12000000L
#define BAUD 9600
#define SMODX2


