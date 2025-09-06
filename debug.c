#include "debug.h"
#include "value.h"

#include <stdio.h>

void disassembleChunk(Chunk* chunk, const char* name) {
	printf("== %s ==\n", name);

	for (int offset = 0; offset < chunk->count; )
	{
		offset = disassembleInstruction(chunk, offset);
	}
}

int disassembleInstruction(Chunk* chunk, int offset) {
	printf("%04d ", offset);
	int now = getLine(chunk, offset);
	int earlier = getLine(chunk, offset-1);
	if (offset > 0 && now == earlier) {
		printf("	| ");
	} else {
		printf("%4d ", now);
	}
	uint8_t instruction = chunk->code[offset];
	switch (instruction)
	{
	case OP_RETURN:
		return simpleInstruction("OP_RETURN", offset);
	case OP_CONSTANT:
		return constantInstruction("OP_CONSTANT", chunk, offset);
	default:
		printf("Unknown opcode %d\n", instruction);
		return offset + 1; // Skip unknown instruction
		break;
	}
}

int simpleInstruction(const char* name, int offset) {
	printf("%s\n", name);
	return offset + 1;
}

int constantInstruction(const char* name, Chunk *chunk, int offset) {
	uint8_t constant = chunk->code[offset];
	printf("%-16s %4d '", name, constant);
	printValue(chunk->constants.values[constant]);
	printf("'\n");
	return offset + 2;
}
