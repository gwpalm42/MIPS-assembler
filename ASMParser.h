#ifndef ASMPARSER_H
#define ASMPARSER_H
#include "ParseResult.h"
#include "LabelHandler.h"

/**  Breaks up given MIPS32 assembly instruction and creates a proper 
 *   ParseResult object storing information about that instruction.
 * 
 *   Pre:  pASM points to an array holding the representation of a
 *         syntactically valid assembly instruction, whose mnemonic is
 *         one of the following:
 *             add  addi  mul  beq  lui  lw  sw	 sub
 * 
 *   Returns:
 *         A pointer to a proper ParseResult object whose fields have been
 *         correctly initialized to correspond to the target of pASM.
 */
ParseResult* parseASM(const char* const pASM, LabelHandler* const pLH, int insAddress);
void DecimalToBinary16(int16_t Imm, char* IMM);
void DecimalToBinary32(int num, char* output);
void DecimalToBinary8(int num, char* output);
void DecimalToBinary5(int num, char* output);
#endif
