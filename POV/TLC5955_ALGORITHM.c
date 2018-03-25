/*****
	
	YEBE
	
******/
///////////////////////////////////////////////////////////////////////////////////////////////
// TLC5955 SETUP & COMMUNICATION -
// 
//////////////

// Setting up GSCLK
// counts up to 65538
// CTC - 4MHz with 2k div and max of 2k RPM
void initGSCLKPWM(){
	DDRD |= (1 << PD5);
	TCCR1A |= (1<<COM1A0);
	OCR1A = 1;
	TCCR1B |= (1 << ICNC1) | (1<<CS10) | (1<<WGM12);
}



void flushTLC(){
	for (byte i=0;i<NUMBER_OF_LED;i++){
		spi_tranceiver(0x00);
	}
}

void latch_tlc() {
	_delay_ms(10);
	PORTB = (1 << PORTB4);
	_delay_ms(10);
	PORTB = (0 << PORTB4);
	_delay_ms(10);
}


// need to create the Control Data sequence in the required format
// the orders should follow page 'Register and Data Latch Configuration' on PDF
void mergeControlBits() {
	// fill values to CDL
	//cdlFill[1]
	CDL[cdlPos] = 0;

	// DC values to CDL
	// cdlDC[1]
	for (int bitPos=5;bitPos<341;bitPos++) {
		cdlPos = bitPos/8;
		dcPos = (bitPos-5)/7;
		bitWrite(CDL[cdlPos], 7-bitPos%8, bitRead(cdlDC[dcPos], 6-((bitPos-5)%7)));
	}

	//append the MC values to CDL
	//cdlMC[3]
	for (int bitPos=341;bitPos<350;bitPos++) {
		cdlPos = bitPos/8;
		mcPos = (bitPos-341)/3;
		bitWrite(CDL[cdlPos], 7-bitPos%8, bitRead(cdlMC[mcPos], 2-((bitPos-341)%3)));
	}
	
	//append the BC values to CDL
	//cdlBC[3]
	for (int bitPos=350;bitPos<371;bitPos++) {
		cdlPos = bitPos/8;
		bcPos = (bitPos-350)/7;
		bitWrite(CDL[cdlPos], 7-bitPos%8, bitRead(cdlBC[bcPos], 6-((bitPos-350)%7)));
	}
	
	//append the FC values to CDL
	//cdlFC[1]
	for (int bitPos=371;bitPos<376;bitPos++) {
		cdlPos = bitPos/8;
		fcPos = (bitPos-371)/5;
		bitWrite(CDL[cdlPos], 7-bitPos%8, bitRead(cdlFC[fcPos], 4-((bitPos-371)%5)));
	}
}

void printCDL(){
	
	//set mode for accessing control bits
	spi_tranceiver(cdMode);
	spi_tranceiver(cdlMode);

	// print controls
	for (int i=0; i < 47; i++){
		spi_tranceiver(CDL[i]);
	}

	latch_tlc();
}

//Initialize all variable to some predefined level.
void initTLCVariables(void){

	//All LEDs Full off
	for (int i=0; i < NUMBER_OF_LED; i++){
		GSDL[i] = 0x00;    
	}

	//preset default values
	for (int i=0; i < 47; i++){
		CDL[i] = 0x00;
	}

	//set DC halfway
	for (int i=0; i < 48; i++){
		cdlDC[i] = 0x8;
	}
	
	//set MC halfway
	for (int i=0; i < 3; i++){
		cdlMC[i] = 0x8;
	}
	
	//set BC halfway
	for (int i=0; i < 3; i++){
		cdlBC[i] = 0x8;
	}
	
	//auto display repeat - page 23
	cdlFC[0] = 0x1F;
	
	// set up latch 'SS'
	DDRB |= (1 << PB4);
	PORTB = (0 << PB4);
	
	// setup GSCLK
	initGSCLKPWM();
	
	setDataModed(SPI_MODE0);
	setClockDividerd(SPI_CLOCK_DIV4);
	setBitOrderd(MSBFIRST);
	spi_init_master();
	
	
	//Setup the TLC5955 once.
	mergeControlBits();
	printCDL();
}

///////////////////////////////////////////////////////////////////////////////////////////////