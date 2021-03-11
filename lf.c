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
	Produced by: Jack Walker
	*/
	
	/*Step 1 - Open channel on serial port*/
	/*Step 2 - Parse incoming data into memory*/
	/*Step 3 - Output some form of progress indicator*/
	/*Step 4 - Output when file fully read*/	
		
	unsigned char *scsr, *scdr, data, length, status, charcount, flag;
	unsigned char inputData[73];
	unsigned int len, origin, checksum, i;
	int linecount;
	
	charcount = 0;
	linecount = 0;
	flag = 0;
	status = 0;

	scsr = (unsigned char *) 0x2e;
	scdr = (unsigned char *) 0x2f;
	do {
		while(((*scsr) & 0x20) == 0x00);
		
		data = *scdr;
		
		if (data == 'S') {
			flag = 0; /* reset char count */	
			
			while(((*scsr) & 0x20) == 0x00);
			
			data = *scdr;
			if (data == '1') {
				charcount = 0;				
				putchar('~'); /*optional to save time remove */				
				flag = 1;  /* tell to start counting characters */				
				linecount++;
			}
			if (data == '9') {
				status = 1; /* Temp stop if S9 detected */
			}
		}
		if (flag == 1) {
			/*Extract length of line*/	
			while(((*scsr) & 0x20) == 0x00);			
			inputData[0] = *scdr;
			
			while(((*scsr) & 0x20) == 0x00);
			inputData[1] = *scdr;
			
			sscanf(inputData, "%x", &len);
			
			printf("%x\n\r", len);
			
			/*TODO: Loop through reading each byte and appending to array*/
			
			flag = 0;			
	
			/* do rest extract length, address*/
			/* You can use XON/XOFF or change delay on hyperterm */
			/*Don't forget to ignore all characters after line length */
		}
		
	} while (status == 0);
		
	printf("\n\rDownload completed S %d lines \n\r", linecount);
	printf("Last S1 Address + data + checksum = %02x \n\r", ((charcount-1)/2) - 1);
	return(0);
}
