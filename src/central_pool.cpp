#include "central_pool.h"
#include <iostream>
#include <cstddef>
#include <mutex>

central_pool::central_pool(){
};

void* central_pool::allocate(int class_idx){
    std::lock_guard<std::mutex> lock(locks[class_idx]);  // lock th mtx for tis size class
    void* ptr = lists[class_idx].pop(); // then pop
    return ptr; // and rturn ptr
};

void central_pool::free(int class_idx, void* ptr){
    std::lock_guard<std::mutex> lock(locks[class_idx]); // lock ,, pus free block back,,auto unlock 
    lists[class_idx].push(ptr);
};
