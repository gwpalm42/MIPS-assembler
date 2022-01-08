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
#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

enum _LookupType {OPCODE, FUNCT, REGISTER};
typedef enum _LookupType LookupType;

struct _TableEntry {
	char* Code;
	char* Name;
	LookupType LType; 
	uint8_t RegisterNumber;
};
typedef struct _TableEntry TableEntry;

const TableEntry* Find(char* Name, LookupType Type);

#endif
