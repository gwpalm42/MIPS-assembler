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
#include "ParseResult.h"
#include <stdlib.h>
#include <string.h>

/**  Frees the dynamic content of a ParseResult object.
 * 
 *   Pre:  pPR points to a proper ParseResult object.
 *   Post: All of the dynamically-allocated arrays in *pPR have been
 *         deallocated; pointers are NULL, static fields are reset to
 *         default values.
 * 
 *   Comments:
 *     -  The function has no information about whether *pPR has been
 *        allocated dynamically, so it cannot risk attempting to 
 *        deallocate *pPR.
 *     -  The function is intended to provide the user with a simple
 *        way to free memory; the user may or may not reuse *pPR.  So,
 *        the function does set the pointers in *pPR to NULL.
 */
void clearResult(ParseResult* const pPR) {
   //char* frees
	free(pPR->ASMInstruction);
	pPR->ASMInstruction = NULL;
	free(pPR->Mnemonic);
	pPR->Mnemonic = NULL;
	free(pPR->rdName);
	pPR->rdName = NULL;
	free(pPR->rsName);
	pPR->rsName = NULL;
	free(pPR->rtName);
	pPR->rtName = NULL;
	free(pPR->Opcode);
	pPR->Opcode = NULL;
	free(pPR->Funct);
	pPR->Funct = NULL;
	free(pPR->RD);
	pPR->RD = NULL;
	free(pPR->RS);
	pPR->RS = NULL;
	free(pPR->RT);
	pPR->RT = NULL;
	free(pPR->IMM);
	pPR->IMM = NULL;
	//integer resets
	pPR->rd = 0;
	pPR->rs = 0;
	pPR->rt = 0;
	pPR->Imm = 0;
}

/**  Prints the contents of a ParseResult object.
 * 
 *   Pre:  Log is open on an output file.
 *         pPR points to a proper ParseResult object.
 */
void printResult(FILE* Log, const ParseResult* const pPR) {
   
      fprintf(Log, "%s\n", pPR->ASMInstruction);
      fprintf(Log, "   %s   %s\n", pPR->Opcode, pPR->Mnemonic);
      fprintf(Log, "   %2"PRIu8"   %s", pPR->rd, pPR->rdName);
      if ( pPR->RD != NULL ) {
			fprintf(Log, "   %s", pPR->RD);
		}
		fprintf(Log, "\n");
      fprintf(Log, "   %2"PRIu8"   %s", pPR->rs, pPR->rsName);
      if ( pPR->RS != NULL ) {
			fprintf(Log, "   %s", pPR->RS);
		}
		fprintf(Log, "\n");
      fprintf(Log, "   %2"PRIu8"   %s", pPR->rt, pPR->rtName);
      if ( pPR->RT != NULL ) {
			fprintf(Log, "   %s", pPR->RT);
		}
		fprintf(Log, "\n");
      fprintf(Log, "   %s\n", pPR->Funct);
      fprintf(Log, "   %"PRId16"\n", pPR->Imm);
      if ( pPR->IMM != NULL ) {
			fprintf(Log, "   %s", pPR->IMM);
		}
		fprintf(Log, "\n");
		fprintf(Log, "\n");
}
/**
 * This method prints the ParseResult as zeroes and ones.
 * 
 *  Pre:  Log is open on an output file.
 *  pPR points to a proper ParseResult object.
 */
void printRaw(FILE* Log, const ParseResult* const result) {
	if(strcmp(result->Mnemonic, "add") == 0 ||
	strcmp(result->Mnemonic, "sub") == 0 ||
	strcmp(result->Mnemonic, "mul") == 0 || 
	strcmp(result->Mnemonic, "and") == 0 ||
	strcmp(result->Mnemonic, "nor") == 0 ||
	strcmp(result->Mnemonic, "mult") == 0 ||
	strcmp(result->Mnemonic, "addu") == 0 ||
	strcmp(result->Mnemonic, "slt") == 0) {
		fprintf(Log, result->Opcode); //opcode
		fprintf(Log, result->RS); //rs
		fprintf(Log, result->RT); //rt
		fprintf(Log, result->RD); //rd
		fprintf(Log, "00000"); //0
		fprintf(Log, result->Funct); //funct
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "addi") == 0 ||
	strcmp(result->Mnemonic, "andi") == 0 ||
	strcmp(result->Mnemonic, "slti") == 0 ||
	strcmp(result->Mnemonic, "lw") == 0 ||
	strcmp(result->Mnemonic, "beq") == 0 ||
	strcmp(result->Mnemonic, "bne") == 0 ||
	strcmp(result->Mnemonic, "la") == 0 ||
	strcmp(result->Mnemonic, "li") == 0 ||
	strcmp(result->Mnemonic, "sw") == 0 ||
	strcmp(result->Mnemonic, "blez") == 0 ||
	strcmp(result->Mnemonic, "bgtz") == 0 ||
	strcmp(result->Mnemonic, "addiu") == 0 || 
	strcmp(result->Mnemonic, "lui") == 0) {
		fprintf(Log, result->Opcode); //opcode
		fprintf(Log, result->RS); //rs
		fprintf(Log, result->RT); //rt
		fprintf(Log, result->IMM); //imm
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "sra") == 0 ||
		strcmp(result->Mnemonic, "sll") == 0) {
		fprintf(Log, result->Opcode); //opcode
		fprintf(Log, "00000"); //0
		fprintf(Log, result->RT); //rt
		fprintf(Log, result->RD); //rd
		fprintf(Log, result->RS); // sa
		fprintf(Log, result->Funct); //funct
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "syscall") == 0) {
		fprintf(Log, result->Opcode);
		fprintf(Log, "00000000000000000000");
		fprintf(Log, result->Funct);
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "j") == 0) {
		fprintf(Log, result->Opcode);
		fprintf(Log, "0000000000");
		fprintf(Log, result->IMM); //imm
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "srav") == 0) {
		fprintf(Log, result->Opcode); //opcode
		fprintf(Log, result->RT); //rt
		fprintf(Log, result->RS); //rs
		fprintf(Log, result->RD); //rd
		fprintf(Log, "00000"); //0
		fprintf(Log, result->Funct); //funct
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "nop") == 0) {
		fprintf(Log, "00000000000000000000000000000000");
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "move") == 0) {
		fprintf(Log, result->Opcode); //opcode
		fprintf(Log, result->RS);
		fprintf(Log, result->RD);
		fprintf(Log, result->RT);
		fprintf(Log, "00000"); //0
		fprintf(Log, result->Funct); //funct
		fprintf(Log, "\n");
	}
	else if (strcmp(result->Mnemonic, "blt") == 0) {
		//print slt
		fprintf(Log, "000000");
		fprintf(Log, result->RS);
		fprintf(Log, result->RT);
		fprintf(Log, "00001"); //$at
		fprintf(Log, "00000");
		fprintf(Log, "101010"); //slt funct
		fprintf(Log, "\n");
		//print bne
		fprintf(Log, "000101"); //BNE opcode.
		fprintf(Log, "00001"); //$at
		fprintf(Log, "00000");
		fprintf(Log, result->IMM); //imm
		fprintf(Log, "\n");
	}
}
