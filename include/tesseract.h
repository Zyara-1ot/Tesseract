#ifndef TESSERACT_H 
#define TESSERACT_H
#include "arena.h"
#include "free_list.h"
#include "size_class.h"
#include "central_pool.h"
#include <iostream>
#include <cstddef>
#include <atomic>

extern std::atomic<long> alloc_count;
extern std::atomic<long> free_count;
extern std::atomic<long> bytes_allocated;
extern arena global_arena;


void *allocate(size_t size);
void tess_free(void* ptr, size_t size);

#endif
