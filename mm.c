#include <stdio.h>
#include <string.h>

void main() {
	/*
	Function: Modify Memory
	Operation: Allow the user to modify values stored in memory
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Change log:
	v1.0 - Will iterate over addresses and ask for input. Error - All inputs are being written as 72
	v1.1 - Iterates over addresses and allows the user to update value. TODO: Validate input.
	Produced by: Jack Walker
	*/
	
	/*Step 1 - Ask for a start address to edit*/
	/*Step 2 - Read user input for address and prompt for new data*/
	/*Step 3 - Validate that the data is storable and store (loop if can't store)*/
	/*Step 4 - Increment to next address and repeat process*/
	/*Step 5 - Terminate if '.' is input*/

	unsigned char stringInp[5], dataInp[3];
	unsigned char *startAddress;
	unsigned char data, topNibble, bottomNibble;
	unsigned int hexData;
	int status = 0, i;
	
	printf("Modify Memory\n\r");
	
	printf("Start address: ");
	gets(stringInp);
	sscanf(stringInp, "%x", &startAddress);	
	
	do {
		printf("%04x\t%02x : ", startAddress, *startAddress);
		gets(dataInp);
		
		sscanf(dataInp, "%c", &data);
		printf("%c\n\r", data);
		
		if (data == '.') {
			status = 1;
		}
		if (data == '\n') {
			startAddress++;
		}
		
		sscanf(dataInp, "%02x", &hexData);
		printf("%02x\n\r", hexData);
		
		if (hexData <= 255) {
			*startAddress = hexData;
			startAddress++;
		} else {
			prinf("Invalid input."); 
			printf("Please use . to stop, carriage return to skip or Hex to input.\n\r");
		}			
	} while (status == 0);
}

