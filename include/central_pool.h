//actually holds allthe free blocks 
#ifndef CENTRAL_POOL_H
#define CENTRAL_POOL_H
#include "size_class.h"
#include "free_list.h"
#include <mutex>

class central_pool{
private:
  freelist lists[num_classes];
  std::mutex locks[num_classes];
public:
  central_pool();
  void* allocate(int class_idx);
  void free(int class_idx,void* ptr);
};

#endif
