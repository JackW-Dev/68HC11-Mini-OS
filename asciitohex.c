#include <stdio.h>
#include <string.h>

unsigned int asciitohex(char);

void main() {
	unsigned char asciiVals[16];
	unsigned int hexVal;
	int i;
	
	strcpy(asciiVals, "0123456789ABCDEFabcdef");
	
	for (i = 0; i < 15; i++) {
		printf("Ascii: %02x - %d - %c\n\r", asciiVals[i], asciiVals[i], asciiVals[i]);
		hexVal = asciitohex(asciiVals[i]);
		printf("Hex: %02x - %d - %c\n\r", hexVal, hexVal, hexVal);
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
