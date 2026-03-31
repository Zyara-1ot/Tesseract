// arena.cpp
 #include "arena.h"
#include <iostream>
 #include <vector>
 #include <cstdint>
 #include <algorithm>
 #include <sys/mman.h>
 arena::arena(){
   total_size = 1*1024*1024*1024;
  start = (char*) mmap(nullptr, total_size, PROT_READ|PROT_WRITE, 
                                            MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
         if(start == MAP_FAILED){
               std::cout << "mmap failed!" << std::endl;
                 }
                   offset = 0;
                 };
                   arena::~arena(){
                     munmap(start, total_size);
                     };
