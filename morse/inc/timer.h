/* function table */
void OStickISR (void) __interrupt (1) __using (0);
extern void init_timer0();
extern void beer(uint8 cont);

/* global variable */
extern volatile uint8 frq;
