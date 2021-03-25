#include <stdio.h>
#include <string.h>

void displayMemory(unsigned int);

void main() {
	unsigned int start = 0x4600;

	displayMemory(start);
}

void displayMemory(unsigned int start) {
	/*
	Function: Display Memory
	Operation: Allow the user to view the values stored in memory
	Returns: Integer error code
	Date: 15/03/2021
	Version: 1.1
	Change log:
	v1.0 - Output values correctly - Some strange characters appearing
	v1.1 - Fix for valid ASCII codes being between 0x20 and 0x7f
	Produced by: Jack Walker
	*/
	
	/*unsigned char stringInp[10];*/
	unsigned char *startAddress;
	int i, j, k;
	unsigned char data;
	
	/*printf("Display Memory\n\r");
	
	printf("Start address: ");
	gets(stringInp);
	sscanf(stringInp, "%x", &startAddress);*/

	startAddress = (unsigned char *)start;

	printf("Address\t\t Hex\t\t\t ASCII\n\r");
	
	/*Loop through 16 times, incrementing by 10 each time to pring the 16 lines*/	
	for(i = 0; i < 160; i = (i + 10)) {		
		printf(" %04x\t ", startAddress);
		
		/*Loop through 10 values from startAddress and output the hex stored in the address*/		
		for(j = 0; j < 10; j++) {
			data = *(startAddress + j);			
			printf("%02x ", data);			
		}
		printf("\t");
		
		/*Loop through 10 values from startAddress and output the cahr stored in the address
		Output "." if the value is not in the ASCII table*/		
		for(k = 0; k < 10; k++) {
			data = *(startAddress + k);
			
			/*Hex values between 0x20 and 0x7f are valid, printable characters.
			Those before are special characters such as SPACE and NULL*/			
			if(data > 0x20 && data < 0x7F) {
				printf("%c", data);
			} else {
				printf(".", data);
			}
		}
		printf("\n\r");
		startAddress = startAddress + 10;
	}
}
