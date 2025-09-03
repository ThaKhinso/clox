#include "common.h"
#include <stdio.h>
#include "chunk.h"

int main(int argc, char* argv[]) {

	Chunk chunk;
	initChunk(&chunk);
	writeChunk(&chunk, OP_RETURN);
	freeChunk(&chunk);
	int out = getc(stdin);
	return 0;
}	