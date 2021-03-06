#include <stdio.h>
#include <string.h>

/*Structure definitions*/
typedef struct {
	int hexValue;
	int expectedArgs;
	char functionName[5];	
} assemblyFunction;

void main() {
	unsigned int startAddress = 0, endAddress = 0;
	
	printf("Start address: ");
	scanf("%x", &startAddress);
	
	printf("End address: ");
	scanf("%x", &endAddress);
	
	
	disassemble(startAddress, endAddress);
}

int disassemble(unsigned int startAddress, unsigned int endAddress) {
	/*
	Function: Disassemble
	Operation: Convert hex into assembly language code
	Returns: Integer error code
	Date: 20/02/2021
	Version: 1.1
	Change log:
	v1.0 - Function stub outputting "disassemble"
	v1.1 - Added assemblyFunction structs and populated array with assembly function details
	Produced by: Jack Walker
	*/
	
	/*Step 1 - Create array of assemblyFunction structures*/
	/*Step 2 - Parse memory determining the function and expectedArgs for each*/
	/*Step 3 - Convert the hex to the corresponding function and read the expectedArgs as data*/
	/*Step 4 - Format output*/
	
	printf("Start address: %x\n\r", startAddress);	
	printf("End address: %x\n\r", endAddress);	
	printf("Disassemble\n\r");
	
	assemblyFunction hexCodes[70];	/*There are 70 assembly functions that must be handled for this assignment*/
	
	/*Filling array with struct values*/
	
	/*Addition Functitons*/
	
	hexCodes[0].hexValue = 0x1B;
	hexCodes[0].expectedArgs = 0;
	strcpy(hexCodes[0].functionName, "ABA");
	
	hexCodes[1].hexValue = 0x3A;
	hexCodes[1].expectedArgs = 0;
	strcpy(hexCodes[1].functionName, "ABX");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[2].hexValue = 0x183A;
	hexCodes[2].expectedArgs = 0;
	strcpy(hexCodes[2].functionName, "ABY");
	
	/*ADCA*/
	
	hexCodes[3].hexValue = 0x89;
	hexCodes[3].expectedArgs = 1;
	strcpy(hexCodes[3].functionName, "ADCA");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[4].hexValue = 0x99;
	hexCodes[4].expectedArgs = 2;
	strcpy(hexCodes[4].functionName, "ADCA");
	
	hexCodes[5].hexValue = 0xB9;
	hexCodes[5].expectedArgs = 2;
	strcpy(hexCodes[5].functionName, "ADCA");
	
	hexCodes[6].hexValue = 0xA9;
	hexCodes[6].expectedArgs = 1;
	strcpy(hexCodes[6].functionName, "ADCA");
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[7].hexValue = 0x18A9;
	hexCodes[7].expectedArgs = 1;
	strcpy(hexCodes[7].functionName, "ADCA");
	
	/*ADCB*/
	
	hexCodes[8].hexValue = 0xC9;
	hexCodes[8].expectedArgs = 1;
	strcpy(hexCodes[8].functionName, "ADCB");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[9].hexValue = 0xD9;
	hexCodes[9].expectedArgs = 2;
	strcpy(hexCodes[9].functionName, "ADCB");
	
	hexCodes[10].hexValue = 0xF9;
	hexCodes[10].expectedArgs = 2;
	strcpy(hexCodes[10].functionName, "ADCB");
	
	hexCodes[11].hexValue = 0xE9;
	hexCodes[11].expectedArgs = 1;
	strcpy(hexCodes[11].functionName, "ADCB");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[12].hexValue = 0x18E9;
	hexCodes[12].expectedArgs = 1;
	strcpy(hexCodes[12].functionName, "ADCB");
	
	/*ADDA*/
	
	hexCodes[13].hexValue = 0x8B;
	hexCodes[13].expectedArgs = 1;
	strcpy(hexCodes[13].functionName, "ADDA");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[14].hexValue = 0x9B;
	hexCodes[14].expectedArgs = 2;
	strcpy(hexCodes[14].functionName, "ADDA");
	
	hexCodes[15].hexValue = 0xBB;
	hexCodes[15].expectedArgs = 2;
	strcpy(hexCodes[15].functionName, "ADDA");
	
	hexCodes[16].hexValue = 0xAB;
	hexCodes[16].expectedArgs = 1;
	strcpy(hexCodes[16].functionName, "ADDA");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[17].hexValue = 0x18AB;
	hexCodes[17].expectedArgs = 1;
	strcpy(hexCodes[17].functionName, "ADDA");
	
	/*ADDB*/
	
	hexCodes[18].hexValue = 0xCB;
	hexCodes[18].expectedArgs = 1;
	strcpy(hexCodes[18].functionName, "ADDB");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[19].hexValue = 0xDB;
	hexCodes[19].expectedArgs = 2;
	strcpy(hexCodes[19].functionName, "ADDB");
	
	hexCodes[20].hexValue = 0xFB;
	hexCodes[20].expectedArgs = 2;
	strcpy(hexCodes[20].functionName, "ADDB");
	
	hexCodes[21].hexValue = 0xEB;
	hexCodes[21].expectedArgs = 1;
	strcpy(hexCodes[21].functionName, "ADDB");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[22].hexValue = 0x18EB;
	hexCodes[22].expectedArgs = 1;
	strcpy(hexCodes[22].functionName, "ADDB");
	
	/*ADDD*/
	
	hexCodes[23].hexValue = 0xC3;
	hexCodes[23].expectedArgs = 2;
	strcpy(hexCodes[23].functionName, "ADDD");
	
	hexCodes[24].hexValue = 0xD3;
	hexCodes[24].expectedArgs = 1;
	strcpy(hexCodes[24].functionName, "ADDD");
	
	hexCodes[25].hexValue = 0xF3;
	hexCodes[25].expectedArgs = 2;
	strcpy(hexCodes[25].functionName, "ADDD");
	
	hexCodes[26].hexValue = 0xE3;
	hexCodes[26].expectedArgs = 1;
	strcpy(hexCodes[26].functionName, "ADDD");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[27].hexValue = 0x18E3;
	hexCodes[27].expectedArgs = 1;
	strcpy(hexCodes[27].functionName, "ADDD");
	
	/*Subtraction Functions*/
	
	/*SUBA*/
	
	hexCodes[28].hexValue = 0x80;
	hexCodes[28].expectedArgs = 1;
	strcpy(hexCodes[28].functionName, "SUBA");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[29].hexValue = 0x90;
	hexCodes[29].expectedArgs = 2;
	strcpy(hexCodes[29].functionName, "SUBA");
	
	hexCodes[30].hexValue = 0xB0;
	hexCodes[30].expectedArgs = 2;
	strcpy(hexCodes[30].functionName, "SUBA");
	
	hexCodes[31].hexValue = 0xA0;
	hexCodes[31].expectedArgs = 1;
	strcpy(hexCodes[31].functionName, "SUBA");
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[32].hexValue = 0x18A0;
	hexCodes[32].expectedArgs = 1;
	strcpy(hexCodes[32].functionName, "SUBA");
	
	/*SUBB*/
	
	hexCodes[33].hexValue = 0xC0;
	hexCodes[33].expectedArgs = 1;
	strcpy(hexCodes[33].functionName, "SUBB");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[34].hexValue = 0xD0;
	hexCodes[34].expectedArgs = 2;
	strcpy(hexCodes[34].functionName, "SUBB");
	
	hexCodes[35].hexValue = 0xF0;
	hexCodes[35].expectedArgs = 2;
	strcpy(hexCodes[35].functionName, "SUBB");
	
	hexCodes[36].hexValue = 0xE0;
	hexCodes[36].expectedArgs = 1;
	strcpy(hexCodes[36].functionName, "SUBB");
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[37].hexValue = 0x18E0;
	hexCodes[37].expectedArgs = 1;
	strcpy(hexCodes[37].functionName, "SUBB");
		
	/*SUBD*/
	
	hexCodes[38].hexValue = 0x83;
	hexCodes[38].expectedArgs = 2;
	strcpy(hexCodes[38].functionName, "SUBD");
	
	hexCodes[39].hexValue = 0x93;
	hexCodes[39].expectedArgs = 1;
	strcpy(hexCodes[39].functionName, "SUBD");
	
	hexCodes[40].hexValue = 0xB3;
	hexCodes[40].expectedArgs = 2;
	strcpy(hexCodes[40].functionName, "SUBD");
	
	hexCodes[41].hexValue = 0xA3;
	hexCodes[41].expectedArgs = 1;
	strcpy(hexCodes[41].functionName, "SUBD");
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[42].hexValue = 0x18A3;
	hexCodes[42].expectedArgs = 1;
	strcpy(hexCodes[42].functionName, "SUBD");
	
	/*Load Accumulator Functions*/	
	
	/*LDAA*/
	
	hexCodes[43].hexValue = 0x86;
	hexCodes[43].expectedArgs = 1;
	strcpy(hexCodes[43].functionName, "LDAA");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[44].hexValue = 0x96;
	hexCodes[44].expectedArgs = 2;
	strcpy(hexCodes[44].functionName, "LDAA");
	
	hexCodes[45].hexValue = 0xB6;
	hexCodes[45].expectedArgs = 2;
	strcpy(hexCodes[45].functionName, "LDAA");
	
	hexCodes[46].hexValue = 0xA6;
	hexCodes[46].expectedArgs = 1;
	strcpy(hexCodes[46].functionName, "LDAA");
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[47].hexValue = 0x18A6;
	hexCodes[47].expectedArgs = 1;
	strcpy(hexCodes[47].functionName, "LDAA");
		
	/*LDAB*/
	
	hexCodes[48].hexValue = 0xC6;
	hexCodes[48].expectedArgs = 1;
	strcpy(hexCodes[48].functionName, "LDAB");
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[49].hexValue = 0xD6;
	hexCodes[49].expectedArgs = 2;
	strcpy(hexCodes[49].functionName, "LDAB");
	
	hexCodes[50].hexValue = 0xF6;
	hexCodes[50].expectedArgs = 2;
	strcpy(hexCodes[50].functionName, "LDAB");
	
	hexCodes[51].hexValue = 0xE6;
	hexCodes[51].expectedArgs = 1;
	strcpy(hexCodes[51].functionName, "LDAB");
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[52].hexValue = 0x18E6;
	hexCodes[52].expectedArgs = 1;
	strcpy(hexCodes[52].functionName, "LDAB");
	
	/*LDD*/
	
	hexCodes[53].hexValue = 0xCC;
	hexCodes[53].expectedArgs = 2;
	strcpy(hexCodes[53].functionName, "LDD");
	
	hexCodes[54].hexValue = 0xDC;
	hexCodes[54].expectedArgs = 1;
	strcpy(hexCodes[54].functionName, "LDD");
	
	hexCodes[55].hexValue = 0xFC;
	hexCodes[55].expectedArgs = 2;
	strcpy(hexCodes[55].functionName, "LDD");
	
	hexCodes[56].hexValue = 0xEC;
	hexCodes[56].expectedArgs = 1;
	strcpy(hexCodes[56].functionName, "LDD");
		
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[57].hexValue = 0x18EC;
	hexCodes[57].expectedArgs = 1;
	strcpy(hexCodes[57].functionName, "LDD");
	
	/*Store Accumulator Functions*/
	
	/*STAA*/
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[58].hexValue = 0x97;
	hexCodes[58].expectedArgs = 2;
	strcpy(hexCodes[58].functionName, "STAA");
	
	hexCodes[59].hexValue = 0xB7;
	hexCodes[59].expectedArgs = 2;
	strcpy(hexCodes[59].functionName, "STAA");
	
	hexCodes[60].hexValue = 0xA7;
	hexCodes[60].expectedArgs = 1;
	strcpy(hexCodes[60].functionName, "STAA");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[61].hexValue = 0x18A7;
	hexCodes[61].expectedArgs = 1;
	strcpy(hexCodes[61].functionName, "STAA");

	/*STAB*/
	
	/*Unsure about the accepted args for this as it can take 2 but will assume top is 00*/	
	hexCodes[62].hexValue = 0xD7;
	hexCodes[62].expectedArgs = 2;
	strcpy(hexCodes[62].functionName, "STAB");
	
	hexCodes[63].hexValue = 0xF7;
	hexCodes[63].expectedArgs = 2;
	strcpy(hexCodes[63].functionName, "STAB");
	
	hexCodes[64].hexValue = 0xE7;
	hexCodes[64].expectedArgs = 1;
	strcpy(hexCodes[64].functionName, "STAB");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[65].hexValue = 0x18E7;
	hexCodes[65].expectedArgs = 1;
	strcpy(hexCodes[65].functionName, "STAB");
	
	/*STD/STAD*/

	hexCodes[66].hexValue = 0xDD;
	hexCodes[66].expectedArgs = 1;
	strcpy(hexCodes[66].functionName, "STD");
	
	hexCodes[67].hexValue = 0xFD;
	hexCodes[67].expectedArgs = 2;
	strcpy(hexCodes[67].functionName, "STD");
	
	hexCodes[68].hexValue = 0xED;
	hexCodes[68].expectedArgs = 1;
	strcpy(hexCodes[68].functionName, "STD");
	
	/*Unsure about hex code when using extended due to it actually needing two hex values*/	
	hexCodes[69].hexValue = 0x18ED;
	hexCodes[69].expectedArgs = 1;
	strcpy(hexCodes[69].functionName, "STD");
	
	/*int i = 0;
	
	for (i; i < 70; i++) {
		printf("hexCodes[%d]\n\r"
		"Hex Value: %x\n\r"
		"Expected Arguments: %x\n\r"
		"Function Name: %s\n\n\r",
		i, hexCodes[i].hexValue, hexCodes[i].expectedArgs, hexCodes[i].functionName);
	}*/
}
