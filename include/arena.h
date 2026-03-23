#ifndef ARENA_H
#define ARENA_H

#include <cstdint>
#include <cstddef>
#include <atomic>

class arena{
private :
  char* start;
  size_t total_size;
  std::atomic<size_t>offset;

public:
  arena();
  void* allocate(size_t size);
  ~arena();
  
};

#endif

