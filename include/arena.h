#ifndef ARENA_H
#define ARENA_H

#include <cstddef>

class arena {
private:
    char* start; // start of 1gb block
    size_t offset; //bump ptr to current position 
    size_t total_size; // total 1gb always
public:
    arena();
    __attribute__((always_inline)) inline void* allocate(size_t size) { //--no func call overhead at all,,code gets pasted directly in the call site ,,
    if (offset + size > total_size) {
            return nullptr; 
         }
    size_t aligned = ((size + 63) / 64) * 64; // roundoff to 64 byte ,,, 
        void* ptr = start + offset; // aligned with cache line
        offset += aligned; //e evry allocation starts at cache line boundary ,, 
        return ptr;
    }
    ~arena();
};

#endif
