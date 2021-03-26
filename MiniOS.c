#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Function Prototypes*/
void modifyMemory(unsigned int);
void displayMemory(unsigned int);
void disassemble(unsigned int, unsigned int);
void loadFile();
void demo();
unsigned int asciitohex(char);

/*Structures*/
typedef struct assemblyFunc {
    char functionName[10];
    int expectedArgs;
} assemblyFunc;

typedef struct extendedAssemblyFunc {
    char functionName[10];
    char functionCode;
    int expectedArgs;
} extendedAssemblyFunc;

typedef struct lineData {
    unsigned int lineLen, origin, checksum, sum;
} lineData;

/*
Function: 68HC11 MiniOS
Operation: Replicate the Mini OS that has been provided for use with the 68HC11
Returns: Void
Date: 25/03/2021
Version: 1.0
Change log:
v1.0 - Consolidated unit tested functions
Produced by: Jack Walker
*/

void main() {
/*
Function: Main (formerly menu)
Operation: Provide a validated menu for the user to select system operation mode
Returns: An integer value representing the desired action
Date: 25/03/2021
Version: 1.7
Change log:
v1.0 - Function will validate user input to only accept valid code
v1.1 - Switch case statement added to branch to corresponding functions
v1.2 - Infinite for loop enclosing content to allow menu to re-run when other functions conclude
v1.3 - Added functionality for accepting start and end address params for functions that need them
v1.4 - After finding a logic error (can't return params and operationMode), the function was repurposed as part of main
v1.5 - Testing on 68HC11 found an error using scanf. Implemented homebrew gets() to replace this
v1.6 - Due to new release of gets(), the homebrew function has been removed
v1.7 - Fully validated user inputs to match validation of existing solution
Produced by: Jack Walker
*/
	char inputString[20], inputMode[8], checkString[8], checkString2[8];
	unsigned int inputStartAddress = 0, inputEndAddress = 0, i;
	unsigned char check, check2;
	
	for(;;) {
		printf("Welcome to Jack's 68HC11 MiniOS!\n\r");
		printf("Please select one of the following operational modes:\n\r");
		printf("Modify Memory - mm [START ADDRESS]\n\r");
		printf("Display Memory - dm [START ADDRESS]\n\r");
		printf("Disassemble Code - dis [START ADDRESS] [END ADDRESS]\n\r");
		printf("Load File - lf\n\r");
		printf("Demo Program - demo\n\r");
			
		/*Clear variables to reduce risk of error*/
		inputMode[0] = '\0';
		inputStartAddress = 0;
		inputEndAddress = 0;
		check = 0;
		check2 = 0;
		
		/*Get user input for mode and params*/
		printf("Mode: ");
		gets(inputString);
		
		sscanf(inputString, "%s %s %s", &inputMode, &checkString, &checkString2);
		sscanf(inputString, "%s %x %x", &inputMode, &inputStartAddress, &inputEndAddress);
					
		/*Test print statement to check values have been set		
		printf("%s - %s - %s\n\r", inputMode, checkString, checkString2);
		printf("%s - %x - %x\n\r", inputMode, inputStartAddress, inputEndAddress);*/
		
		for(i = 0; i < 5; i++) {
			inputMode[i] = tolower(inputMode[i]);
		}
					
		if(strcmp(inputMode, "mm") == 0) {
			
			/*Valid input should be 3 or 4 digit hex*/
			check = (isxdigit(checkString[0]) && isxdigit(checkString[1]) && isxdigit(checkString[2]) && checkString[3] == '\0');
			check2 = (isxdigit(checkString[0]) && isxdigit(checkString[1]) && isxdigit(checkString[2]) && isxdigit(checkString[3]) && checkString[4] == '\0');
			
			if(check || check2) {
				
				/*End address will be empty if correct input routine followed*/
				if(inputEndAddress == 0x0000) {
									
					/*Between 400 and 7DFF as a memory boundary*/
					if(0x400 <= inputStartAddress && inputStartAddress <= 0x7dff) {
						
						/*All tests passed, data is valid*/
						printf("Memory Modify\n\r");
						modifyMemory(inputStartAddress);
						
					} else {
						printf("Invalid address given. User gave %04x and value must be in range 0x400 -> 0x7dff\n\r", inputStartAddress);
					}											
				} else {
					printf("Invalid input provided, please only provide a start address.\n\r");
				}					
			} else {
				printf("Invalid address given. User gave %s and value must be hex 0-9 A-F\n\r", checkString);
			}								
		} else if(strcmp(inputMode, "dm") == 0) {									
							
			/*Valid input should be 3 or 4 digit hex*/
			check = (isxdigit(checkString[0]) && isxdigit(checkString[1]) && isxdigit(checkString[2]) && checkString[3] == '\0');
			check2 = (isxdigit(checkString[0]) && isxdigit(checkString[1]) && isxdigit(checkString[2]) && isxdigit(checkString[3]) && checkString[4] == '\0');
			
			if(check || check2) {
				
				/*End address will be empty if correct input routine followed*/
				if(inputEndAddress == 0x0000) {
									
					/*Between 400 and 7DFF as a memory boundary*/
					if(0x400 <= inputStartAddress && inputStartAddress <= 0x7dff) {
						
						/*All tests passed, data is valid*/
						printf("Display Memory\n\r");
						displayMemory(inputStartAddress);
						
					} else {
						printf("Invalid address given. User gave %04x and value must be in range 0x400 -> 0x7dff\n\r", inputStartAddress);
					}					
				} else {
					printf("Invalid input provided, please only provide a start address.\n\r");
				}
			} else {
				printf("Invalid address given. User gave %s and value must be hex 0-9 A-F\n\r", checkString);
			}						
		} else if(strcmp(inputMode, "dis") == 0) {											
			
			/*Valid input should be 3 or 4 digit hex*/
			check = (isxdigit(checkString[0]) && isxdigit(checkString[1]) && isxdigit(checkString[2]) && checkString[3] == '\0');
			check2 = (isxdigit(checkString[0]) && isxdigit(checkString[1]) && isxdigit(checkString[2]) && isxdigit(checkString[3]) && checkString[4] == '\0');
			
			if(check || check2) {
				
				/*Valid input should be 3 or 4 digit hex*/
				check = (isxdigit(checkString2[0]) && isxdigit(checkString2[1]) && isxdigit(checkString2[2]) && checkString2[3] == '\0');
				check2 = (isxdigit(checkString2[0]) && isxdigit(checkString2[1]) && isxdigit(checkString2[2]) && isxdigit(checkString2[3]) && checkString2[4] == '\0');
				
				if(check || check2) {
					
					check = 0x400 <= inputStartAddress && inputStartAddress <= 0x7dff;
					check2 = 0x400 <= inputEndAddress && inputEndAddress <= 0x7dff;

					/*Between 400 and 7DFF as a memory boundary*/
					if(check && check2) {
						
						/*Start address must be less than end address*/
						if(inputStartAddress < inputEndAddress) {
							
							/*All tests passed, data is valid*/
							printf("Disassemble\n\r");
							disassemble(inputStartAddress, inputEndAddress);
							
						} else {
							printf("Invalid address format. User gave %04x %04x. Start address must be less than end address.\n\r", inputStartAddress, inputEndAddress);
						}							
					} else {
						printf("Invalid address given. User gave %04x and value must be in range 0x400 -> 0x7dff\n\r", inputStartAddress);
					}
				} else {
					printf("Invalid end address given. User gave %s and value must be hex 0-9 A-F\n\r", checkString);
				}				
			} else {
				printf("Invalid start address given. User gave %s and value must be hex 0-9 A-F\n\r", checkString);
			}							
		} else if(strcmp(inputMode, "lf") == 0) {
			
			/*If any extra data is given, ignore it*/
			if(inputStartAddress != 0 || inputEndAddress != 0) {
				printf("Additional data has been ignored.\n\r");
			}				
			printf("Load File\n\r");
			loadFile();
		
		} else if(strcmp(inputMode, "demo") == 0) {	
		
			/*If any extra data is given, ignore it*/
			if(inputStartAddress != 0 || inputEndAddress != 0) {
				printf("Additional data has been ignored.\n\r");
			}						
			printf("Demo\n\r");
			demo();					
		} else {
			printf("Invalid command please try again!\n\r");
			inputMode[0] = '\0';
		}	
	}	
}

