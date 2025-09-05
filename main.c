#include "common.h"
#include <stdio.h>
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char* argv[]) {

	initVM();
	Chunk chunk;
	initChunk(&chunk);


	int constant = addConstant(&chunk, 2.1);
	//int sec = addConstant(&chunk, 3.3);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constant, 123);
	//writeChunk(&chunk, sec);
	writeChunk(&chunk, OP_RETURN, 124);

	writeChunk(&chunk, OP_RETURN, 125);
	writeChunk(&chunk, OP_RETURN, 125);
	writeChunk(&chunk, OP_RETURN, 125);

	writeChunk(&chunk, OP_RETURN, 126);
	writeChunk(&chunk, OP_RETURN, 126);
	writeChunk(&chunk, OP_RETURN, 126);
	writeChunk(&chunk, OP_RETURN, 126);
	writeChunk(&chunk, OP_RETURN, 126);
	writeChunk(&chunk, OP_RETURN, 126);
	printf("line number: %d\n", getLine(&chunk, (uint8_t)2));
	printf("line_count: %d, %d\n", chunk.count, chunk.repeatedLines.lines[0]);
	for (int i = 0; i < chunk.repeatedLines.size_of_lines; i++)
	{
		printf("different_line number = %i\n", chunk.repeatedLines.lines[i]);
		/*for (int j = 0; j < chunk.repeatedLines.size; j++)
		{
			printf(" Times = %d\n", chunk.repeatedLines.run_count[j]);
		}*/
	}
	for (int i = 0; i < chunk.repeatedLines.size; i++)
	{
		printf("repeatedcount = %i\n", chunk.repeatedLines.run_count[i]);
	}
	//printf("first chunk: %d, second chunk: %d\n", chunk.code[0], chunk.code[1]);
	//printf("repeated line: %d\n", chunk.repeatedLines.run_count[0]);
	disassembleChunk(&chunk, "test chunk");
	interpret(&chunk);
	freeVM();
	freeChunk(&chunk);
	int out = getc(stdin);
	return 0;
}	