//  On my honor: 
//    
//  - I have not discussed the C language code in my program with 
//    anyone other than my instructor or the teaching assistants  
//    assigned to this course. 
//    
//  - I have not used C language code obtained from another student,  
//    the Internet, or any other unauthorized source, either modified 
//    or unmodified.   
//    
//  - If any C language code or documentation used in my program  
//    was obtained from an authorized source, such as a text book or 
//    course notes, that has been clearly noted with a proper citation 
//    in the comments of my program. 
//    
//  - I have not designed this program in such a way as to defeat or 
//    interfere with the normal operation of the grading code.
// 
//    Gannon Palm
//    gwpalm42
#include "ASMParser.h"
#include "LookupTable.h"

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include <unistd.h>

/** Breaks up given the MIPS32 assembly instruction and creates a proper
* ParseResult object storing information about that instruction.
*
* Pre: pASM points to an array holding the representation of a
* syntactically valid assembly instruction.
*
* The instruction will be formatted as follows:
*
* <mnemonic><ws><operand1>,<ws><operand2>,<ws>...
*
* where <ws> is an arbitrary mixture of space and tab characters.
*
* Returns:
* A pointer to a proper ParseResult object whose fields have been
* correctly initialized to correspond to the target of pASM.
*/
ParseResult* parseASM(const char* const pASM, LabelHandler* const pLH, int insAddress) {
    
	ParseResult* result = (ParseResult*)calloc(10, sizeof(ParseResult));
	
	//figure out instruction type
	result->ASMInstruction = (char*) calloc(100, sizeof(char)); 
	strcpy(result->ASMInstruction, pASM); //store instruction into result
	
	//store the mnemonicF
	char* tokenpASM = (char*) pASM;
	result->Mnemonic = (char*) calloc(15, sizeof(char));
	strcpy(result->Mnemonic, strtok(tokenpASM, " ")); //grab mnemonic
	//use lookup tables to fill in instruction.
	if(strcmp(result->Mnemonic, "add") == 0 ||
	strcmp(result->Mnemonic, "sub") == 0 ||
	strcmp(result->Mnemonic, "mul") == 0 || 
	strcmp(result->Mnemonic, "and") == 0 ||
	strcmp(result->Mnemonic, "nor") == 0 ||
	strcmp(result->Mnemonic, "addu") == 0 ||
	strcmp(result->Mnemonic, "slt") == 0 ||
	strcmp(result->Mnemonic, "srav") == 0) {
		
		LookupType LT;

		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rd
		result->rdName = (char*) calloc(10, sizeof(char));
		strcpy(result->rdName, strtok(NULL, ", "));
		result->RD = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RD, Find(result->rdName, LT)-> Code);
		result->rd = Find(result->rdName, LT)->RegisterNumber;
		
		//rs
		result->rsName = (char*) calloc(10, sizeof(char));
		strcpy(result->rsName, strtok(NULL, ", "));
		result->RS = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RS, Find(result->rsName, LT)-> Code);
		result->rs = Find(result->rsName, LT)->RegisterNumber;
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, " "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		//funct
		result->Funct = (char*) calloc(10, sizeof(char));
		LT = FUNCT;
		strcpy(result->Funct, Find(result->Mnemonic, LT)-> Code);
		
		//null out unused stuff
		result->Imm = 0;
		result->IMM = NULL;
		
		return result;
	}
	else if (strcmp(result->Mnemonic, "addi") == 0 ||
	strcmp(result->Mnemonic, "andi") == 0 ||
	strcmp(result->Mnemonic, "slti") == 0 ||
	strcmp(result->Mnemonic, "addiu") == 0) {
		LookupType LT;
		
		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, ", "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		//rs
		result->rsName = (char*) calloc(10, sizeof(char));
		strcpy(result->rsName, strtok(NULL, ", "));
		result->RS = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RS, Find(result->rsName, LT)-> Code);
		result->rs = Find(result->rsName, LT)->RegisterNumber;

		//immediate
		result->Imm = atoi(strtok(NULL, " "));
		result->IMM = (char*) calloc(20, sizeof(char));
		DecimalToBinary16(result->Imm, result->IMM);
		
		//null out unused things
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		result->Funct = NULL;
		
		return result;
	}
	//opcode rs rt imm
	else if (strcmp(result->Mnemonic, "beq") == 0 ||
	strcmp(result->Mnemonic, "bne") == 0 ||
	strcmp(result->Mnemonic, "blez") == 0 ||
	strcmp(result->Mnemonic, "bgtz") == 0){
		
		LookupType LT;
		
		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rs
		result->rsName = (char*) calloc(10, sizeof(char));
		strcpy(result->rsName, strtok(NULL, ", "));
		result->RS = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RS, Find(result->rsName, LT)-> Code);
		result->rs = Find(result->rsName, LT)->RegisterNumber;
		
		if (strcmp(result->Mnemonic, "blez") == 0 ||
			strcmp(result->Mnemonic, "bgtz") == 0) {
			result->RT = (char*) calloc(10, sizeof(char));
			strcpy(result->RT, "00000");
		}
		else {
			//rt
			result->rtName = (char*) calloc(10, sizeof(char));
			strcpy(result->rtName, strtok(NULL, ", "));
			result->RT = (char*) calloc(10, sizeof(char));
			LT = REGISTER;
			strcpy(result->RT, Find(result->rtName, LT)-> Code);
			result->rt = Find(result->rtName, LT)->RegisterNumber;
		}
		
		//jump amount. Uses labels. pLH
		result->Imm = (getLabelAddress(pLH, strtok(NULL, " ")) - insAddress)/4 - 1;
		result->IMM = (char*) calloc(20, sizeof(char));
		DecimalToBinary16(result->Imm, result->IMM);
		
		//null out unused things
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		result->Funct = NULL;
		
		return result;
	}
	else if (strcmp(result->Mnemonic, "lw") == 0 ||
	strcmp(result->Mnemonic, "sw") == 0 ) {
		
		LookupType LT;
		
		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, ", "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		//either immediate or label pseudoinstruction
		char* labelOrIMM = strtok(NULL, "(");
		//check for label case before continuing
		if (isdigit(labelOrIMM[1]) == 0 && labelOrIMM[1] != '-') { //Label case.
			char* address = strtok(labelOrIMM, " ");
			result->Imm = getLabelAddress(pLH, address);
			result->IMM = (char*) calloc(20, sizeof(char));
			DecimalToBinary16(result->Imm, result->IMM);
			result->rsName = (char*) calloc(10, sizeof(char));
			strcpy(result->rsName, "$zero");
			result->RS = (char*) calloc(10, sizeof(char));
			LT = REGISTER;
			strcpy(result->RS, Find(result->rsName, LT)-> Code);
			result->rs = Find(result->rsName, LT)->RegisterNumber;
			return result;
		}
		
		result->Imm = atoi(labelOrIMM);
		result->IMM = (char*) calloc(20, sizeof(char));
		DecimalToBinary16(result->Imm, result->IMM);
		
		//rs
		result->rsName = (char*) calloc(10, sizeof(char));
		strcpy(result->rsName, strtok(NULL, ")"));
		result->RS = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RS, Find(result->rsName, LT)-> Code);
		result->rs = Find(result->rsName, LT)->RegisterNumber;
		
		//null out unused things
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		result->Funct = NULL;
		
		return result;
	}
	else if (strcmp(result->Mnemonic, "lui") == 0){
			
		LookupType LT;
		
		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, ", "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		//immediate
		result->Imm = atoi(strtok(NULL, " "));
		result->IMM = (char*) calloc(20, sizeof(char));
		DecimalToBinary16(result->Imm, result->IMM);
		
		//rs
		result->RS= (char*) calloc(20, sizeof(char));
		strcpy(result->RS, "00000");
		result->rs = 0;
		
		//null out unused things
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		result->rsName = NULL;
		result->Funct = NULL;
		
		return result;
	}
	//syscall
	else if (strcmp(result->Mnemonic, "syscall") == 0) {
		result->Opcode = (char*) calloc(10, sizeof(char));
		result->Funct = (char*) calloc(10, sizeof(char));
		
		strcpy(result->Opcode, "000000");
		strcpy(result->Funct, "001100");
		
		return result;
	}
	//000000 rs rt 0000000000 funct
	else if (strcmp(result->Mnemonic, "mult") == 0) {
		
		LookupType LT;
		
		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rs
		result->rsName = (char*) calloc(10, sizeof(char));
		strcpy(result->rsName, strtok(NULL, ", "));
		result->RS = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RS, Find(result->rsName, LT)-> Code);
		result->rs = Find(result->rsName, LT)->RegisterNumber;
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, " "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		//rd
		result->RD = (char*) calloc(10, sizeof(char));
		strcpy(result->RD, "00000");
		
		//funct
		result->Funct = (char*) calloc(10, sizeof(char));
		LT = FUNCT;
		strcpy(result->Funct, Find(result->Mnemonic, LT)-> Code);
		
		//null out unused stuff
		result->Imm = 0;
		result->IMM = NULL;
		
		return result;
	}
	//pseudo instruction. turns into opcode rs $zero imm
	else if (strcmp(result->Mnemonic, "la") == 0 ||
		strcmp(result->Mnemonic, "li") == 0 || 
		strcmp(result->Mnemonic, "move") == 0) {
		LookupType LT;

		//opcode
		result->Opcode = (char*) calloc(15, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, ", "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		//rs
		result->rsName = (char*) calloc(10, sizeof(char));
		strcpy(result->rsName, "$zero");
		result->RS = (char*) calloc(10, sizeof(char));
		strcpy(result->RS, "00000");
		result->rs = Find(result->rsName, LT)->RegisterNumber;

		//LABEL/IMM
		if (strcmp(result->Mnemonic, "li") == 0) {
			result->Imm = atoi(strtok(NULL, " "));
			result->IMM = (char*) calloc(20, sizeof(char));
			DecimalToBinary16(result->Imm, result->IMM);
		}
		else if (strcmp(result->Mnemonic, "la") == 0) {
			result->Imm = getLabelAddress(pLH, strtok(NULL, " "));
			result->IMM = (char*) calloc(20, sizeof(char));
			DecimalToBinary16(result->Imm, result->IMM);
		} 
		else { //move
			result->rdName = (char*) calloc(10, sizeof(char));
			strcpy(result->rdName, strtok(NULL, " "));
			result->RD = (char*) calloc(10, sizeof(char));
			strcpy(result->RD, Find(result->rdName, LT)-> Code);
			//funct
			result->Funct = (char*) calloc(10, sizeof(char));
			LT = FUNCT;
			strcpy(result->Funct, Find(result->Mnemonic, LT)-> Code);
			return result;
		}
		
		//null out unused things
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		result->Funct = NULL;
		
		return result;
	}
	
	else if (strcmp(result->Mnemonic, "sra") == 0 ||
		strcmp(result->Mnemonic, "sll") == 0) {
		LookupType LT;

		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		LT = OPCODE;
		strcpy(result->Opcode, Find(result->Mnemonic, LT)-> Code);
		
		//rd
		result->rdName = (char*) calloc(10, sizeof(char));
		strcpy(result->rdName, strtok(NULL, ", "));
		result->RD = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RD, Find(result->rdName, LT)-> Code);
		result->rd = Find(result->rdName, LT)->RegisterNumber;
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, ", "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		//rs will be used to hold sa
		result->RS = (char*) calloc(10, sizeof(char));
		DecimalToBinary5(atoi(strtok(NULL, " ")), result->RS);
		
		//funct
		result->Funct = (char*) calloc(10, sizeof(char));
		LT = FUNCT;
		strcpy(result->Funct, Find(result->Mnemonic, LT)-> Code);
		
		//null out unused stuff
		result->Imm = 0;
		result->IMM = NULL;
		
		return result;
	}
	else if (strcmp(result->Mnemonic, "j") == 0) { 
		//opcode
		result->Opcode = (char*) calloc(10, sizeof(char));
		strcpy(result->Opcode, "000010");
		
		//LABEL
		result->Imm = getLabelAddress(pLH, strtok(NULL, " "))/4;
		result->IMM = (char*) calloc(20, sizeof(char));
		DecimalToBinary16(result->Imm, result->IMM);
		
		return result;
	}
	//blt is weird!
	else if (strcmp(result->Mnemonic, "blt") == 0) {
		LookupType LT;
		
		//rs
		result->rsName = (char*) calloc(10, sizeof(char));
		strcpy(result->rsName, strtok(NULL, ", "));
		result->RS = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RS, Find(result->rsName, LT)-> Code);
		result->rs = Find(result->rsName, LT)->RegisterNumber;
		
		//rt
		result->rtName = (char*) calloc(10, sizeof(char));
		strcpy(result->rtName, strtok(NULL, ", "));
		result->RT = (char*) calloc(10, sizeof(char));
		LT = REGISTER;
		strcpy(result->RT, Find(result->rtName, LT)-> Code);
		result->rt = Find(result->rtName, LT)->RegisterNumber;
		
		char* labelOrIMM = strtok(NULL, " ");
		//check for label case before continuing
		if (isdigit(labelOrIMM[1]) == 0 && labelOrIMM[1] != '-') { //Label case.
		    result->Imm = (getLabelAddress(pLH, labelOrIMM) - (insAddress+8)) /4;
			result->IMM = (char*) calloc(20, sizeof(char));
			DecimalToBinary16(result->Imm, result->IMM);
			return result;
		}
		
		//immediate
		result->Imm = atoi(labelOrIMM);
		result->IMM = (char*) calloc(20, sizeof(char));
		DecimalToBinary16(result->Imm, result->IMM);
		
		return result;
	}
	else if (strcmp(result->Mnemonic, "nop") == 0) { 
		return result;
	}
	
    return NULL; //return null if invalid mnemonic
}

