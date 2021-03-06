#include <stdio.h>
#include <string.h>

void main() {
	unsigned int startAddress = 0;
	
	printf("Start address: ");
	scanf("%x", &startAddress);
	
	modifyMemory(startAddress);
}

int modifyMemory(unsigned int startAddress) {
	/*
	Function: Modify Memory
	Operation: Allow the user to modify values stored in memory
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Change log:
	Produced by: Jack Walker
	*/
	
	/*Step 1 - Ask for a start address to edit*/
	/*Step 2 - Read user input for address and prompt for new data*/
	/*Step 3 - Validate that the data is storable and store (loop if can't store)*/
	/*Step 4 - Increment to next address and repeat process*/
	/*Step 5 - Terminate if '.' is input*/
	
	printf("Start address: %x\n\r", startAddress);	
	printf("Modify Memory\n\r");
}
