
#ifndef SYSTEM_CONSTANTS
#define SYSTEM_CONSTANTS



//////////////////////////// Bit Configuration //////////////////////
// started counting from 0. eg. 0b01-> zeros bit
static const  int NOBIT = 0;
static const  int ZEROSBIT = 0x1;
static const  int FIRSTBIT = 0x2;
static const  int SECONDBIT= 0x4;
static const  int THIRDBIT = 0x8;
static const  int FOURTHBIT = 0x10;
static const  int FIFTHBIT = 0x20;
static const  int SIXTHBIT = 0x40;
static const  int SEVENTHBIT =0x80;





// frequently used variables 
#define	bool _Bool
#define byte uint8_t
#define	MSBFIRST 1
#define LSBFIRST 0

#define screenWidth 2000
#define outerScreenWidth 32
#define innerScreenWidth 16 


// frequently used constants
#define true 1
#define false  0

#define NUMBER_OF_BOARD 1																			// number of boards
#define NUMBER_OF_LED_PER_BOARD 16																	// holds those three internal LED's /BGR/ -> AS ONE
#define NUMBER_OF_SUBLED_PER_LED 3*2																// 2 since each array should hold 8bits -> total of 16 with longer array
#define NUMBER_OF_LED 	NUMBER_OF_BOARD*NUMBER_OF_LED_PER_BOARD*NUMBER_OF_SUBLED_PER_LED			// Total number of arrays being used



// setting up WIFI
const char SSID[] = "SprintWiFia-1EE31B";
const char PW[] = "0339985a";

// Modes need to be set
const char CIPMUX = '1';  // we are using TCP
const char CWMODE = '1';  // we are choosing it to be station  2 is for APmode


volatile byte counter=0;



#endif