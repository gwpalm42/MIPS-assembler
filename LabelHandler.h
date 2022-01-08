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
#ifndef LABELHANDLER_H
#define LABELHANDLER_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

struct _LabelHandler {
	uint8_t Size;
	
	char* Name1;
	int16_t Address1;
	
	char* Name2;
	int16_t Address2;
	
	char* Name3;
	int16_t Address3;
	
	char* Name4;
	int16_t Address4;
	
	char* Name5;
	int16_t Address5;
	
	char* Name6;
	int16_t Address6;
	
	char* Name7;
	int16_t Address7;
	
	char* Name8;
	int16_t Address8;
	
	char* Name9;
	int16_t Address9;
	
	char* Name10;
	int16_t Address10;
	
	char* Name11;
	int16_t Address11;
	
	char* Name12;
	int16_t Address12;
	
	char* Name13;
	int16_t Address13;
	
	char* Name14;
	int16_t Address14;
	
	char* Name15;
	int16_t Address15;
	
	char* Name16;
	int16_t Address16;
	
};
typedef struct _LabelHandler LabelHandler;

void storeLabel(LabelHandler* const pLH, char* name, int16_t address);
int16_t getLabelAddress(LabelHandler* const pLH, char* name);
void printAddresses(LabelHandler* const pLH, FILE* Log);
void clearHandler(LabelHandler* const pLH);

#endif
