#include <stdio.h>

void main() {
	/*
	Function: Demo
	Operation: Demo program using a variable resistor to step a motor
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Change log:
	Produced by: Jack Walker
	*/
	
	/*Step 1 - Start demo program using ports*/
	/*Step 2 - Set up E0 to continuous read mode to read resistance value*/
	/*Step 3 - Set up porta A0-A3 as output and set a looping output sequence*/
	/*Step 4 - Read in val on E0 and set as time delay for outputs on A0-A3*/
	
	unsigned char *adControlStatus, *adResults1, *portA, *ddrA, portAMask, data;
	unsigned int i, delay;
	
	adControlStatus = (unsigned char*)0x30;
	adResults1 = (unsigned char*)0x31;
	portA = (unsigned char *)0x00; /*Cast to pointers*/
	ddrA = (unsigned char *)0x01;
	*ddrA = 0xff;	
	
	printf("Demo\n\r");	
	
	*adControlStatus =  0x20; /*Single continuous scan mode*/
	
	for(;;) {
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/
		
		*portA = 0x01;
		
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/		
		
		*portA = 0x03;
		
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/
		
		*portA = 0x02;
				
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/
		
		*portA = 0x06;
		
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/		
		
		*portA = 0x04;
		
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/		
		
		*portA = 0x0c;
		
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/	
		
		data = 0x08;
				
		while(((*adControlStatus) & 0x80) == 0x00); /*Wait for E0C*/
		printf("Data from E0 is %02x\n\r", *adResults1);
		delay = *adResults1 * 0xff;	/*Multiply by 0xff to create delay*/
		printf("Delay is %04x\n\r", delay);
		for (i = 0; i < delay; i++);	/*Delay based on resistor value read on E0*/	
		
		*portA = 0x09;
	}
}

