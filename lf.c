#include <stdio.h>
#include <string.h>

unsigned int asciitohex(char);
void loadFile();

typedef struct lineData {
    unsigned int lineLen, origin, checksum, sum;
} lineData;

void main() {
	loadFile();
}

void loadFile() {
	/*
	Function: Load File
	Operation: Load a Motorola S19 file into memory
	Returns: Integer error code
	Date: 18/03/2021
	Version: 1.4
	Change log:
	v1.0 - Implemented basic file load that will read in the length of the file
	v1.1 - Complete overhaul for reading method, now using nibbles
	v1.2 - Reads in length and start address
	v1.3 - Reads file data into memory and keeps a running total of the bytes (for use with checksum)
	v1.4 - Implemented checksum validation, printf of values after reading in and a structure for holding line data
	Produced by: Jack Walker
	*/
	
	struct lineData lineDetails[10];
	unsigned char *scsr, *scdr, *addrPtr, data, status = 0, count = 0, flag = 0, topNibble, bottomNibble, errorStatus = 0;
	int i, linecount = 0;

	/*printf("Load File\n\r");*/

	scsr = (unsigned char *) 0x2e;
	scdr = (unsigned char *) 0x2f;
	
	do {
		lineDetails[linecount].sum = 0;
		
		while(((*scsr) & 0x20) == 0x00);
		
		data = *scdr;
		
		if(data == 'S') {
			
			/*Reset char count*/	
			flag = 0; 
			
			while(((*scsr) & 0x20) == 0x00);
			
			data = *scdr;
			if(data == '1') {
				count = 0;	
				
				/*Optional to save time remove*/	
				putchar('~');
				
				/*Tell to start counting characters*/				
				flag = 1;						
			}
			if(data == '9') {
				
				/*Stop if S9 detected*/
				status = 1; 
			}
		}
		
		if(flag == 1) {
								
			/*Extract length of line*/	
			while(((*scsr) & 0x20) == 0x00);
			topNibble = asciitohex(*scdr);						
			
			while(((*scsr) & 0x20) == 0x00);
			bottomNibble = asciitohex(*scdr);
						
			/*Shift top nibble to top half of byte and add bottom nibble to form whole byte*/
			lineDetails[linecount].lineLen = topNibble << 4 | bottomNibble;
			
			lineDetails[linecount].sum += lineDetails[linecount].lineLen;
						
			/*Extract start address of line*/
			while(((*scsr) & 0x20) == 0x00);
			topNibble = asciitohex(*scdr);						
			
			while(((*scsr) & 0x20) == 0x00);
			bottomNibble = asciitohex(*scdr);
			
			/*Increment byte count*/
			count++;
			
			/*Shift top nibble to top half of byte and add bottom nibble to form whole byte*/
			lineDetails[linecount].origin = topNibble << 4 | bottomNibble;
			
			lineDetails[linecount].sum += lineDetails[linecount].origin;
			
			while(((*scsr) & 0x20) == 0x00);
			topNibble = asciitohex(*scdr);						
			
			while(((*scsr) & 0x20) == 0x00);
			bottomNibble = asciitohex(*scdr);
			
			/*Increment byte count*/
			count++;
			
			lineDetails[linecount].sum += (topNibble << 4 | bottomNibble);
			
			/*Shift value already stored into the top byte and add the other formed byte to the bottom byte*/
			lineDetails[linecount].origin = (lineDetails[linecount].origin << 8) + (topNibble << 4 | bottomNibble);
			
			addrPtr = (char *)lineDetails[linecount].origin;
			
			/*Loop through data coming in and write direct to memory, starting at the address stored in origin*/		
			for(i = 0; i < lineDetails[linecount].lineLen - 3; i++) {
				while(((*scsr) & 0x20) == 0x00);
				topNibble = asciitohex(*scdr);						
			
				while(((*scsr) & 0x20) == 0x00);
				bottomNibble = asciitohex(*scdr);
				
				/*Increment byte count*/
				count++;
				
				*addrPtr = topNibble << 4 | bottomNibble;
				lineDetails[linecount].sum += *addrPtr;
				addrPtr++;
			}
			
			/*Extract checksum*/
			while(((*scsr) & 0x20) == 0x00);
			topNibble = asciitohex(*scdr);						
			
			while(((*scsr) & 0x20) == 0x00);
			bottomNibble = asciitohex(*scdr);
			
			/*Increment byte count*/
			count++;
			
			/*Shift top nibble to top half of byte and add bottom nibble to form whole byte*/
			lineDetails[linecount].checksum = topNibble << 4 | bottomNibble;
			
			/*Mask to 8 bit and then invert*/
			lineDetails[linecount].sum = lineDetails[linecount].sum | 0xff00;
			lineDetails[linecount].sum = ~lineDetails[linecount].sum;
			
			if(lineDetails[linecount].sum == lineDetails[linecount].checksum) {
				linecount++;							
				
			} else {
				printf("\n\r");
				printf("Error loading line %d.\n\r", linecount + 1);
				printf("Calculated checksum %02x does not match expected checksum %02x.\n\r", lineDetails[linecount].sum, lineDetails[linecount].checksum);
				printf("Aborting load process!\n\r");
				errorStatus = 1;
				status = 1;
			}
			flag = 0;			
		}			
	} while(status == 0);
	
	printf("\n\r");

	for(i = 0; i < linecount + 1; i++) {
		printf("Line len: %02x\t Origin: %04x\t Checksum: %02x\t Calculated checksum: %02x\n\r", lineDetails[i].lineLen, lineDetails[i].origin, lineDetails[i].checksum, lineDetails[i].sum);
	}
	
	if(errorStatus == 0) {
		printf("S19 File Download Completed - %d Lines Read Into Memory\n\r", linecount + 1);
		printf("Program starts at %04x\n\r", lineDetails[0].origin);
	}	
}

unsigned int asciitohex(char thisChar) {
	/*
	Function: Ascii to Hex
	Operation: Convert Ascii value to hex
	Returns: Unsigned int hex value converted from Ascii values
	Date: 18/03/2021
	Version: 1.1
	Change log:
	v1.0 - Converts 0-9 chars to hex and not ascii hex
	v1.1 - Converts A-F chars to hex and not ascii hex
	Produced by: Jack Walker
	*/
	
	/*If in the range of char '0' to '9', subtracting '0' will convert Ascii to hex*/	
	if('0' <= thisChar && thisChar <= '9') {
		return thisChar - '0';
	}
	
	/*If in the range of char 'A' to 'F', adding 10 and subtracting 'A' will convert Ascii to hex*/	
	if('A' <= thisChar && thisChar <= 'F') {
		return thisChar + 10 - 'A';
	}
	
	/*If in the range of char 'a' to 'f', adding 10 and subtracting 'a' will convert Ascii to hex*/	
	if('a' <= thisChar && thisChar <= 'f') {
		return thisChar + 10 - 'a';
	}
}

