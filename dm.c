#include <stdio.h>
#include <string.h>

void main() {
	unsigned int startAddress = 0;
	
	printf("Start address: ");
	scanf("%x", &startAddress);
	
	displayMemory(startAddress);
}

int displayMemory(unsigned int startAddress) {
	/*
	Function: Display Memory
	Operation: Allow the user to view the values stored in memory
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Change log:
	Produced by: Jack Walker
	*/
	
	/*Step 1 - Ask for start address*/
	/*Step 2 - Validate user input and loop if invalid*/
	/*Step 3 - Display contents of memory from the starting address to the address + 100 (if possible)*/
	
	printf("Start address: %x\n\r", startAddress);	
	printf("Display Memory\n\r");
}

