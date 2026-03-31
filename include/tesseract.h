#ifndef TESSERACT_H 
#define TESSERACT_H
#include "arena.h"
#include "free_list.h"
#include "size_class.h"
#include "central_pool.h"
#include <iostream>

extern arena global_arena;
extern central_pool global_pool;
extern thread_local freelist cache[num_classes];

void *allocate(size_t size);
void tess_free(void* ptr, size_t size);

#endif
