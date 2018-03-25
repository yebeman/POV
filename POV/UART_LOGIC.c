/*****
	
	YEBE
	
******/
///////////////////////////////////////////////////////////////////////////////////////////////
// UART COMMUNICATION -
// Currently Using: Interrupt /External/ & Timer - Int/NO:0, Trig:0->1/ - PORT:D2
//////////////

void USART_Init( unsigned int baud )
{
	// disable interrupts
	cli();
	
	/* Set baud rate */
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	/* Set frame format: 8data*/
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	
	// reenable interrupts
	sei();
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}



void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

// This will enable us send collective of chars
void USART_Print(const char *send)
{
	// go thorough each char
	while (*send) {
		USART_Transmit(*send++);
	}
}



// doesn't remove it but gives u a sneak peak => trailer
char checkTopChar(void){
	char recivedChar = NULL;
	
	if(rxReadCurrPosition != rxWriteCurrPosition){
		recivedChar = rxBuffer[rxReadCurrPosition];
	}
	
	return recivedChar;
}

char getcharcter(void){
	
	char recivedChar = NULL;
	
	if(rxReadCurrPosition != rxWriteCurrPosition){
		recivedChar = rxBuffer[rxReadCurrPosition];
		rxReadCurrPosition++;
		
		if(rxReadCurrPosition >= RX_BUFFER_SIZ){
			rxReadCurrPosition = 0;
		}
	}
	
	return recivedChar;
}

int available(void)
{
	if(rxWriteCurrPosition > rxReadCurrPosition)
	return true;
	return false;
}



// checks if it contains a specific word
int doesContain(const char keyword[],  int timeoutVal, byte saveData){
	timeoutStart=currTime_mS;//for the timeout
	char data_in[RX_BUFFER_SIZ];
	int key_size = sizeof(keyword);//since we're going to get an extra charachter from the sizeof()
	counter = 0;
	
	// wait until all data is sent with a given timeoutValue
	// could be available and not done sending data ...
	while(!((currTime_mS - timeoutStart) > timeoutVal) ){
	};

	
	cli();

	counter = rxWriteCurrPosition;
	
	// move data to locally created variable
	for(byte i=0; i < counter; i++){
		data_in[i] = getcharcter();
	}
	
	

	if(saveData){
		for(byte i=0; i < counter; i++){
			savedUartData[i] = data_in[i];
		}
		savedUartEnd = counter;
	}

	int foundCharNumber = 0;
	for(byte i=0; i<key_size; i++){
		
		for(byte j=0; j<counter; j++){
			if(keyword[i]==data_in[j])
			{
				foundCharNumber++;
			break;}
			else continue;
			
		}
		
		if(foundCharNumber == key_size - 1 ) {
			
			rxWriteCurrPosition = 0; // objective archived. restart
			rxReadCurrPosition = 0;
			sei();
			return true;
		}
	}
	
	rxWriteCurrPosition = 0; // objective archived. restart
	rxReadCurrPosition = 0;
	sei();
	return false;
}


// issue would be filling up and being reused for a new data
ISR(USART0_RX_vect){
	rxBuffer[rxWriteCurrPosition] = UDR0;
	
	rxWriteCurrPosition++;
	
	if(rxWriteCurrPosition >= RX_BUFFER_SIZ)
	{
		rxWriteCurrPosition = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
