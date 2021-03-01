#include <stdio.h>
#include <string.h>

/*Function Prototypes*/
int menu();
int modifyMemory();
int displayMemory();
int disassemble();
int loadFile();
int demo();

/*Structure definitions*/
typedef struct {
	int hexValue;
	int expectedArgs;
	char functionName[4];	
} assemblyFunction;

void main(void) {
	/*
	Function: Main
	Operation: Handle main code operation and call relevant functions
	Returns: Void
	Date: 20/02/2021
	Version: 1.0
	Produced by: Jack Walker
	*/
	
	for(;;) {
		int mode;
	
		mode = menu();
		/*printf("%i\n\r", mode);*/
		
		switch(mode) {
			case 1:
				modifyMemory();
				break;
			case 2:
				displayMemory();
				break;
			case 3:
				disassemble();
				break;
			case 4:
				loadFile();
				break;
			case 5:
				demo();
				break;
		}	
	}
	
}

int menu() {	
	/*
	Function: Menu
	Operation: Provide a validated menu for the user to select system operation mode
	Returns: An integer value representing the desired action
	Date: 20/02/2021
	Version: 1.2
	Change log:
	v1.0 - Function will validate user input to anly accept valid code
	v1.1 - Switch case statement added to branch to corresponding functions
	v1.2 - Infinite for loop enclosing content to allow menu to re-run when other functions conclude
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
	
	/*Step 1 - Ask for a start address to edit*/
	/*Step 2 - Read user input for address and prompt for new data*/
	/*Step 3 - Validate that the data is storable and store (loop if can't store)*/
	/*Step 4 - Increment to next address and repeat process*/
	/*Step 5 - Terminate if '.' is input*/
	
	printf("Modify Memory\n\r");
	
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
	
	/*Step 1 - Ask for start address*/
	/*Step 2 - Validate user input and loop if invalid*/
	/*Step 3 - Display contents of memory from the starting address to the address + 100 (if possible)*/
	
	printf("Display Memory\n\r");
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
	
	/*Step 1 - Create array of assemblyFunction structures*/
	/*Step 2 - Parse memory determining the function and expectedArgs for each*/
	/*Step 3 - Convert the hex to the corresponding function and read the expectedArgs as data*/
	/*Step 4 - Format output*/
	
	printf("Disassemble\n\r");
	
	assemblyFunction hexCodes[70];	/*There are 70 assembly functions that must be handled for this assignment*/
	
	hexCodes[0].hexValue = 0x1B;
	hexCodes[0].expectedArgs = 0;
	strcpy(hexCodes[0].functionName, "ABA");
		
	/*printf("hexCodes[0]\n\r"
	"Hex Value: %x\n\r"
	"Expected Arguments: %x\n\r"
	"Function Name: %s\n\r",
	hexCodes[0].hexValue, hexCodes[0].expectedArgs, hexCodes[0].functionName);*/
	
	
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
	
	/*Step 1 - Open channel on serial port*/
	/*Step 2 - Parse incoming data into memory*/
	/*Step 3 - Output some form of progress indicator*/
	/*Step 4 - Output when file fully read*/
	
	
	printf("Load File\n\r");
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
	
	/*Step 1 - Start demo program using ports*/
	
	printf("Demo\n\r");
}
