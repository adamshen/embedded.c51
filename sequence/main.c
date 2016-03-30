#include "board.h"

#include "stdlib.h"
 
#include "i2c.h"
#include "uart.h"

/* struct def */
typedef struct s_block {
struct s_block *next;
uint8 MinNum;
uint8 MinNumIndex;
}s_block; 

/* global variable */
__idata uint8 buff[BlockSize];

/* func declare */
void s_insert(__idata uint8 array[],int n);

void write_randnum_to_eeprom()
{
	uint8 i;	
	uint8 addr,data;
	
	srand(9);
	for (i = 0;i < TotalSize;i++) {
		addr = i + ADDR;
		data = (uint8)(rand());
		At24c02Write(addr,data);
	}

}


void sequence_each_block()
{
	uint8 i,addr,data;
	uint8 BlockNum;
	
	for (BlockNum = 0;BlockNum < 4;BlockNum++) {
		for (i = 0;i < BlockSize;i++) {
			addr = i + BlockSize * BlockNum + ADDR;
			buff[i] = At24c02Read(addr);
		}


		/* sequece each block */
		s_insert(buff,BlockSize);

		/* write back to e2prom */
		for (i = 0;i < BlockSize;i++) {
			addr = i + BlockSize * BlockNum + ADDR;

			At24c02Write(addr,buff[i]);
			data = At24c02Read(addr);

			if (buff[i] != data) {
				/* check i2c write */							
			}
		}
		
		
	}
}


s_block* min_in_block(s_block block[],uint8 n)
{
	uint8 i;
	uint8 p = 0;

	for(i = 1;i < n;i++) {
        	if (block[p].MinNum > block[i].MinNum) p = i;
    	}

	return &block[p];
	
} 


void s_insert(__idata uint8 array[],int n)
{
	char low,high,mid;
	char i,j;
	uint8 num;
	
	for (i = 1;i < n;i++) {

		low = 0;
		high = i-1;

	 	while (low <= high) {
			mid = (low + high) / 2;
			if (array[mid] > array[i]) {
				high = mid - 1;
			} else {
				low = mid + 1;	
			}
		}

		num = array[i];


		for (j = i-1;j >= low;j--) {
			array[j+1] = array[j];
		}

		array[low] = num;	
	} 
}

void main(void)
{
	uint8 i;
	uint8 BlockNum;
	uint8 addr,data;

	s_block block[4];
	s_block *p;
		
	init_uart();

	write_randnum_to_eeprom();
	sequence_each_block();

	/* init s_block.minnum */
	for (BlockNum = 0;BlockNum < 4;BlockNum++) {
		if (BlockNum == 3)
			block[BlockNum].next = NULL;
		else
			block[BlockNum].next = &block[BlockNum+1];

		block[BlockNum].MinNumIndex = 0;
		addr = block[BlockNum].MinNumIndex + BlockNum * BlockSize + ADDR;
		block[BlockNum].MinNum = At24c02Read(addr);
	}

	for (i = 0;i < TotalSize;i++) {

		p = min_in_block(block,4);
		addr = i + ADDR;

		At24c02Write(addr, p->MinNum);

		data = At24c02Read(addr);

		if (p->MinNumIndex == BlockSize - 1) 
			p->MinNum = U8MAX;
		else 
			p->MinNumIndex++;	

		addr = p->MinNumIndex + i * BlockSize + ADDR;

		/* issue : sometimes when it reads specific addr 
			   the 24C16 retrun wrony value 
			   fix it later
		*/ 
			   	
		p->MinNum = At24c02Read(addr);
	
	}

	/* check */
	for (i = 0;i < TotalSize;i++) {
		data = At24c02Read(i + ADDR);
		uart_send_byte(data);			
	} 

	while(1);
}


