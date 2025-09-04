#pragma once
#include "common.h"

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
		(type*)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
		reallocate(pointer, sizeof(type) * (oldCount), 0)

#define INIT_ARRAY(type, pointer, count, init_number) \
		for(int i = 0; i < count; i++) { \
			pointer[i] = (type)init_number;		 \
		}

void* reallocate(void* pointer, size_t oldSize, size_t newSize);