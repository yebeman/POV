#ifndef WIFI_LOGIC
#define WIFI_LOGIC

/*****
	TITLE: Contains WIFI module Initialization and Communication 
	TARGET: OUTPUT ==>
	AT version:0.60.0.0(Jan 29 2016 15:10:17)
	SDK version:1.5.2(7eee54f4)
	Ai-Thinker Technology Co. Ltd.
	May  5 2016 17:30:30
	OK
	
	DEPENDENCY: UART_LOGIC
	
	
	
	YEBE
*/

// we are using 9600 as boudrate so
// from old iterations of the manual
// temp place -> will be moved from current position
#define FOSC F_CPU
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

//DEFINE KEYWORDS HERE
const char _OK[] = "OK";
const char _Ready[] = "ready";
const char _ip[] = "192.";
const char _carrot[] = ">";
const char _sendok[] = "SEND OK";
const char _linkdisc[] = "CLOSED";
const char _noData[] = "different";


char goToLink[150];
byte goToLink_size=0;
char ipAddress[16];
char current_temp[5];


const char tempURL[] = "GET https://api.thingspeak.com/apps/thinghttp/send_request?api_key=U7WRMZZBOGKL5RSK HTTP/1.0\r\n\r\n";
//keywords for current temp
const char _temp_Query[] = "query";



#include "WIFI_LOGIC.c"
#endif