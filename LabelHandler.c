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
#include "LabelHandler.h"
#include "ASMParser.h" 

/**
 *  This method stores an address and a name.
 */ 
void storeLabel(LabelHandler* const pLH, char* name, int16_t address) {
	switch(pLH->Size) {
		case 0: 
			pLH->Name1 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name1, name); 
			pLH->Address1 = address;
			(pLH->Size)++;
			break;
		case 1: 
			pLH->Name2 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name2, name); 
			pLH->Address2 = address;
			(pLH->Size)++;
			break;
		case 2: 
			pLH->Name3 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name3, name); 
			pLH->Address3 = address;
			(pLH->Size)++;
			break;
		case 3: 
			pLH->Name4 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name4, name); 
			pLH->Address4 = address;
			(pLH->Size)++;
			break;
		case 4: 
			pLH->Name5 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name5, name); 
			pLH->Address5 = address;
			(pLH->Size)++;
			break;
		case 5: 
			pLH->Name6 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name6, name); 
			pLH->Address6 = address;
			(pLH->Size)++;
			break;
		case 6: 
			pLH->Name7 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name7, name); 
			pLH->Address7 = address;
			(pLH->Size)++;
			break;
		case 7: 
			pLH->Name8 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name8, name); 
			pLH->Address8 = address;
			(pLH->Size)++;
			break;
		case 8: 
			pLH->Name9 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name9, name); 
			pLH->Address9 = address;
			(pLH->Size)++;
			break;
		case 9: 
			pLH->Name10 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name10, name); 
			pLH->Address10 = address;
			(pLH->Size)++;
			break;	
		case 10: 
			pLH->Name11 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name11, name); 
			pLH->Address11 = address;
			(pLH->Size)++;
			break;	
		case 11: 
			pLH->Name12 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name12, name); 
			pLH->Address12 = address;
			(pLH->Size)++;
			break;	
		case 12: 
			pLH->Name13 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name13, name); 
			pLH->Address13 = address;
			(pLH->Size)++;
			break;	
		case 13: 
			pLH->Name14 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name14, name); 
			pLH->Address14 = address;
			(pLH->Size)++;
			break;	
		case 14: 
			pLH->Name15 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name15, name); 
			pLH->Address15 = address;
			(pLH->Size)++;
			break;	
		case 15: 
			pLH->Name16 = (char*) calloc(20, sizeof(char));
			strcpy(pLH->Name16, name); 
			pLH->Address16 = address;
			(pLH->Size)++;
			break;
		default: 
			printf("lable handler is full\n");
	}	
}

/**
 * This method takes a name and returns an address from the table.
 */
int16_t getLabelAddress(LabelHandler* const pLH, char* name){
		if (strcmp(pLH->Name1, name) == 0) {
			return pLH->Address1;
		}
		else if (strcmp(pLH->Name2, name) == 0) {
			return pLH->Address2;
		}
		else if (strcmp(pLH->Name3, name) == 0) {
			return pLH->Address3;
		}
		else if (strcmp(pLH->Name4, name) == 0) {
			return pLH->Address4;
		}
		else if (strcmp(pLH->Name5, name) == 0) {
			return pLH->Address5;
		}
		else if (strcmp(pLH->Name6, name) == 0) {
			return pLH->Address6;
		}
		else if (strcmp(pLH->Name7, name) == 0) {
			return pLH->Address7;
		}
		else if (strcmp(pLH->Name8, name) == 0) {
			return pLH->Address8;
		}
		else if (strcmp(pLH->Name9, name) == 0) {
			return pLH->Address9;
		}
		else if (strcmp(pLH->Name10, name) == 0) {
			return pLH->Address10;
		}
		else if (strcmp(pLH->Name11, name) == 0) {
			return pLH->Address11;
		}
		else if (strcmp(pLH->Name12, name) == 0) {
			return pLH->Address12;
		}
		else if (strcmp(pLH->Name13, name) == 0) {
			return pLH->Address13;
		}
		else if (strcmp(pLH->Name14, name) == 0) {
			return pLH->Address14;
		}
		else if (strcmp(pLH->Name15, name) == 0) {
			return pLH->Address15;
		}
		else if (strcmp(pLH->Name16, name) == 0) {
			return pLH->Address16;
		}
		else {
			return 0;
		}
}
/**
 *  This method prints the label symbols to the output file. 
 *  Activated with the -symbols flag.
 */
