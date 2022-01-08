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
//
// 	  This driver is a modified version of c02driver.c from the previous assignment.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <inttypes.h>

#include "ParseResult.h"       
#include "ASMParser.h"        
#include "LookupTable.h"
#include "LabelHandler.h" 		

int isEmpty(char string[100]);
int hasColon(char string[100]);
int isComment(char string[100]);

/*
 * arg 1 is the input file and arg 2 is the output file. 
 * master method that parses the file and then gives the 
 * information to the corresponding files.
 */
int main(int argc, char** argv) {
    
    // Open specified input file and verify it's available:
    FILE* src = fopen(argv[1], "r");
    if (src == NULL) {
		printf("Unable to find file %s... exiting.\n", argv[1]);
		return 2;
	}
   
	//output file
	FILE* results  = fopen(argv[2], "w");
   
	char asmInstruction[100];   // holder for current asm instruction
	LabelHandler* labels = (LabelHandler*)calloc(1, sizeof(LabelHandler));
	int16_t dataAddressCounter = 8192;
	int16_t textAddressCounter = 0;
	FILE* data = tmpfile();
	//first pass will fetch instructions
	while (fgets(asmInstruction, 100, src) != NULL) {
		if (isEmpty(asmInstruction) == 0)  {
			
			//printf(asmInstruction);
			//printf("\n");
			
			// erase trailing newline from string
			asmInstruction[strlen(asmInstruction) - 1] = '\0';
		    char* token = strtok(asmInstruction, " ");
		    if (asmInstruction[0] == ' ' && isComment(asmInstruction) == 0) {
				textAddressCounter += 4;
			}
			else if (token[0] != '.' && token[0] != '#'){
				//remove colon and store label
				token[strlen(token) - 1] = '\0';
				char* label = token;

				//figure out which type of variable this is and then
				//write the proper data into dataSection and increment addressCounter
				token = strtok(NULL, " ");
				if (token == NULL) {
					//in .text label case.
					storeLabel(labels, label, textAddressCounter);
				}
				else if (strcmp(token, ".word") == 0) {
					if (dataAddressCounter % 4 != 0) {
						for (int i = 4 - (dataAddressCounter % 4); i > 0; i--) {
							fprintf(data, "00000000"); // null terminator
							dataAddressCounter++;
						}
						if (dataAddressCounter % 4 == 0) {
							fprintf(data, "\n");
						}
					}
					storeLabel(labels, label, (dataAddressCounter));
					//3 cases for .word: 2:2 / 2 / 2, 2, 2,...
					token = strtok(NULL, " ");
					if (token[strlen(token) - 1] != ',') {
						if (hasColon(token) == 0) {
							//no special char case
							DecimalToBinary32(atoi(token), token);
							fprintf(data, token); 
							fprintf(data, "\n"); 
							dataAddressCounter += 4;
						}
						else {
							//colon case = x:y create y 32 bit integers set to x
							char* set = (char*) calloc(32, sizeof(char));
							strcpy(set, strtok(token, ":"));
							char* amt = (char*) calloc(32, sizeof(char));
							strcpy(amt, strtok(NULL, " "));
							DecimalToBinary32(atoi(set), set);
							for (int i = 0; i < atoi(amt); i++) {
									fprintf(data, set); 
									fprintf(data, "\n"); 
									dataAddressCounter += 4;
							}
							free(set);
							free(amt);
						}	
					} 
					else { //handle list case
						 char* temp = (char*) calloc(40, sizeof(char));
						 while (token != NULL) {
							if (token[strlen(token) - 1] == ',') {
								token[strlen(token) - 1] = '\0'; 
							}
							DecimalToBinary32(atoi(token), temp);
							fprintf(data, temp); 
							fprintf(data, "\n"); 
							dataAddressCounter += 4;
							token = strtok(NULL, " ");
						 }
						 free(temp);
					}	
				}
				else if (strcmp(token, ".asciiz") == 0) {
					//ascii case
					storeLabel(labels, label, (dataAddressCounter));
					token = strtok(NULL, "\"");
					token = strtok(NULL, "\"");
					char* printMe = (char*) calloc(32, sizeof(char));
					for (int i = 1; i <= (int) strlen(token); i++) {
						DecimalToBinary8(token[i - 1], printMe);
						fprintf(data, printMe);
						dataAddressCounter++; 
						if (dataAddressCounter % 4 == 0) {
							fprintf(data, "\n");
						} 
					}
					fprintf(data, "00000000"); // null terminator
					dataAddressCounter++;
					if (dataAddressCounter % 4 == 0) {
							fprintf(data, "\n");
					}
					free(printMe);
				}
			}
		}
	}
	//fill out any remaining whitespace
	if (dataAddressCounter % 4 != 0) {
		for (int i = 4 - (dataAddressCounter % 4); i > 0; i--) {
			fprintf(data, "00000000"); // null terminator
				dataAddressCounter++;
		}
		if (dataAddressCounter % 4 == 0) {
			fprintf(data, "\n");
		}
	}
	
	//this if statements handles the -symbols case.
	if (argc == 4 && argv[3][0] == '-' && argv[3][1] == 's') {
		printAddresses(labels, results);
		clearHandler(labels);
		fclose(src);
		fclose(results);
		return 0;
	}
	
	rewind(src);
	textAddressCounter = 0;
	//this pass will fetch all instructions
	while (fgets(asmInstruction, 100, src) != NULL) {
		if (asmInstruction[0] == ' ' && isEmpty(asmInstruction) == 0 &&
			isComment(asmInstruction) == 0) {
			
			// erase trailing newline from string
			asmInstruction[strlen(asmInstruction) - 1] = '\0';	
			
			printf(asmInstruction);
			printf("\n");
		
			//check to make sure that the line is not a comment
		
			// Invoke ASM parser on current instruction:
			ParseResult* parsedInstruction = parseASM(
				asmInstruction, labels, textAddressCounter);
	
			// Check for NULL return:
			if (parsedInstruction == NULL) {
				fprintf(results, "Error:  parseASM() returned NULL \n");
				return 1;
			}
      
				// Write to output file
			printRaw(results, parsedInstruction);
			
				// Clean up dynamic allocations and increment coutner:
			textAddressCounter += 4;
			clearResult(parsedInstruction);
			free(parsedInstruction);

		}
	}

	// write temp file into real file
	rewind(data);
    char dataLine[100];
    fprintf(results, "\n");
    while (fgets(dataLine, 100, data) != NULL)  {
        fprintf(results, dataLine);
	}
    
    // exit behavior:
    clearHandler(labels);
    free(labels);
    fclose(data);
    fclose(src);
    fclose(results);
   
    return 0;
}
/**
 * This helper method takes a pointer to a string and returns
 * 1 if the string is empty and 0 if it is not.
 */
int isEmpty(char string[100]) {
	for (int i = 0; string[i] != '\n'; i++) {
		if (!isspace((unsigned char)string[i])) {
			return 0;
		}
	}
	return 1;
}
/**
 * This helper method takes a pointer to a string and returns
 * 1 if the string is empty and 0 if it is not.
 */
int isComment(char string[100]) {
	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == '#') {
			return 1;
		}
		else if (string[i] != ' ') {
			return 0;
		}
	}
	return 0;
}
/**
 *  helper method to determine if a string has a colon or not
 */
int hasColon(char string[100]) {
	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == ':') {
			return 1;
		}
	}
	return 0;
}
