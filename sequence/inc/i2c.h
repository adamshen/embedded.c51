/* function table */
extern void I2C_Start();
extern void I2C_Stop();

extern uint8 I2C_SendByte(uint8 dat, uint8 ack);
extern uint8 I2C_ReadByte();

extern At24c02Write(uint8 addr,uint8 dat);
extern uint8 At24c02Read(uint8 addr);



