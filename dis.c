#include <stdio.h>
#include <string.h>

typedef struct assemblyFunc {
    char functionName[10];
    int expectedArgs;
} assemblyFunc;

int main() {    
    struct assemblyFunc functions[255];
    unsigned char *startAddress, *endAddress, data, data2;
    unsigned char stringInp[10];
    char temp[15], temp2[10], temp3[10];

    /*Populate functions array with assembly function data*/
    
    /*Addition Functions*/
    
    strcpy(functions[0x1B].functionName, "ABA ");
    functions[0x1B].expectedArgs = 0;
    
	strcpy(functions[0x3A].functionName, "ABX ");
    functions[0x3A].expectedArgs = 0;
    
	/*Unsure about hex code when using extended due to it actually needing two hex values*/ 
/*    
	strcpy(functions[0x183A].functionName, "ABY ");
	functions[0x183A].expectedArgs = 0;
*/
	
	/*ADCA*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0x89].functionName, "ADCA #$");
	functions[0x89].expectedArgs = 2;	
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x99].functionName, "ADCA $");
	functions[0x99].expectedArgs = 2;
	
	strcpy(functions[0xB9].functionName, "ADCA $");
	functions[0xB9].expectedArgs = 2;
	
	strcpy(functions[0xA9].functionName, "ADCA $x, ");
	functions[0xA96].expectedArgs = 1;

	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*		
	strcpy(functions[0x18A9].functionName, "ADCA $y, ");
	functions[0x18A9].expectedArgs = 1;
*/
	
	/*ADCB*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0xC9].functionName, "ADCB #$");
	functions[0xC9].expectedArgs = 2;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xD9].functionName, "ADCB $");
	functions[0xD9].expectedArgs = 2;
	
	strcpy(functions[0xF9].functionName, "ADCB $");
	functions[0xF9].expectedArgs = 2;
	
	strcpy(functions[0xE9].functionName, "ADCB $x, ");
	functions[0xE9].expectedArgs = 1;

	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*	
	strcpy(functions[0x18E9].functionName, "ADCB $y, ");
    functions[0x18E9].expectedArgs = 1;
*/
    
    /*ADDA*/
    
	/*Usually one byte but can be two*/	
	strcpy(functions[0x8B].functionName, "ADDA #$");
	functions[0x8B].expectedArgs = 2;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x9B].functionName, "ADDA $");
	functions[0x9B].expectedArgs = 2;

	strcpy(functions[0xBB].functionName, "ADDA $");
	functions[0xBB].expectedArgs = 2;
	
	strcpy(functions[0xAB].functionName, "ADDA $x, ");
	functions[0xAB].expectedArgs = 1;

	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18AB].functionName, "ADDA $y, ");
	functions[0x18AB].expectedArgs = 1;
*/
	
	/*ADDB*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0xCB].functionName, "ADDB #$");
	functions[0xCB].expectedArgs = 2;
		
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xDB].functionName, "ADDB $");
	functions[0xDB].expectedArgs = 2;
	
	strcpy(functions[0xFB].functionName, "ADDB $");
	functions[0xFB].expectedArgs = 2;
	
	strcpy(functions[0xEB].functionName, "ADDB $x, ");
	functions[0xEB].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18EB].functionName, "ADDB $y, ");
	functions[0x18EB].expectedArgs = 1;
*/

	/*ADDD*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0xC3].functionName, "ADDD #$");	
	functions[0xC3].expectedArgs = 2;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xD3].functionName, "ADDD $");
	functions[0xD3].expectedArgs = 1;
	
	strcpy(functions[0xF3].functionName, "ADDD $");
	functions[0xF3].expectedArgs = 2;
	
	strcpy(functions[0xE3].functionName, "ADDD $x, ");
	functions[0xE3].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18E3].functionName, "ADDD $y, ");
	functions[0x18E3].expectedArgs = 1;
*/	

	/*Subtraction Functions*/
	
	/*SUBA*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0x80].functionName, "SUBA #$");
	functions[0x80].expectedArgs = 2;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x90].functionName, "SUBA $");
	functions[0x90].expectedArgs = 2;

	strcpy(functions[0xB0].functionName, "SUBA $");
	functions[0xB0].expectedArgs = 2;

	strcpy(functions[0xA0].functionName, "SUBA $x, ");
	functions[0xA0].expectedArgs = 1;
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18A0].functionName, "SUBA $y, ");
	functions[0x18A0].expectedArgs = 1;	
*/	

	/*SUBB*/

	/*Usually one byte but can be two*/	
	strcpy(functions[0xC0].functionName, "SUBB #$");
	functions[0xC0].expectedArgs = 2;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xD0].functionName, "SUBB $");
	functions[0xD0].expectedArgs = 2;
	
	strcpy(functions[0xF0].functionName, "SUBB $");
	functions[0xF0].expectedArgs = 2;
	
	strcpy(functions[0xE0].functionName, "SUBB $x, ");
	functions[0xE0].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	functions[0x18E0].expectedArgs = 1;
	strcpy(functions[0x18E0].functionName, "SUBB $y, ");
