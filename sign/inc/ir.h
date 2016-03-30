/* function table */
extern void Ir_init();
extern void Read_ir(void) __interrupt (0) __using (0);

/* globle variable */
extern volatile uint8 irvalue;

