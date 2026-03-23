#include "arena.h"
#include <iostream>
#include <atomic>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <sys/mman.h>

// constructor ,,, asking os for 1gb raw mem
arena::arena(){
  //mmap - anon chunk of VM ,, nullptr -- let os choose the addr
  start = (char*) mmap(nullptr, total_size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  total_size = 1*1024*1024*1024;
  offset = 0; //bump pointer, starts at 0 
};

void* arena::allocate(size_t size){
  size_t aligned = ((size + 63) / 64) * 64; // round to 64bytes
  // save current posn before moving 
  size_t old_offset = offset.load();
  size_t curr_offset = old_offset + aligned; // move fwd by aligned size
  offset.store(curr_offset); // store new posn 
//return ptr to start of alloc region
  return(start + old_offset);

};
//destructor 
arena::~arena(){
  munmap(start,total_size); // releasing 1gb 
};