*/
	
	/*SUBD*/
	
	strcpy(functions[0x83].functionName, "SUBD #$");
	functions[0x83].expectedArgs = 2;
	
	strcpy(functions[0x93].functionName, "SUBD $");
	functions[0x93].expectedArgs = 1;
	
	strcpy(functions[0xB3].functionName, "SUBD $");
	functions[0xB3].expectedArgs = 2;
	
	strcpy(functions[0xA3].functionName, "SUBD $x, ");
	functions[0xA3].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18A3].functionName, "SUBD $y, ");
	functions[0x18A3].expectedArgs = 1;
*/
	
	/*Load Accumulator Functions*/	
	
	/*LDAA*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0x86].functionName, "LDAA #$");
	functions[0x86].expectedArgs = 1;
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x96].functionName, "LDAA $");
	functions[0x96].expectedArgs = 2;
	
	strcpy(functions[0xB6].functionName, "LDAA $");
	functions[0xB6].expectedArgs = 2;	
	
	strcpy(functions[0xA6].functionName, "LDAA $x, ");
	functions[0xA6].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18A6].functionName, "LDAA $y, ");
	functions[0x18A6].expectedArgs = 1;
*/
	
	/*LDAB*/
	
	/*Usually one byte but can be two*/	
	strcpy(functions[0xC6].functionName, "LDAB #$");
	functions[0xC6].expectedArgs = 1;	
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xD6].functionName, "LDAB $");
	functions[0xD6].expectedArgs = 2;	
	
	strcpy(functions[0xF6].functionName, "LDAB $");
	functions[0xF6].expectedArgs = 2;
	
	strcpy(functions[0xE6].functionName, "LDAB $x, ");
	functions[0xE6].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18E6].functionName, "LDAB $y, ");
	functions[0x18E6].expectedArgs = 1;	
*/

	/*LDD/LDAD*/
	
	strcpy(functions[0xCC].functionName, "LDD #$");
	functions[0xCC].expectedArgs = 2;
	
	strcpy(functions[0xDC].functionName, "LDD $");
	functions[0xDC].expectedArgs = 1;
	
	strcpy(functions[0xFC].functionName, "LDD $");
	functions[0xFC].expectedArgs = 2;
	
	strcpy(functions[0xEC].functionName, "LDD $x, ");
	functions[0xEC].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
/*
	strcpy(functions[0x18EC].functionName, "LDD $y, ");
	functions[0x18EC].expectedArgs = 1;	
*/
	
	/*Store Accumulator Functions*/
	
	/*STAA*/
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0x97].functionName, "STAA $");
	functions[0x97].expectedArgs = 2;
	
	strcpy(functions[0xB7].functionName, "STAA $");
	functions[0xB7].expectedArgs = 2;
	
	strcpy(functions[0xA7].functionName, "STAA $x, ");
	functions[0xA7].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	functions[0x18A7].expectedArgs = 1;
	strcpy(functions[0x18A7].functionName, "STAA $y, ");
*/
	
	/*STAB*/
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	strcpy(functions[0xD7].functionName, "STAB $");
	functions[0xD7].expectedArgs = 2;
	
	strcpy(functions[0xF7].functionName, "STAB $");
	functions[0xF7].expectedArgs = 2;
	
	strcpy(functions[0xE7].functionName, "STAB $x, ");
	functions[0xE7].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18E7].functionName, "STAB $y, ");
	functions[0x18E7].expectedArgs = 1;
*/
	
	/*STD/STAD*/
	
	
	strcpy(functions[0xDD].functionName, "STD $");
	functions[0xDD].expectedArgs = 1;
	
	strcpy(functions[0xFD].functionName, "STD $");
	functions[0xFD].expectedArgs = 2;
	
	strcpy(functions[0xED].functionName, "STD $x, ");
	functions[0xED].expectedArgs = 1;
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/
/*
	strcpy(functions[0x18ED].functionName, "STAD $y, ");
	functions[0x18ED].expectedArgs = 1;
*/

	printf("Please enter start and end address in form [start] [end]: ");
	gets(stringInp);
	sscanf(stringInp, "%x %x", &startAddress, &endAddress);
	printf("Start address: %x\n\r", startAddress);
	printf("End address: %x\n\r", endAddress);	
		
	while (startAddress <= endAddress) {
		temp[0] = '\0';
		temp2[0] = '\0';
		temp3[0] = '\0';
	
		data = *startAddress;
		
		printf("%x\t %x", startAddress, data);
				
		strcpy(temp, functions[data].functionName);
		printf("\t %s\t", temp);
			 
		if (functions[data].expectedArgs == 1) {
		
			strcpy(temp, functions[data].functionName);
						
        	data = *(startAddress + 1);
    		sprintf(temp2, "%02x", data);
    		
    		strcat(temp, temp2);	
					
			startAddress++;
		}
		if (functions[data].expectedArgs == 2) {
			strcpy(temp, functions[data].functionName);
						
        	data = *(startAddress + 1);
    		sprintf(temp2, "%02x", data);
						
			data = *(startAddress + 2);
			sprintf(temp3, "%02x", data);
			
			strcat(temp2, temp3);
				
			strcat(temp, temp2);

			startAddress = startAddress + 2;
		}
		if (functions[data].expectedArgs >= 0) {
			printf("\t %s", temp);	
		} else {
			printf("\t .....");
		}
		
		printf("\n\r");		
		startAddress++;
	} 
	
}
