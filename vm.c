#include "vm.h"

VM vm;

void initVM()
{

}

void freeVM() {

}

InterpretResult interpret(Chunk* chunk)
{
	vm.chunk = chunk;
	vm.ip = vm.chunk->code;
	return run();
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
	for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
		disassemmbleInstruction(vm.chunk,
			(int)(vm.ip - vm.chunk->code));
#endif
		uint8_t instruction = 0;
		switch (instruction == READ_BYTE())
		{
		case OP_RETURN:
			return INTERPRET_OK;
		case OP_CONSTANT: {
			Value constant = READ_CONSTANT();
			printValue(constant);
			printf("\n");
			break;
		}
		default:
			break;
		}
	}
#undef READ_BYTE
#undef READ_CONSTANT
}
