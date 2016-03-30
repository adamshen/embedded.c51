#include "board.h"

/* short delay for i2c */
void delay2Us(uint8 t)
{
	while(--t);
}

void delay1ms(uint8 t)
{
	while (t--) {
		delay2Us(245);
		delay2Us(245);
	}
}

/* start i2c transfer */
/* SCL = 1 & SDA from 1 to 0 */
void I2C_Start()
{
	I2C_SDA = 1;
	delay2Us(10);

	I2C_SCL = 1;
	delay2Us(10);

	I2C_SDA = 0;
	delay2Us(10);

	/* prepare for transfer */
	I2C_SCL = 0;			
	delay2Us(10);		
}

/* end i2c transfer */
/* SCL = 1 & SDA from 0 to 1 */
void I2C_Stop()
{
	I2C_SDA = 0;
	delay2Us(10);

	I2C_SCL = 1;
	delay2Us(10);

	I2C_SDA = 1;
	delay2Us(10);		
}

/* i2c send byte */
uint8 I2C_SendByte(uint8 dat, uint8 ack)
{
	uint8 i = 0;
			
	for (i = 0; i < 8; i++) {
		I2C_SDA = dat >> 7;
		dat = dat << 1;
		delay2Us(10);
		
		/* send bit */
		I2C_SCL = 1;
		delay2Us(10);

		I2C_SCL = 0;
		delay2Us(10);
	}

	/* wait slave ack */
	I2C_SDA = 1;
	delay2Us(10);

	I2C_SCL = 1;
	/* slave clr_sda */
	while(I2C_SDA && (ack == 1))
	{
		if (i > 100) {
			I2C_SCL = 0;
			delay2Us(10);
			return 0;
		}
		i++;
	}

	I2C_SCL = 0;

	delay2Us(10);
 	return 1;		
}

/* i2c read byte */
uint8 I2C_ReadByte()
{
	uint8 i = 0,dat = 0;
	I2C_SDA = 1;	
	delay2Us(10);

	for (i = 0; i < 8; i++) {
		I2C_SCL = 1;
		delay2Us(10);

		dat <<= 1;
		dat |= I2C_SDA;
		delay2Us(10);

		I2C_SCL = 0;
		delay2Us(10);
	}

	delay1ms(5);	
	return dat;		
}

/* page switch not supply */
/*  chip addr
  	B7 ~ B4 1010
	B3 ~ B1 addr
	B0 read/write

    24c02 write sequence
	START
	SLAVE ADDRESS--ack
	BYTE ADDRESS--ack
	DATA--ack
	STOP
*/
void At24c02Write(uint8 addr,uint8 dat)
{
	I2C_Start();

	/*select chip*/
	I2C_SendByte(0xa0, 1);

	/* send address */
	I2C_SendByte(addr, 1);

	/* send date */
	I2C_SendByte(dat, 1);

	I2C_Stop();
	
	delay1ms(5);
}


/*  24c02 read sequence
	START
	SLAVE ADDRESS--ack
	BYTE ADDRESS--ack
	START
	SLAVE ADDRESS--ack
	DATA--noack
	STOP
*/
uint8 At24c02Read(uint8 addr)
{
	uint8 data;

	I2C_Start();

	I2C_SendByte(0xa0, 1);
	I2C_SendByte(addr, 1);

	I2C_Start();
	I2C_SendByte(0xa1, 1);
	data = I2C_ReadByte();

	I2C_Stop();
	return data;	
}
