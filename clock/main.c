#include "board.h"

#include "display.h"
#include "ds1302.h"

/* 0~9 A~F */
__code uint8 Dig_Code[17] = {
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void init_board()
{
	Ds1302_Init();
}

void Dig_Show_Time()
{
	DisplayBuff[0] = Dig_Code[RtcTime[HOUR]/16];
	DisplayBuff[1] = Dig_Code[RtcTime[HOUR]&0x0f];				 
	DisplayBuff[2] = IN_LINE;
	DisplayBuff[3] = Dig_Code[RtcTime[MINUTE]/16];
	DisplayBuff[4] = Dig_Code[RtcTime[MINUTE]&0x0f];	
	DisplayBuff[5] = IN_LINE;
	DisplayBuff[6] = Dig_Code[RtcTime[SECOND]/16];
	DisplayBuff[7] = Dig_Code[RtcTime[SECOND]&0x0f];

	Dig_Display();
}

void Dig_Show_Date()
{
	uint16 i;

	DisplayBuff[0] = Dig_Code[RtcTime[YEAR]/16];
	DisplayBuff[1] = Dig_Code[RtcTime[YEAR]&0x0f];				 
	DisplayBuff[2] = IN_LINE;
	DisplayBuff[3] = Dig_Code[RtcTime[MONTH]/16];
	DisplayBuff[4] = Dig_Code[RtcTime[MONTH]&0x0f];	
	DisplayBuff[5] = IN_LINE;
	DisplayBuff[6] = Dig_Code[RtcTime[DAY]/16];
	DisplayBuff[7] = Dig_Code[RtcTime[DAY]&0x0f];

	for (i = 0;i < 1500;i++)
		Dig_Display();
}

void main()
{
	
	init_board();

	while(1) {
		Ds1302_Read_Time();
		Dig_Show_Time();

		if (Key_Scan() == KEY1_PRESSED)
			Dig_Show_Date();	
	
		/* unfortunately 18b20 in the board was missed */
	//	if (key_Scan() == KEY2_PRESSED)
	//		Dig_Show_Temp();		
	}
}	
