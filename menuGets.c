#include <stdio.h>
#include <string.h>

char *mgets(char*);

/*
Function: Menu (Now Removed)
Operation: Provide a validated menu for the user to select system operation mode
Returns: An integer value representing the desired action
Date: 20/02/2021
Version: 1.2
Change log:
v1.0 - Function will validate user input to only accept valid code
v1.1 - Switch case statement added to branch to corresponding functions
v1.2 - Infinite for loop enclosing content to allow menu to re-run when other functions conclude
v1.3 - Added functionality for accepting start and end address params for functions that need them
v1.4 - After finding a logic error (can't return params and operationMode), the function was repurposed as part of main
v1.5 - Testing on 68HC11 found an error using scanf. Implemented homebrew gets() to replace this
Produced by: Jack Walker
*/

void main(void) {
	char inputString[15], inputMode[4];
	unsigned int validData = 0, operationMode = 0, inputStartAddress = 0, inputEndAddress = 0;
	
	for(;;) {
		printf("Welcome to Jack's 68HC11 MiniOS!\n\r");
		printf("Please select one of the following operational modes:\n\r");
		printf("Modify Memory - mm [START ADDRESS]\n\r");
		printf("Display Memory - dm [START ADDRESS]\n\r");
		printf("Disassemble Code - dis [START ADDRESS] [END ADDRESS]\n\r");
		printf("Load File - lf\n\r");
		printf("Demo Program - demo\n\r");
		
		do {
			printf("Mode: ");
			mgets(inputString);
			sscanf(inputString, "%s %x %x", &inputMode, &inputStartAddress, &inputEndAddress);
			
			/*Test print statement to check values have been set*/	
			printf("%s - %x - %x\n\r", inputMode, inputStartAddress, inputEndAddress);
						
			if(strcmp(inputMode, "mm") == 0) {										
				operationMode = 1;
				validData = 1;		
			} else if(strcmp(inputMode, "dm") == 0) {									
				operationMode = 2;
				validData = 1;			
			} else if(strcmp(inputMode, "dis") == 0) {											
				operationMode = 3;
				validData = 1;			
			} else if(strcmp(inputMode, "lf") == 0) {					
				operationMode = 4;
				validData = 1;			
			} else if(strcmp(inputMode, "demo") == 0) {				
				operationMode = 5;
				validData = 1;			
			} else {
				printf("Invalid command please try again!\n\r");
				inputMode[0] = '\0';
			}		
		} while(validData != 1);
			
		switch(operationMode) {
			case 1:
				printf("Memory Modify\n\r");
				break;
			case 2:
				printf("Display Memory\n\r");
				break;
			case 3:
				printf("Disassemble\n\r");
				break;
			case 4:
				printf("Load File\n\r");
				break;
			case 5:
				printf("Demo\n\r");
				break;
		}	
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
