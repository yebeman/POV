#ifndef TLC5955_ALGORITHM
#define TLC5955_ALGORITHM

/*****
	TITLE: TLC5955 SETUP & COMMUNICATION
	DEPENDENCY: SPI_LOGIC , LED_LOGIC
	SET UP: GSCLK
	
	
	YEBE
*/




byte cdlFill[1] = {0x00};  //5bits used
byte cdlDC[48]; //7bits used
byte cdlMC[3];  //3bits used
byte cdlBC[3];  //7bits used
byte cdlFC[1];  //5bits used

byte outBuffer[97];

byte CDL[47];    // configuration bytes

byte cdMode = 0x01; //FF/01=CD
byte gsMode = 0x00; //00=GS
byte cdlMode = 0x96; //mode must be FF followed by 96 for control data. => pg17

//

long GSDL[NUMBER_OF_LED];

// MUST HAVE DEFINITIONS -> makes life easier 
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


// bit manipulation bits
int cdlPos=0;
int dcPos=0;
int fillPos=0;
int mcPos=0;
int bcPos=0;
int fcPos=0;


#include "TLC5955_ALGORITHM.c"
#endif
