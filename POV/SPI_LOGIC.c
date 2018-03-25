/*****
	
	YEBE
	
******/
///////////////////////////////////////////////////////////////////////////////////////////////
// SPI COMMUNICATION -
// 
//////////////


 void setDataModed(uint8_t dataMode) {
	 SPCR = (SPCR & ~SPI_MODE_MASK) | dataMode;
 }

 void setClockDividerd(uint8_t clockDiv) {
	 SPCR = (SPCR & ~SPI_CLOCK_MASK) | (clockDiv & SPI_CLOCK_MASK);
	 SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((clockDiv >> 2) & SPI_2XCLOCK_MASK);
 }


 void setBitOrderd(uint8_t bitOrder) {
	 if (bitOrder == LSBFIRST) SPCR |= _BV(DORD);
	 else SPCR &= ~(_BV(DORD));
 }
 
// Initialize SPI Master Device (with SPI interrupt)
void spi_init_master (void)
{
	// Set MOSI, SCK as Output
	// port 7 and 5 are now set
	DDRB=(1<<PORTB5)|(1<<PORTB7)|(1<<PORTB4);
	
	// Enable SPI, Set as Master
	// Prescaler: Fosc/16, Enable Interrupts
	//The MOSI, SCK pins are as per ATMega8
	SPCR=(1<<SPE)|(1<<MSTR);// 010100000//
	
	// Enable Global Interrupts
}

//Function to send and receive data for both master and slave
inline static uint8_t spi_tranceiver (uint8_t data)
{
	// Load data into the buffer
	SPDR = data;
	
	asm volatile("nop");
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF)));
	
	// Return received data
	return(SPDR);
}


///////////////////////////////////////////////////////////////////////////////////////////////