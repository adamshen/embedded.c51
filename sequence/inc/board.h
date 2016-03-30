#include <8051.h>

/* type */
#define uint8 unsigned char
#define uint16 unsigned int

/* gpio */
#define I2C_SCL P2_1
#define I2C_SDA P2_0

/* uart */
#define USE_UART
#define UART_MODE_1
#define FOSC 12000000L
#define BAUD 4800
#define SMODX2

/* sequence */
#define ADDR 11
#define TotalSize 64	
#define BlockSize 16
#define U8MAX 0xff
