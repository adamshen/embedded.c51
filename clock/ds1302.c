#include "board.h"

/* second minute hour day month week year*/
uint8 __code RtcReadAddr[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
uint8 __code RtcWriteAddr[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

/* init time 2015-5-20 13:14:00 (BCD code)*/
uint8 RtcTime[7] = {0x00, 0x14, 0x13, 0x20, 0x05, 0x02, 0x15};

void Ds1302_Write(uint8 addr, uint8 data)
{
	uint8 i;

	RST = 0;
	NOP;

	SCLK = 0;
	NOP;

	/* start write */
	RST = 1;
	NOP;

	/* send address */
	for (i = 0;i < 8;i++) {

		DSIO = addr & 0x01;
		addr >>= 1;

		SCLK = 1;
		NOP;

		SCLK = 0;
		NOP;
	}

	/* send data */
	for (i = 0;i < 8;i++) {

		DSIO = data & 0x01;
		data >>= 1;

		SCLK = 1;
		NOP;

		SCLK = 0;
		NOP;	
	}	

	/* finish */
	RST = 0;
	NOP;

}

uint8 Ds1302_Read(uint8 addr)
{

	uint8 i;
	uint8 data = 0;

	RST = 0;
	NOP;

	SCLK = 0;
	NOP;

	/* start read */
	RST = 1;
	NOP;

	/* send address */
	for (i = 0;i < 8;i++) {

		DSIO = addr & 0x01;
		addr >>= 1;

		SCLK = 1;
		NOP;

		SCLK = 0;
		NOP;
	}

	NOP;

	/* read data */
	for (i = 0;i < 8;i++) {

		data = data >> 1;
		if (DSIO == 1) data = data|0x80;

		SCLK = 1;
		NOP;

		SCLK = 0;
		NOP;

	}

	/* finish */
	RST = 0;
	NOP;

	SCLK = 1;
	NOP;

	DSIO = 0;
	NOP;

	DSIO = 1;
	NOP;

	return data;	

}

void Ds1302_Init()
{
	uint8 i;

	/* turn off write-protect */
	Ds1302_Write(0x8E,0X00);

	for (i = 0;i < 7;i++) {
		Ds1302_Write(RtcWriteAddr[i],RtcTime[i]);	
	}

	/* turn on write-protect */
	Ds1302_Write(0x8E,0x80);	
}

void Ds1302_Read_Time()
{
	uint8 i;

	for (i = 0;i < 7;i++) {
		RtcTime[i] = Ds1302_Read(RtcReadAddr[i]);
	}
}

