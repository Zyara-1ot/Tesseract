#include "free_list.h"
#include <iostream>
#include <cstddef>

freelist::freelist(){
  head = nullptr; // else , head will start with garbage value 
};

void freelist::push(void* ptr){   // when someone calls push() it will, say hey, freelist, i just freed this block of memory , and heres the address,, 
  freeblock* newblock = (freeblock*)ptr; //newblock pointing freeblock at address ptr
  newblock -> next = head; // then its next field pointing to whtevr head currently points to... 
  head = newblock; //head points to a address , the new block is now first in the address .

};

void* freelist::pop(){
  freeblock* curr = head;  // need a temporary var to hold before we move head to next
  head = head -> next;  // head move to next block 
  return curr;// return curr,, the first one which we popped out,, 
  
}; 

bool freelist::is_empty(){
  return head == nullptr;
};
