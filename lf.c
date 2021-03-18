#include <stdio.h>
#include <string.h>

void main() {
	loadFile();
}

int loadFile() {
	/*
	Function: Load File
	Operation: Load a Motorola S19 file into memory
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Change log:
	v1.0 - Implemented basic file load that will read in the length of the file
	Produced by: Jack Walker
	*/
	
	/*Step 1 - Open channel on serial port*/
	/*Step 2 - Parse incoming data into memory*/
	/*Step 3 - Output some form of progress indicator*/
	/*Step 4 - Output when file fully read*/	
		
	unsigned char *scsr, *scdr, data, status, charcount, flag;
	/*Pre-initialised due to strange issue when outputting values using printf*/
	unsigned char lenArr[3] = {'0', '0', '\0'}, originArr[5] = {'0', '0', '0', '0', '\0'}, dataArr[65], checksumArr[3] = {'0', '0', '\0'};
	unsigned int lineLen, origin, checksum, i;
	int linecount;
	
	charcount = 0, linecount = 0, flag = 0,	status = 0;
	dataArr[64] = '\0';

	scsr = (unsigned char *) 0x2e;
	scdr = (unsigned char *) 0x2f;
	
	do {
		while(((*scsr) & 0x20) == 0x00);
		
		data = *scdr;
		
		if (data == 'S') {
			flag = 0; /*Reset char count */	
			
			while(((*scsr) & 0x20) == 0x00);
			
			data = *scdr;
			if (data == '1') {
				charcount = 0;				
				putchar('~'); /*Optional to save time remove*/				
				flag = 1;  /*Tell to start counting characters*/				
				linecount++;
			}
			if (data == '9') {
				status = 1; /*Temp stop if S9 detected*/
			}
		}
		
		if (flag == 1) {						
			/*Extract length of line*/	
			while(((*scsr) & 0x20) == 0x00);			
			lenArr[0] = *scdr;
			
			while(((*scsr) & 0x20) == 0x00);
			lenArr[1] = *scdr;
						
			/*Extract start address for line*/
			for (i = 0; i < 4; i++) {
				while(((*scsr) & 0x20) == 0x00);			
				originArr[i] = *scdr;
			}		
						
			/*TODO: Loop through reading each byte and appending to array*/		
			for (i = 0; i < lineLen - 6; i++) {
				while(((*scsr) & 0x20) == 0x00);			
				dataArr[i] = *scdr;
			}
									
			while(((*scsr) & 0x20) == 0x00);			
			checksumArr[0] = *scdr;
			
			while(((*scsr) & 0x20) == 0x00);
			checksumArr[1] = *scdr;
			
			sscanf(lenArr, "%x", &lineLen);			
			printf("Line len: %x\n\r", lineLen);
			
			sscanf(originArr, "%x", &origin);			
			printf("Origin: %x\n\r", origin);
			
			printf("Data: %s\n\r", dataArr);
			
			sscanf(checksumArr, "%x", &checksum);			
			printf("Checksum: %x\n\r", checksum);
									
			flag = 0;
				
			/*Do rest extract length, address*/
			/*You can use XON/XOFF or change delay on hyperterm*/
			/*Don't forget to ignore all characters after line length*/
		}	
			
	} while (status == 0);
	
	printf("\n\rDownload completed S %d lines\n\r", linecount);
	printf("Last S1 Address + data + checksum = %02x\n\r", ((charcount - 1) / 2) - 1);
	return(0);
}