void printAddresses(LabelHandler* const pLH, FILE* Log){
		if (pLH->Name1 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address1);
			fprintf(Log, pLH->Name1);
			fprintf(Log, "\n");
		}
		if (pLH->Name2 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address2);
			fprintf(Log, pLH->Name2);
			fprintf(Log, "\n");
		}
		if (pLH->Name3 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address3);
			fprintf(Log, pLH->Name3);
			fprintf(Log, "\n");
		}
		if (pLH->Name4 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address4);
			fprintf(Log, pLH->Name4);
			fprintf(Log, "\n");
		}
		if (pLH->Name5 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address5);
			fprintf(Log, pLH->Name5);
			fprintf(Log, "\n");
		}
		if (pLH->Name6 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address6);
			fprintf(Log, pLH->Name6);
			fprintf(Log, "\n");
		}
		if (pLH->Name7 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address7);
			fprintf(Log, pLH->Name7);
			fprintf(Log, "\n");
		}
		if (pLH->Name8 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address8);
			fprintf(Log, pLH->Name8);
			fprintf(Log, "\n");
		}
		if (pLH->Name9 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address9);
			fprintf(Log, pLH->Name9);
			fprintf(Log, "\n");
		}
		if (pLH->Name10 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address10);
			fprintf(Log, pLH->Name10);
			fprintf(Log, "\n");
		}
		if (pLH->Name11 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address11);
			fprintf(Log, pLH->Name11);
			fprintf(Log, "\n");
		}
		if (pLH->Name12 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address12);
			fprintf(Log, pLH->Name12);
			fprintf(Log, "\n");
		}
		if (pLH->Name13 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address13);
			fprintf(Log, pLH->Name13);
			fprintf(Log, "\n");
		}
		if (pLH->Name14 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address14);
			fprintf(Log, pLH->Name14);
			fprintf(Log, "\n");
		}
		if (pLH->Name15 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address15);
			fprintf(Log, pLH->Name15);
			fprintf(Log, "\n");
		}
		if (pLH->Name16 != NULL) {
			fprintf(Log, "0x%08X   ", (int) pLH->Address16);
			fprintf(Log, pLH->Name16);
			fprintf(Log, "\n");
		}
}

/**
 * This function frees everything.
 */ 
void clearHandler(LabelHandler* const pLH) {
	free(pLH->Name1);
	pLH->Name1 = NULL;
	free(pLH->Name2);
	pLH->Name2 = NULL;
	free(pLH->Name3);
	pLH->Name3 = NULL;
	free(pLH->Name4);
	pLH->Name4 = NULL;
	free(pLH->Name5);
	pLH->Name5 = NULL;
	free(pLH->Name6);
	pLH->Name6 = NULL;
	free(pLH->Name7);
	pLH->Name7 = NULL;
	free(pLH->Name8);
	pLH->Name8 = NULL;
	free(pLH->Name9);
	pLH->Name9 = NULL;
	free(pLH->Name10);
	pLH->Name10 = NULL;
	free(pLH->Name11);
	pLH->Name11 = NULL;
	free(pLH->Name12);
	pLH->Name12 = NULL;
	free(pLH->Name13);
	pLH->Name13 = NULL;
	free(pLH->Name14);
	pLH->Name14 = NULL;
	free(pLH->Name15);
	pLH->Name15 = NULL;
	free(pLH->Name16);
	pLH->Name16 = NULL;
	pLH->Address1 = 0;
	pLH->Address2 = 0;
	pLH->Address3 = 0;
	pLH->Address4 = 0;
	pLH->Address5 = 0;
	pLH->Address6 = 0;
	pLH->Address7 = 0;
	pLH->Address8 = 0;
	pLH->Address9 = 0;
	pLH->Address10 = 0;
	pLH->Address11 = 0;
	pLH->Address12 = 0;
	pLH->Address13 = 0;
	pLH->Address14 = 0;
	pLH->Address15 = 0;
	pLH->Address16 = 0;
}
