#ifndef FREE_LIST_H
#define FREE_LIST_H
#include <cstddef>

class freelist {
public:
    struct freeblock {
        freeblock* next;
    };
    freeblock* head;
    freelist();
    __attribute__((always_inline)) inline void push(void* ptr) {
        freeblock* newblock = (freeblock*)ptr;
        newblock->next = head;
        head = newblock;
    }
    __attribute__((always_inline)) inline void* pop() {
        if (__builtin_expect(!head, 0)) { // expect the !head to be false,,,hint to cpu  --- 99% time crct guess ,,, fast overall 
            return nullptr;
        }
        freeblock* curr = head;
        head = head->next;
        return (void*)curr;
    }
    __attribute__((always_inline)) inline bool is_empty() const {
        return head == nullptr;
    }
};

#endif
