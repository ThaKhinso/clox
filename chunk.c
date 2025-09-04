#include "chunk.h"
#include "memory.h"

#include <stdlib.h>

void initChunk(Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->repeatedLines.capacity = 0;
	chunk->repeatedLines.capacity_of_lines = 0;
	chunk->repeatedLines.size = 0;
	chunk->repeatedLines.size_of_lines = 0;
	chunk->repeatedLines.lines = NULL;
	chunk->repeatedLines.run_count = NULL;
	initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
	int repeatingLineIndex = 0;
	if (chunk->capacity < chunk->count + 1)
	{
		int oldCapcity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapcity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapcity, chunk->capacity);
	}

	if (chunk->repeatedLines.capacity_of_lines < chunk->repeatedLines.size_of_lines + 1) {
		int oldCapcity = chunk->repeatedLines.capacity_of_lines;
		chunk->repeatedLines.capacity_of_lines = GROW_CAPACITY(oldCapcity);
		chunk->repeatedLines.lines = GROW_ARRAY(int, chunk->repeatedLines.lines, oldCapcity, 
			chunk->repeatedLines.capacity_of_lines);
		INIT_ARRAY(int, chunk->repeatedLines.lines,
			chunk->repeatedLines.capacity_of_lines, 0);
	}

	if (chunk->repeatedLines.capacity < chunk->repeatedLines.size + 1)
	{
		int oldCapacity = chunk->repeatedLines.capacity;
		chunk->repeatedLines.capacity = GROW_CAPACITY(oldCapacity);
		chunk->repeatedLines.run_count = GROW_ARRAY(int, chunk->repeatedLines.run_count,
			oldCapacity, chunk->repeatedLines.capacity);
		INIT_ARRAY(int, chunk->repeatedLines.run_count, chunk->repeatedLines.capacity, 1);
	}

	chunk->code[chunk->count] = byte;
	if (chunk->count > 0 && line == chunk->repeatedLines.lines[chunk->repeatedLines.size_of_lines-1])
	{
		chunk->repeatedLines.run_count[chunk->repeatedLines.size - 1] += 1;
	}
	else {
		chunk->repeatedLines.size++;
		chunk->repeatedLines.lines[chunk->repeatedLines.size_of_lines] = line;
		chunk->repeatedLines.size_of_lines++;
	}
	chunk->count++;
}

void freeChunk(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	//FREE_ARRAY(int, chunk->lines, chunk->capacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int instructionOffset)
{
	int result = 0;
	int sum = 0;
	for (int i = 0; i < chunk->repeatedLines.size; i++)
	{
		sum += chunk->repeatedLines.run_count[i];
		if (instructionOffset < sum)
		{
			result = chunk->repeatedLines.lines[i];
			break;
		}
	}
	return result;
}
