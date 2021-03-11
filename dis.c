#include <stdio.h>
#include <string.h>

typedef struct assemblyFunc {
    char functionName[10];
    int expectedArgs;
} assemblyFunc;

typedef struct extendedAssemblyFunc {
    char functionName[10];
    char functionCode;
    int expectedArgs;
} extendedAssemblyFunc;

int main() {    
    struct assemblyFunc functions[255];
	struct extendedAssemblyFunc extendedFunctions[15];
    unsigned char *startAddress, *endAddress, data, data2, i, extendedFlag;
    unsigned char stringInp[10];
    char temp[15], temp2[10], temp3[10];

    /*Populate functions array with assembly function data*/
    
    /*Addition Functions*/
    
    strcpy(functions[0x1B].functionName, "ABA ");
    functions[0x1B].expectedArgs = 0;
    
	strcpy(functions[0x3A].functionName, "ABX ");
    functions[0x3A].expectedArgs = 0;
    	
	/*ADCA*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0x89].functionName, "ADCA #$");
	functions[0x89].expectedArgs = 1;	
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x99].functionName, "ADCA $");
	functions[0x99].expectedArgs = 1;
	
	strcpy(functions[0xB9].functionName, "ADCA $");
	functions[0xB9].expectedArgs = 2;
	
	strcpy(functions[0xA9].functionName, "ADCA X, $");
	functions[0xA9].expectedArgs = 1;
	
	/*ADCB*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0xC9].functionName, "ADCB #$");
	functions[0xC9].expectedArgs = 1;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xD9].functionName, "ADCB $");
	functions[0xD9].expectedArgs = 1;
	
	strcpy(functions[0xF9].functionName, "ADCB $");
	functions[0xF9].expectedArgs = 2;
	
	strcpy(functions[0xE9].functionName, "ADCB X, $");
	functions[0xE9].expectedArgs = 1;
 
    /*ADDA*/
    
	/*Usually one byte but can be two*/	
	strcpy(functions[0x8B].functionName, "ADDA #$");
	functions[0x8B].expectedArgs = 1;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x9B].functionName, "ADDA $");
	functions[0x9B].expectedArgs = 1;

	strcpy(functions[0xBB].functionName, "ADDA $");
	functions[0xBB].expectedArgs = 2;
	
	strcpy(functions[0xAB].functionName, "ADDA X, $");
	functions[0xAB].expectedArgs = 1;
	
	/*ADDB*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0xCB].functionName, "ADDB #$");
	functions[0xCB].expectedArgs = 1;
		
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xDB].functionName, "ADDB $");
	functions[0xDB].expectedArgs = 1;
	
	strcpy(functions[0xFB].functionName, "ADDB $");
	functions[0xFB].expectedArgs = 2;
	
	strcpy(functions[0xEB].functionName, "ADDB X, $");
	functions[0xEB].expectedArgs = 1;
	
	/*ADDD*/
	
	strcpy(functions[0xC3].functionName, "ADDD #$");	
	functions[0xC3].expectedArgs = 2;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xD3].functionName, "ADDD $");
	functions[0xD3].expectedArgs = 1;
	
	strcpy(functions[0xF3].functionName, "ADDD $");
	functions[0xF3].expectedArgs = 2;
	
	strcpy(functions[0xE3].functionName, "ADDD X, $");
	functions[0xE3].expectedArgs = 1;
	
	/*Subtraction Functions*/
	
	/*SUBA*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0x80].functionName, "SUBA #$");
	functions[0x80].expectedArgs = 1;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x90].functionName, "SUBA $");
	functions[0x90].expectedArgs = 1;

	strcpy(functions[0xB0].functionName, "SUBA $");
	functions[0xB0].expectedArgs = 2;

	strcpy(functions[0xA0].functionName, "SUBA X, $");
	functions[0xA0].expectedArgs = 1;
	
	/*SUBB*/

	/*Usually one byte but can be two*/	
	strcpy(functions[0xC0].functionName, "SUBB #$");
	functions[0xC0].expectedArgs = 1;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
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
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0x86].functionName, "LDAA #$");
	functions[0x86].expectedArgs = 1;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x96].functionName, "LDAA $");
	functions[0x96].expectedArgs = 1;
	
	strcpy(functions[0xB6].functionName, "LDAA $");
	functions[0xB6].expectedArgs = 2;	
	
	strcpy(functions[0xA6].functionName, "LDAA X, $");
	functions[0xA6].expectedArgs = 1;
		
	/*LDAB*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0xC6].functionName, "LDAB #$");
	functions[0xC6].expectedArgs = 1;	
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
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
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x97].functionName, "STAA $");
	functions[0x97].expectedArgs = 1;
	
	strcpy(functions[0xB7].functionName, "STAA $");
	functions[0xB7].expectedArgs = 2;
	
	strcpy(functions[0xA7].functionName, "STAA X, $");
	functions[0xA7].expectedArgs = 1;
		
	/*STAB*/
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
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


	printf("Please enter start and end address in form [start] [end]: ");
	gets(stringInp);
	sscanf(stringInp, "%x %x", &startAddress, &endAddress);
	
	printf("Address\t Hex\t\t Assembly\n\r");
	
	/*Will loop until range is covered*/
	while (startAddress <= endAddress - 1) {
		/*Reset strings to null*/
		temp[0] = '\0';
		temp2[0] = '\0';
		temp3[0] = '\0';
		extendedFlag = 0;
						
		/*Get the hex value held at the start address*/
		data = *startAddress;
		
		/*Check for extended address functions*/
		if (data == 0x18) {
			/*Get the hex value held at start address + 1 (extended mode uses 2 byte code)*/
			data2 = *(startAddress + 1);
			
			/*Iterate through the array of extended address functions*/
			for (i = 0; i < 15; i++) {
				/*If function code matches data 2 (all extended are 0x18~~ in format)*/
				if (extendedFunctions[i].functionCode == data2) {
					extendedFlag = 1;
					/*Output address followed by data and data2 (this will output the function's full hex code)*/
					printf("%x\t %02x%02x", startAddress, data, data2);		
					strcpy(temp, extendedFunctions[i].functionName);
					
					/*Switch case based on the expected arguments
					This will ensure any relevant data is output with the function*/
					switch(extendedFunctions[i].expectedArgs){
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
			
			if (extendedFlag == 0) {
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
