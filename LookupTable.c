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
#include "LookupTable.h"

#define NUMRECORDS 66

static TableEntry LTable[NUMRECORDS] = {
	{"000000", "add", OPCODE, 0},
	{"000000", "sub", OPCODE, 0},
	{"001000", "addi", OPCODE, 0},
	{"001111", "lui", OPCODE, 0},
	{"100011", "lw", OPCODE, 0},
	{"011100", "mul", OPCODE, 0},
	{"000100", "beq", OPCODE, 0},
	{"101011", "sw", OPCODE, 0},
	{"000000", "and", OPCODE, 0},
	{"001100", "andi", OPCODE, 0},
	{"000000", "nor", OPCODE, 0},
	{"001010", "slti", OPCODE, 0},
	{"000000", "mult", OPCODE, 0},
	{"000101", "bne", OPCODE, 0},
	{"001000", "la", OPCODE, 0},
	{"001001", "li", OPCODE, 0},
	{"000000", "addu", OPCODE, 0},
	{"000000", "slt", OPCODE, 0},
	{"000000", "sra", OPCODE, 0},
	{"000000", "sll", OPCODE, 0},
	{"000110", "blez", OPCODE, 0},
	{"000111", "bgtz", OPCODE, 0},
	{"001001", "addiu", OPCODE, 0},
	{"000000", "srav", OPCODE, 0},
	{"000000", "move", OPCODE, 0},
	{"100001", "move", FUNCT, 0},
	{"000111", "srav", FUNCT, 0},
	{"000000", "sll", FUNCT, 0},
	{"000011", "sra", FUNCT, 0},
	{"101010", "slt", FUNCT, 0},
	{"100001", "addu", FUNCT, 0},
	{"100100", "and", FUNCT, 0},
	{"100111", "nor", FUNCT, 0},
	{"100000", "add", FUNCT, 0},
	{"100101", "or", FUNCT, 0},
	{"100010", "sub", FUNCT, 0},
	{"000010", "mul", FUNCT, 0},
	{"011000", "mult", FUNCT, 0},
	{"00000", "$zero", REGISTER, 0},
	{"00001", "$at", REGISTER, 1},
	{"00010", "$v0", REGISTER, 2},
	{"00011", "$v1", REGISTER, 3},
	{"00100", "$a0", REGISTER, 4},
	{"00101", "$a1", REGISTER, 5},
	{"00110", "$a2", REGISTER, 6},
	{"00111", "$a3", REGISTER, 7},
	{"01000", "$t0", REGISTER, 8},
	{"01001", "$t1", REGISTER, 9},
	{"01010", "$t2", REGISTER, 10},
	{"01011", "$t3", REGISTER, 11},
	{"01100", "$t4", REGISTER, 12},
	{"01101", "$t5", REGISTER, 13},
	{"01110", "$t6", REGISTER, 14},
	{"01111", "$t7", REGISTER, 15},
	{"10000", "$s0", REGISTER, 16},
	{"10001", "$s1", REGISTER, 17},
	{"10010", "$s2", REGISTER, 18},
	{"10011", "$s3", REGISTER, 19},
	{"10100", "$s4", REGISTER, 20},
	{"10101", "$s5", REGISTER, 21},
	{"10110", "$s6", REGISTER, 22},
	{"10111", "$s7", REGISTER, 23},
	{"11000", "$t8", REGISTER, 24},
	{"11001", "$t9", REGISTER, 25},
	{"11010", "$k0", REGISTER, 26},
	{"11011", "$k1", REGISTER, 27}
	
	
};
/**
 * This method takes a name an a lookup type and returns a table entry struct.
 */
const TableEntry* Find(char* Name, LookupType Type){
	
	for (int i = 0; i < NUMRECORDS; i++) {
		if (strcmp(Name, LTable[i].Name) == 0 && Type == LTable[i].LType) {
			return &LTable[i];
		}
	}
	return NULL;
}