/**
 * This helper method takes an int from Imm and writes the binary
 * version of the number as a string into IMM. 
 * 16 bit version. 
 */
void DecimalToBinary16(int16_t Imm, char* IMM) {
    char binStr[17];
    binStr[16] = '\0';
    for (int i = 0; i < 16; i++)
    {
		//make a binary number that only has a 1 in the desired index
		//and then AND it with Imm to see if there is 1 in that index.
        int mask = 1 << (15 - i);
        if (Imm & mask) {
			binStr[i] = '1';
		}
        else {
            binStr[i] = '0';
        }
   }
   strcpy(IMM, binStr);
}
/**
 * This helper method takes an int from Imm and writes the binary
 * version of the number as a string into IMM. 
 * 32 bit version. 
 */
void DecimalToBinary32(int num, char* output) {
    char binStr[33];
    binStr[32] = '\0';
    for (int i = 0; i < 32; i++)
    {
		//make a binary number that only has a 1 in the desired index
		//and then AND it with Imm to see if there is 1 in that index.
        int mask = 1 << (31 - i);
        if (num & mask) {
			binStr[i] = '1';
		}
        else {
            binStr[i] = '0';
        }
   }
   strcpy(output, binStr);
}
//helper method that uses 8 bits.
void DecimalToBinary8(int num, char* output) {
	char binStr[9];
    binStr[8] = '\0';
    for (int i = 0; i < 8; i++)
    {
        int mask = 1 << (7 - i);
        if (num & mask) {
			binStr[i] = '1';
		}
        else {
            binStr[i] = '0';
        }
   }
   strcpy(output, binStr);
}
// I know this is a ridiculous amount of converter methods
// but I need a 5 bit converter for the sa in sra and sll
//
// it has now dawned on me that I could have had the bit amount
// be a paramter but the program is due tn and everything works rn
void DecimalToBinary5(int num, char* output) {
	char binStr[6];
    binStr[5] = '\0';
    for (int i = 0; i < 5; i++)
    {
        int mask = 1 << (4 - i);
        if (num & mask) {
			binStr[i] = '1';
		}
        else {
            binStr[i] = '0';
        }
   }
   strcpy(output, binStr);
}
