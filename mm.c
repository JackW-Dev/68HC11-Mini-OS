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
	v1.0 - Will iterate over addresses and ask for input. Error - All inputs are being written as 72.
	v1.1 - Iterates over addresses and allows the user to update value. TODO: Validate input.
	v1.2 - Implemented isxdigit() to validate input.
	v1.3 - Corrected ability to skip using enter key.
	Produced by: Jack Walker
	*/
	
	unsigned char stringInp[10], dataInp[10];
	unsigned char *startAddress;
	unsigned char data, skipFlag, check, check2, check3;
	unsigned int hexData;
	int status, i;
	
	status = 0;
	
	printf("Modify Memory\n\r");
	
	printf("Start address: ");
	gets(stringInp);
	sscanf(stringInp, "%x", &startAddress);	
	
	do {
		/*Reset the dataInp array, data and skipFlag to reduce risk of remaining data causing errors*/
		
		dataInp[0] = '\n';
		dataInp[1] = '\0';
		data = '\0';
		skipFlag = 0;
		
		printf("%04x\t%02x : ", startAddress, *startAddress);
		gets(dataInp);
		
		sscanf(dataInp, "%c", &data);
				
		/*If the input is a full stop, set the status flag to stop MM and set skipFlag to prevent modify*/
		
		if (data == '.') {
			status = 1;
			skipFlag = 1;
		}
		
		/*If the input is a new line, increment the start address and set skipFlag to prevent modify*/
		
		if (data == '\n') {
			startAddress++;
			skipFlag = 1;
		}
		
		/*If skipFlag is not set, validate the input and either modify memory or report an error*/
		
		if (skipFlag == 0) {
								
			/*Check if valid hex input:
			- Both dataInp[0] and dataInp[1] are hex and dataInp[2] is '\0'
			- dataInp[0] is hex and dataInp[1] is '\0'
			- dataInp[0] is ' ', dataInp[1] is hex and dataInp[2] is '\0'*/		
				
			check = (isxdigit(dataInp[0]) && isxdigit(dataInp[1]) && dataInp[2] == '\0');
			check2 = (isxdigit(dataInp[0]) && dataInp[1] == '\0');
			check3 = (dataInp[0] == ' ' && isxdigit(dataInp[1]) && dataInp[2] == '\0');
					
			if (check || check2 || check3) {
				sscanf(dataInp, "%02x", &hexData);
				*startAddress = hexData;
				startAddress++;
			} else {	
				printf("Invalid input detected: %s.\n\r", dataInp); 
				printf("Please use . to stop, carriage return to skip or Hex to input.\n\r");	
			}
		}					
	} while (status == 0);
}

