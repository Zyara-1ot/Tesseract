#include "tesseract.h"
#include <iostream>

arena global_arena;
central_pool global_pool;
thread_local freelist cache[num_classes];

const int BATCH_SIZE = 1;// batching,, fast ,,

static inline void refill_cache(int class_idx, size_t size) {
      for (int i = 0; i < BATCH_SIZE; i++) {
                   void* ptr = global_arena.allocate(size);   // grab from centrall pool 
                   cache[class_idx].push(ptr); // store to thread local cache
    }
}


void* allocate(size_t size) {
  if (size > 10240) {
        return global_arena.allocate(size);
    }
      
  int class_idx = get_size_class(size);
      freelist& local_cache = cache[class_idx];
      if (local_cache.head) {
        void* ptr = local_cache.head;
        local_cache.head = local_cache.head->next;
        return ptr;
    }
      refill_cache(class_idx, size);
      if (local_cache.head) {
        void* ptr = local_cache.head;
        local_cache.head = local_cache.head->next;
        return ptr;
    }
      return global_arena.allocate(size);
}

void tess_free(void* ptr, size_t size) {
      int class_idx = get_size_class(size); // free always goes to thread local cache
      cache[class_idx].push(ptr);
}
