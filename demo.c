#include <stdio.h>

void demo();

void main() {
	demo();
}

void demo() {	
	/*
	Function: Demo
	Operation: Demo program using a variable resistor to step a motor
	Returns: Integer error code
	Date: 25/03/2021
	Version: 1.1
	Change log:
	v1.0 - Read value on port E0 and produce an offset to delay the output on ports A0 - A3
	v1.1 - Changed offset from multiplication to addition to allow more granular control (smaller offsets for higher speed)
	Produced by: Jack Walker
	*/
	
	unsigned char *adControlStatus, *adResults1, *portA, *ddrA, portAMask, data;
	unsigned int i, delay;
	
	adControlStatus = (unsigned char*)0x30;
	adResults1 = (unsigned char*)0x31;
	
	/*Cast to pointers*/
	portA = (unsigned char *)0x00; 
	ddrA = (unsigned char *)0x01;
	*ddrA = 0xff;	
	
	/*printf("Demo\n\r");*/
	
	*adControlStatus =  0x20; /*Single continuous scan mode*/
	
	for(;;) {
		/*Wait for E0C*/
		while(((*adControlStatus) & 0x80) == 0x00); 
		
		/*printf("Data from E0 is %02x\n\r", *adResults1);*/
		
		/*Add 0xff to create delay*/
		delay = (*adResults1) + 0xff;
			
		/*printf("Delay is %04x\n\r", delay);*/
		
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		*portA = 0x01;

		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
			
		*portA = 0x03;

		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);
		
		*portA = 0x02;
				
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);
		
		*portA = 0x06;
	
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		*portA = 0x04;
		
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);		
		
		*portA = 0x0c;
		
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		data = 0x08;
				
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		*portA = 0x09;
	}
}

