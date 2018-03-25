/*
 * POV.c
 *
 * Created: 4/3/2016 1:51:52 PM
 * Author : yebeman
 */ 

#include "CONFIGURATION_INDEX.h"
#include "SYSTEM_CONSTANTS.h"
#include "GLOBAL_TIME_ALGORITHM.h"
#include "UART_LOGIC.h"
#include "WIFI_LOGIC.h"
#include "MOTOR_CONTROL_LOGIC.h"
#include "RPM_COUNTER_ALGORITHM.h"
#include "SPI_LOGIC.h"
#include "TLC5955_ALGORITHM.h"
#include "LED_LOGIC.h"

int main(void)
{
	// wait for a lil bit
	_delay_ms(200);	


	
	/////////////////////////////////////////////////////////////////////////////////
	// initialize Global Time Counter
	initTime();
	sei();
	/////////////////////////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////////////////////
	// Initialize UART -> WIFI Communication
	USART_Init(MYUBRR);
	_delay_ms(500);
	
	if (WIFI_ACTIVE){
		// Initialize WIFI module
		areWeCool();
		_delay_ms(1000);
	
		resetWIFI();
		_delay_ms(3000);
	
		setMode();
		_delay_ms(2000);
		
		while(!handShake()){
			_delay_ms(1000);
		}
		_delay_ms(10000);
	
		registerdID();
		_delay_ms(5000);
	
		while(!freeHugForEveryone());
		_delay_ms(5000);
		
		// reset timer incase we need more time
		resetTime();
		while(!getTemp()){
			_delay_ms(100);
			} ;
		showTemp();
		//	USART_Print(savedUartData);
			//	USART_Print(checkTopChar);
		}
	/////////////////////////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////////////////////
	// initialize Motor - IR
	if (MOTOR_ACTIVE){
	initMotor();
	motorFunction(true);
	}
	/////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////
	// initialize RPM COUNTER -> Angular Speed  - Counts RPM
	if(RPM_ACTIVE)
	initRPMCounter();
	/////////////////////////////////////////////////////////////////////////////////

	// SPI CONFIGURATION
	initTLCVariables();

	// adjust GSDL -> adjustedGSDL[][][] for ease of use.
	adjustGSDL();
	

	
	// start timing high frequency activities
	resetTime();
	resetTimer();
	resetRPMTime();
	uint16_t oldT =  currTime_S;


	
	
    while (true) 
    {
	
					// ready for printing
					flushTLC();
				spi_tranceiver(gsMode);
					
	//if(msRevPeriod != 0){
	
	//writeChar(0,0,'!', 100, 0xFFFF,0xFFFF,0xFFFF);
	//writeChar(0,0,'B', msRevPeriod, 0xFFFF,0x00,0x00);
	
	//}
	

	switch (currTime_S - oldT)
	{
		case 1:
			
		clearFrame();
		
		//writeChar(1,0,'~', 1000, 0xFFFF,0x0000,0x0000);
		//writeChar(0,0,'~', 1000, 0xFFFF,0x0000,0x0000);
		setSubLED(0, 0, 0, 0xFFFF);
		if(oldT%2)
		{		//setPixel(1,4,0x0000,0x0000,0xFFFF);
		}
		else
			{//	setPixel(2,5,0x0000,0x0000,0xFFFF);
			}
		oldT = currTime_S;
		break;
		default:
		break;
	}
	

  

		// update screen with new information
		updateScreen();

	} 
	
}
 

/*
	// reset if no interrupt occurred during
	if(!interrOccurred){
	RPM = 0;	}
	interrOccurred= false;
	
	char numberCharBuff[20];
	itoa(RPM,numberCharBuff,10);
	USART_Print(numberCharBuff);
	USART_Print("\r\n");
	
	
	*/

