#include <stdio.h>

/*Function Prototypes*/
int menu();
int modifyMemory();
int displayMemory();
int disassemble();
int loadFile();
int demo();

void main(void) {
	/*
	Function: Main
	Operation: Handle main code operation and call relevant functions
	Returns: Void
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
	int mode;
	
	mode = menu();
	printf("%i", mode);
	
	
}

int menu() {	
	/*
	Function: Menu
	Operation: Provide a validated menu for the user to select system operation mode
	Returns: An integer value representing the desired action
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
	char userInput[4];
	int validData = 0, operationMode = 0;
	
	printf("Welcome to Jack's 68HC11 MiniOS!\n\r"
	"Please select one of the following operational modes:\n\r"
	"Modify Memory - mm\n\r"
	"Display Memory - dm\n\r"
	"Disassemble Code - dis\n\r"
	"Load File - lf\n\r"
	"Demo Program - demo\n\r");
	
	do {
		printf("Mode: ");
		scanf("%s", &userInput);
		printf("User Input: %s\n\r", userInput);
		
		if(strcmp(userInput, "mm") == 0) {
			operationMode = 1;
			validData = 1;
		} else if(strcmp(userInput, "dm") == 0) {
			operationMode = 2;
			validData = 1;
		} else if(strcmp(userInput, "dis") == 0) {
			operationMode = 3;
			validData = 1;
		} else if(strcmp(userInput, "lf") == 0) {
			operationMode = 4;
			validData = 1;
		} else if(strcmp(userInput, "demo") == 0) {
			operationMode = 5;
			validData = 1;
		} else {
			userInput[0] = '\0';
		}		
	} while(validData != 1);
	
	return operationMode;
}

int modifyMemory() {
	/*
	Function: Modify Memory
	Operation: Allow the user to modify values stored in memory
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
}

int displayMemory() {
	/*
	Function: Display Memory
	Operation: Allow the user to view the values stored in memory
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
}

int disassemble() {
	/*
	Function: Disassemble
	Operation: Convert hex into assembly language code
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
}

int loadFile() {
	/*
	Function: Load File
	Operation: Load a Motorola S19 file into memory
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
}

int demo() {
	/*
	Function: Demo
	Operation: Demo program using a variable resistor to step a motor
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
}
