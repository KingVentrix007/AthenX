#include "../include/io.h"
#include "../include/pit.h"
unsigned read_pit_count(void) {
	unsigned count = 0;
 
	// Disable interrupts
	cli();
 
	// al = channel in bits 6 and 7, remaining bits clear
	output_bytes(0x43,0b0000000);
 
	count = input_bytes(0x40);		// Low byte
	count |= input_bytes(0x40)<<8;		// High byte
 
	return count;
}

void set_pit_count(unsigned count)
{
    cli();
    out_bytes(0x40,count&0xFF);
    out_bytes(0x40,(count&0xFF00) >>8 );
    return;
    
}

