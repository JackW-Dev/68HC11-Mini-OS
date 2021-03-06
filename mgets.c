#include <stdio.h>

char *mgets(char*);

void main() {
	char testStr[10];
	
	for(;;) {
		printf("Input a string (up to 9 char) and have it echo back!\n\r");
		mgets(testStr);
		printf("%s\n\r", testStr);
	}	
}

char *mgets(char *inputString) {
	/*
	Function: My Gets
	Operation: Homebrew gets() for reading in a string on the 68HC11
	Returns: String
	Date: 05/03/2021
	Version: 1.0
	Change log:
	Produced by: Jack Walker
	*/
    char *outputString;
    int currentChar;

    outputString = inputString;
    for (;;) {
		currentChar = getchar();
        if (currentChar == EOF) {
			return (NULL);
		} else if (currentChar == 0x0d) {
			break;	
		} else if (currentChar == 0x08) {			
			*outputString-- = putchar(' ');			
		} else {
			*outputString++ = currentChar;	
		}
    }
    if (inputString == outputString) return (NULL);
    *outputString = '\0';
    return (inputString);
}
