#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Function: Menu (Now integrated directly into main)
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

void main(void) {
	char inputString[20], inputMode[8], checkString[8], checkString2[8];
	unsigned int validData = 0, operationMode = 0, inputStartAddress = 0, inputEndAddress = 0, i;
	unsigned char check, check2;
	
	for(;;) {
		printf("Welcome to Jack's 68HC11 MiniOS!\n\r");
		printf("Please select one of the following operational modes:\n\r");
		printf("Modify Memory - mm [START ADDRESS]\n\r");
		printf("Display Memory - dm [START ADDRESS]\n\r");
		printf("Disassemble Code - dis [START ADDRESS] [END ADDRESS]\n\r");
		printf("Load File - lf\n\r");
		printf("Demo Program - demo\n\r");
		
		do {
			
			/*Clear variables to reduce risk of error*/
			inputMode[0] = '\0';
			inputStartAddress = 0;
			inputEndAddress = 0;
			operationMode = 0;
			validData = 0;
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
							operationMode = 1;
							validData = 1;
							
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
							operationMode = 2;
							validData = 1;
							
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
								operationMode = 3;
								validData = 1;
								
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
				operationMode = 4;
				validData = 1;
			
			} else if(strcmp(inputMode, "demo") == 0) {	
			
				/*If any extra data is given, ignore it*/
				if(inputStartAddress != 0 || inputEndAddress != 0) {
					printf("Additional data has been ignored.\n\r");
				}						
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

