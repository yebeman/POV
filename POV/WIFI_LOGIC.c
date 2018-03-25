/*****
	
	YEBE
	
******/

///////////////////////////////////////////////////////////////////////////////////////////////
// WIFI COMMUNICATION - 
// Currently Using: Interrupt /External/ & Timer - Int/NO:0, Trig:0->1/ - PORT:D2
//////////////

// checks for 192 and continues saving until a '"'
void parseOutIp(void){
	
	// save init data
	ipAddress[0] = '1';
	ipAddress[1] = '9';
	ipAddress[2] = '2';
	ipAddress[3] = '.';
	
	counter = 0;
	
	
	for(byte j=0; j<savedUartEnd; j++){
		
		if(counter <= 3){
			if(_ip[counter]==savedUartData[j])
			{
				counter ++;
			}
			}else{
			if(savedUartData[j] != '\"'){
				ipAddress[counter] = savedUartData[j];
				counter++;
			}
			else break;
		}

	}
	
}

// connects online to the requested payload
// if connects, returns 1
bool connectOnline(void){
	
	USART_Print("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",80\r\n");
	
	if(doesContain(_OK,5000,0)){
		
		char numberCharBuff[20];
		
		itoa(goToLink_size,numberCharBuff,10);
		
		
		USART_Print("AT+CIPSEND=0,");
		USART_Print(numberCharBuff);
		USART_Print("\r\n");
		
		if(doesContain(_carrot,5000,0)) {
			
			for(int i=0; i<goToLink_size; i++)
				USART_Transmit(goToLink[i]);

			if(doesContain(_sendok,5000,0)) {
		 
				if(doesContain(_noData, 10000,1))				
										 return false;
				else
					return true;

			}
			else// SEND OK
				return false;

		}//got the back carrot >
		else
			return false;
	}
	else
		return false;
}

bool getTemp(void){
	counter=0;
	goToLink_size=0;
	
	// copy
	for(int i=0; i<(sizeof(tempURL)-1); i++){
		goToLink[i] = tempURL[i];
		counter++;
	}
	
	goToLink_size = counter;
	
	
	
	while(!connectOnline()){
			resetTime();
			_delay_ms(100);
		} 
	

	return true;
}

// Send just 'AT' to make sure the ESP is responding
bool areWeCool(){
	
		USART_Print("AT\r\n");
		
		if(doesContain(_OK,1000,0))
			return true;
		else
			return false;
}

// reset if prev connected 
bool resetWIFI(){
	
	USART_Print("AT+RST\r\n");
	
	if(doesContain(_Ready,2000,0))
		return true;
	else
		return false;
}

// set to station mode
bool setMode(){
	
	USART_Print("AT+CWMODE=");
	USART_Transmit(CWMODE);
	USART_Print("\r\n");
		
	if(doesContain(_OK,1000,0))
		return true;
	else
		return false;
}

// set pw and ssid
bool handShake(){
	
	USART_Print("AT+CWJAP=\"");
	USART_Print(SSID);
	USART_Print("\",\"");
	USART_Print(PW);
	USART_Print("\"\r\n");
	
	if(doesContain(_OK,2000,0))
		return true;
	else
		return false;
}

// check if IP obtained. save if any.
bool registerdID(){
	
	USART_Print("AT+CIFSR\r\n");
	
	if(doesContain(_ip,4000,1)){
		parseOutIp();
		
		//USART_Print(ipAddress);
		//USART_Print("\r\n");
		
		return true;
	}
	else
		return  false;
}

// set to multiple connection
bool freeHugForEveryone(){
	
	USART_Print("AT+CIPMUX=");
	USART_Transmit(CIPMUX);
	USART_Print("\r\n");
	
	if(doesContain(_OK,5000,0))
		return true;
	else
		return false;
}

void showTemp(){
	int index=0;
	int t=0;
	char buffer[5];
	if(getTemp())
	{
		for(int i=0; i<sizeof(savedUartData);i++)
		{
			while(savedUartData[i]==':'){
				index++;
				if(index==1){
					current_temp[t]=+savedUartData[i];
					t=t+1;
				}
				
			}
		}
		itoa(current_temp[5],buffer,10);
		USART_Print(buffer);
		//	USART_Print(current_temp);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////