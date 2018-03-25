#ifndef UART_LOGIC
#define UART_LOGIC

/*****
	TITLE: Contains UART initialization and Communication
	TYPE: Interrupt /External/ & Timer 
	SUBTYPE: Int/NO:0, Trig:0->1/ 
	PORT: PORT:D2
	
	YEBE
*/




// setting up buffer size
#define  RX_BUFFER_SIZ 2000

volatile char rxBuffer[RX_BUFFER_SIZ];
volatile int rxReadCurrPosition = 0;
volatile int rxWriteCurrPosition = 0;

volatile char savedUartData[RX_BUFFER_SIZ];
volatile int  savedUartEnd = 0;

int timeoutStart;

#include "UART_LOGIC.c"
#endif