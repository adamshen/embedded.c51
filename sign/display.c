#include "board.h" 
#include "ledmap.h"
  
uint8 hc595_data_buff[4];

void HC595_Send_Data()
{
	uint8 bit,byte;

	for(byte = 0;byte < 4;byte++) {
		for(bit = 0;bit < 8;bit++) {
			MOSIO = hc595_data_buff[byte] >> 7;
			hc595_data_buff[byte] <<= 1;

			S_CLK = 0;
			S_CLK = 1;		
		}
	}

	R_CLK = 0;
	R_CLK = 1;
	R_CLK = 0;

}

void HC595_Set_Row(uint8 line,int data)
{
	hc595_data_buff[0] = ~(data & 0xff);
	hc595_data_buff[1] = ~(data >> 8);
	hc595_data_buff[2] = row_mask[line] >> 8;
	hc595_data_buff[3] = row_mask[line] & 0xff;
	
	HC595_Send_Data(); 
}

void Show_Sign(uint8 sign)
{
	uint8 i;
	uint8 line;

	for(i = 0;i < 80;i++) {
		for(line = 0;line < 16; line++) {
			HC595_Set_Row(line,map[sign][line]);
		}
	}

}