void modifyMemory(unsigned int start) {
	/*
	Function: Modify Memory
	Operation: Allow the user to modify values stored in memory
	Returns: Integer error code
	Date: 25/03/2021
	Version: 1.3
	Change log:
	v1.0 - Will iterate over addresses and ask for input. Error - All inputs are being written as 72.
	v1.1 - Iterates over addresses and allows the user to update value. TODO: Validate input.
	v1.2 - Implemented isxdigit() to validate input.
	v1.3 - Corrected ability to skip using enter key.
	Produced by: Jack Walker
	*/
	
	unsigned char /*stringInp[10],*/ dataInp[10];
	unsigned char *startAddress;
	unsigned char data, skipFlag, check, check2, check3, check4;
	unsigned int hexData;
	int status, i;
	
	status = 0;
	
	/*printf("Modify Memory\n\r");
	
	printf("Start address: ");
	gets(stringInp);
	sscanf(stringInp, "%x", &startAddress);*/
	
	startAddress = (unsigned char *)start;
	
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
			- dataInp[0] is ' ', dataInp[1] is hex and dataInp[2] is '\0'
			- dataInp[0] is hex, dataInp[1] is ' ' and dataInp[2] is '\0'*/						
			check = (isxdigit(dataInp[0]) && isxdigit(dataInp[1]) && dataInp[2] == '\0');
			check2 = (isxdigit(dataInp[0]) && dataInp[1] == '\0');
			check3 = (dataInp[0] == ' ' && isxdigit(dataInp[1]) && dataInp[2] == '\0');
			check4 = (isxdigit(dataInp[0]) && dataInp[1] == ' ' && dataInp[2] == '\0');
					
			if (check || check2 || check3 || check4) {
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

void disassemble(unsigned int start, unsigned int end) {
		
	/*
	Function: Disassemble
	Operation: Convert hex into assembly language code
	Returns: Integer error code
	Date: 11/03/2021
	Version: 1.4
	Change log:
	v1.0 - Function stub outputting "disassemble"
	v1.1 - Added assemblyFunction structs and populated array with assembly function details
	v1.2 - Adjust structures to behave better with for loop
	v1.3 - Remove for loop and utilise while loop instead	
	v1.4 - Implement extended functions using different structure
	Produced by: Jack Walker
	*/
  
    struct assemblyFunc functions[255];
	struct extendedAssemblyFunc extendedFunctions[15];
    unsigned char *startAddress, *endAddress, data, data2, i, extendedFlag;
    /*unsigned char stringInp[10];*/
    char temp[15], temp2[10], temp3[10];

    /*Populate functions array with assembly function data*/
    
    /*Addition Functions*/
    
    strcpy(functions[0x1B].functionName, "ABA ");
    functions[0x1B].expectedArgs = 0;
    
	strcpy(functions[0x3A].functionName, "ABX ");
    functions[0x3A].expectedArgs = 0;
    	
	/*ADCA*/
	
	strcpy(functions[0x89].functionName, "ADCA #$");
	functions[0x89].expectedArgs = 1;	

	strcpy(functions[0x99].functionName, "ADCA $");
	functions[0x99].expectedArgs = 1;
	
	strcpy(functions[0xB9].functionName, "ADCA $");
	functions[0xB9].expectedArgs = 2;
	
	strcpy(functions[0xA9].functionName, "ADCA X, $");
	functions[0xA9].expectedArgs = 1;
	
	/*ADCB*/

	strcpy(functions[0xC9].functionName, "ADCB #$");
	functions[0xC9].expectedArgs = 1;

	strcpy(functions[0xD9].functionName, "ADCB $");
	functions[0xD9].expectedArgs = 1;
	
	strcpy(functions[0xF9].functionName, "ADCB $");
	functions[0xF9].expectedArgs = 2;
	
	strcpy(functions[0xE9].functionName, "ADCB X, $");
	functions[0xE9].expectedArgs = 1;
 
    /*ADDA*/
    
	strcpy(functions[0x8B].functionName, "ADDA #$");
	functions[0x8B].expectedArgs = 1;
	
	strcpy(functions[0x9B].functionName, "ADDA $");
	functions[0x9B].expectedArgs = 1;

	strcpy(functions[0xBB].functionName, "ADDA $");
	functions[0xBB].expectedArgs = 2;
	
	strcpy(functions[0xAB].functionName, "ADDA X, $");
	functions[0xAB].expectedArgs = 1;
	
	/*ADDB*/
	
	strcpy(functions[0xCB].functionName, "ADDB #$");
	functions[0xCB].expectedArgs = 1;
		
	strcpy(functions[0xDB].functionName, "ADDB $");
	functions[0xDB].expectedArgs = 1;
	
	strcpy(functions[0xFB].functionName, "ADDB $");
	functions[0xFB].expectedArgs = 2;
	
	strcpy(functions[0xEB].functionName, "ADDB X, $");
	functions[0xEB].expectedArgs = 1;
	
	/*ADDD*/
	
	strcpy(functions[0xC3].functionName, "ADDD #$");	
	functions[0xC3].expectedArgs = 2;

	strcpy(functions[0xD3].functionName, "ADDD $");
	functions[0xD3].expectedArgs = 1;
	
	strcpy(functions[0xF3].functionName, "ADDD $");
	functions[0xF3].expectedArgs = 2;
	
	strcpy(functions[0xE3].functionName, "ADDD X, $");
	functions[0xE3].expectedArgs = 1;
	
	/*Subtraction Functions*/
		
	/*SUBA*/

	strcpy(functions[0x80].functionName, "SUBA #$");
	functions[0x80].expectedArgs = 1;
	
	strcpy(functions[0x90].functionName, "SUBA $");
	functions[0x90].expectedArgs = 1;

	strcpy(functions[0xB0].functionName, "SUBA $");
	functions[0xB0].expectedArgs = 2;

	strcpy(functions[0xA0].functionName, "SUBA X, $");
	functions[0xA0].expectedArgs = 1;
	
	/*SUBB*/

	strcpy(functions[0xC0].functionName, "SUBB #$");
	functions[0xC0].expectedArgs = 1;

	strcpy(functions[0xD0].functionName, "SUBB $");
	functions[0xD0].expectedArgs = 1;
	
	strcpy(functions[0xF0].functionName, "SUBB $");
	functions[0xF0].expectedArgs = 2;
	
	strcpy(functions[0xE0].functionName, "SUBB X, $");
	functions[0xE0].expectedArgs = 1;
		
	/*SUBD*/
	
	strcpy(functions[0x83].functionName, "SUBD #$");
	functions[0x83].expectedArgs = 2;
	
	strcpy(functions[0x93].functionName, "SUBD $");
	functions[0x93].expectedArgs = 1;
	
	strcpy(functions[0xB3].functionName, "SUBD $");
	functions[0xB3].expectedArgs = 2;
	
	strcpy(functions[0xA3].functionName, "SUBD X, $");
	functions[0xA3].expectedArgs = 1;
		
	/*Load Accumulator Functions*/	
	
	/*LDAA*/

	strcpy(functions[0x86].functionName, "LDAA #$");
	functions[0x86].expectedArgs = 1;

	strcpy(functions[0x96].functionName, "LDAA $");
	functions[0x96].expectedArgs = 1;
	
	strcpy(functions[0xB6].functionName, "LDAA $");
	functions[0xB6].expectedArgs = 2;	
	
	strcpy(functions[0xA6].functionName, "LDAA X, $");
	functions[0xA6].expectedArgs = 1;
		
	/*LDAB*/

	strcpy(functions[0xC6].functionName, "LDAB #$");
	functions[0xC6].expectedArgs = 1;	

	strcpy(functions[0xD6].functionName, "LDAB $");
	functions[0xD6].expectedArgs = 1;	
	
	strcpy(functions[0xF6].functionName, "LDAB $");
	functions[0xF6].expectedArgs = 2;
	
	strcpy(functions[0xE6].functionName, "LDAB X, $");
	functions[0xE6].expectedArgs = 1;
	
	/*LDD/LDAD*/
	
	strcpy(functions[0xCC].functionName, "LDD #$");
	functions[0xCC].expectedArgs = 2;
	
	strcpy(functions[0xDC].functionName, "LDD $");
	functions[0xDC].expectedArgs = 1;
	
	strcpy(functions[0xFC].functionName, "LDD $");
	functions[0xFC].expectedArgs = 2;
	
	strcpy(functions[0xEC].functionName, "LDD X, $");
	functions[0xEC].expectedArgs = 1;
		
	/*Store Accumulator Functions*/
	
	/*STAA*/
	
	strcpy(functions[0x97].functionName, "STAA $");
	functions[0x97].expectedArgs = 1;
	
	strcpy(functions[0xB7].functionName, "STAA $");
	functions[0xB7].expectedArgs = 2;
	
	strcpy(functions[0xA7].functionName, "STAA X, $");
	functions[0xA7].expectedArgs = 1;
		
	/*STAB*/
	
	strcpy(functions[0xD7].functionName, "STAB $");
	functions[0xD7].expectedArgs = 1;
	
	strcpy(functions[0xF7].functionName, "STAB $");
	functions[0xF7].expectedArgs = 2;
	
	strcpy(functions[0xE7].functionName, "STAB X, $");
	functions[0xE7].expectedArgs = 1;
		
	/*STD/STAD*/
	
	strcpy(functions[0xDD].functionName, "STD $");
	functions[0xDD].expectedArgs = 1;
	
	strcpy(functions[0xFD].functionName, "STD $");
	functions[0xFD].expectedArgs = 2;
	
	strcpy(functions[0xED].functionName, "STD X, $");
	functions[0xED].expectedArgs = 1;
	
	/*Extended Functions*/

	strcpy(extendedFunctions[0].functionName, "ABY ");
	extendedFunctions[0].expectedArgs = 0;
	extendedFunctions[0].functionCode = 0x3A;

	strcpy(extendedFunctions[1].functionName, "ADCA Y, $");
	extendedFunctions[1].expectedArgs = 1;
	extendedFunctions[1].functionCode = 0xA9;

	strcpy(extendedFunctions[2].functionName, "ADCB Y, $");
    extendedFunctions[2].expectedArgs = 1;
    extendedFunctions[2].functionCode = 0xE9;

	strcpy(extendedFunctions[3].functionName, "ADDA Y, $");
	extendedFunctions[3].expectedArgs = 1;
	extendedFunctions[3].functionCode = 0xAB;
	
	strcpy(extendedFunctions[4].functionName, "ADDB Y, $");
	extendedFunctions[4].expectedArgs = 1;
	extendedFunctions[4].functionCode = 0xEB;

	strcpy(extendedFunctions[5].functionName, "ADDD Y, $");
	extendedFunctions[5].expectedArgs = 1;
	extendedFunctions[5].functionCode = 0xE3;

	strcpy(extendedFunctions[6].functionName, "SUBA Y, $");
	extendedFunctions[6].expectedArgs = 1;
	extendedFunctions[6].functionCode = 0xA0;	
	
	strcpy(extendedFunctions[7].functionName, "SUBB Y, $");
	extendedFunctions[7].expectedArgs = 1;
	extendedFunctions[7].functionCode = 0xE0;

	strcpy(extendedFunctions[8].functionName, "SUBD Y, $");
	extendedFunctions[8].expectedArgs = 1;
	extendedFunctions[8].functionCode = 0xA3;

	strcpy(extendedFunctions[9].functionName, "LDAA Y, $");
	extendedFunctions[9].expectedArgs = 1;
	extendedFunctions[9].functionCode = 0xA6;

	strcpy(extendedFunctions[10].functionName, "LDAB Y, $");
	extendedFunctions[10].expectedArgs = 1;
	extendedFunctions[10].functionCode = 0xE6;	

	strcpy(extendedFunctions[11].functionName, "LDD Y, $");
	extendedFunctions[11].expectedArgs = 1;
	extendedFunctions[11].functionCode = 0xEC;

	strcpy(extendedFunctions[12].functionName, "STAA Y, $");
	extendedFunctions[12].expectedArgs = 1;
	extendedFunctions[12].functionCode = 0xA7;

	strcpy(extendedFunctions[13].functionName, "STAB Y, $");
	extendedFunctions[13].expectedArgs = 1;
	extendedFunctions[13].functionCode = 0xE7;

	strcpy(extendedFunctions[14].functionName, "STAD Y, $");
	extendedFunctions[14].expectedArgs = 1;
	extendedFunctions[14].functionCode = 0xED;

	/*print("Disassemble"\n\r);
	
	printf("Please enter start and end address in form [start] [end]: ");
	gets(stringInp);
	sscanf(stringInp, "%x %x", &startAddress, &endAddress);*/
	
	startAddress = (unsigned char *)start;
	endAddress = (unsigned char *)end;
	
	printf("Address\t Hex\t\t Assembly\n\r");
	
	/*Will loop until range is covered*/	
	while(startAddress <= endAddress - 1) {
		
		/*Reset strings to null to reduce risk of remaining data causing errors*/		
		temp[0] = '\0';
		temp2[0] = '\0';
		temp3[0] = '\0';
		extendedFlag = 0;
						
		/*Get the hex value held at the start address*/		
		data = *startAddress;
		
		/*Check for extended address functions*/		
		if(data == 0x18) {
			
			/*Get the hex value held at start address + 1 (extended mode uses 2 byte code)*/			
			data2 = *(startAddress + 1);
			
			/*Iterate through the array of extended address functions*/			
			for(i = 0; i < 15; i++) {
				
				/*If function code matches data 2 (all extended are 0x18~~ in format)*/				
				if(extendedFunctions[i].functionCode == data2) {
					extendedFlag = 1;
					
					/*Output address followed by data and data2 (this will output the function's full hex code)*/					
					printf("%x\t %02x%02x", startAddress, data, data2);		
					strcpy(temp, extendedFunctions[i].functionName);
					
					/*Switch case based on the expected arguments
					This will ensure any relevant data is output with the function*/					
					switch(extendedFunctions[i].expectedArgs) {
						case 0:
							printf("\t\t %s\n\r", temp);
							startAddress++;
							break;
						case 1:
							data = *(startAddress + 2);
							sprintf(temp2, "%02x", data);
							
				    		printf("%02x", data);
				    		
				    		strcat(temp, temp2);
									
							startAddress++;
							startAddress++;
							
							printf("\t\t %s\n\r", temp);
							break;
					}					
				}
			}
			
			if(extendedFlag == 0) {
				printf("%x\t %02x\n\r", startAddress, data);
			}
							
		/*Handle all normal address functions*/						
		} else {
			
			/*Output address followed by data (this will output the function's hex code)*/							
			printf("%x\t %02x", startAddress, data);
				
			strcpy(temp, functions[data].functionName);
			
			/*Switch case based on the expected arguments
			This will ensure any relevant data is output with the function*/			
			switch(functions[data].expectedArgs) {
				case 0:					
					printf("\t\t %s\n\r", temp);
					break;
				case 1:
					data = *(startAddress + 1);
					sprintf(temp2, "%02x", data);
					
					printf("%02x", data);    		
		    		
		    		strcat(temp, temp2);	
							
					startAddress++;
					
					printf("\t\t %s\n\r", temp);
					break;
				case 2:
					data = *(startAddress + 1);
		    		sprintf(temp2, "%02x", data);
		    		
		    		printf("%02x", data);
								
					data = *(startAddress + 2);
					sprintf(temp3, "%02x", data);
					
					printf("%02x", data);
					
					strcat(temp2, temp3);
						
					strcat(temp, temp2);
		
					startAddress = startAddress + 2;
					
					printf("\t\t %s\n\r", temp);
					break;
				default:
					printf("\n\r");
					break;		
			}					
		}	
		startAddress++;
	} 
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

	/*
	for(i = 0; i < linecount; i++) {
		printf("Line len: %02x\t Origin: %04x\t Checksum: %02x\t Calculated checksum: %02x\n\r", lineDetails[i].lineLen, lineDetails[i].origin, lineDetails[i].checksum, lineDetails[i].sum);
	}
	*/
	
	if(errorStatus == 0) {
		printf("S19 File Download Completed - %d Lines Read Into Memory\n\r", linecount);
		printf("Program starts at %04x\n\r", lineDetails[0].origin);
	}	
}

void demo() {	
	/*
	Function: Demo
	Operation: Demo program using a variable resistor to step a motor
	Returns: Integer error code
	Date: 25/03/2021
	Version: 1.1
	Change log:
	v1.0 - Read value on port E0 and produce an offset to delay the output on ports A0 - A3
	v1.1 - Changed offset from multiplication to addition to allow more granular control (smaller offsets for higher speed)
	Produced by: Jack Walker
	*/
	
	unsigned char *adControlStatus, *adResults1, *portA, *ddrA, portAMask, data;
	unsigned int i, delay;
	
	adControlStatus = (unsigned char*)0x30;
	adResults1 = (unsigned char*)0x31;
	
	/*Cast to pointers*/
	portA = (unsigned char *)0x00; 
	ddrA = (unsigned char *)0x01;
	*ddrA = 0xff;	
	
	/*printf("Demo\n\r");*/
	
	*adControlStatus =  0x20; /*Single continuous scan mode*/
	
	for(;;) {
		/*Wait for E0C*/
		while(((*adControlStatus) & 0x80) == 0x00); 
		
		/*printf("Data from E0 is %02x\n\r", *adResults1);*/
		
		/*Add 0xff to create delay*/
		delay = (*adResults1) + 0xff;
			
		/*printf("Delay is %04x\n\r", delay);*/
		
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		*portA = 0x01;

		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
			
		*portA = 0x03;

		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);
		
		*portA = 0x02;
				
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);
		
		*portA = 0x06;
	
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		*portA = 0x04;
		
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);		
		
		*portA = 0x0c;
		
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		data = 0x08;
				
		/*Delay based on resistor value read on E0*/
		for (i = 0; i < delay; i++);	
		
		*portA = 0x09;
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

