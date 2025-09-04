#pragma once

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_RETURN,
}OpCode;

typedef struct {
	int* lines;
	int* run_count;
	int size_of_lines;
	int capacity_of_lines;
	int size;
	int capacity;
}LineData;

typedef struct {
	int count;

	int capacity;
	uint8_t* code;
	LineData repeatedLines;
	ValueArray constants;
}Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

int getLine(Chunk* chunk, int instructionOffset);

