#ifndef FREE_LIST_H
#define FREE_LIST_H

#include <cstddef>

struct freeblock{
  freeblock* next;  //ptr to next block ,,, if user even overwrites it ,, issok, we just need it once,,
};

class freelist{
private:
freeblock* head;    //pts to 1st free block,, 

public:
  freelist();
  void push(void* ptr );    //freed block to front, 
  void* pop();          //take block from front, return it,,,
  bool is_empty();     //we just need true of false 
};


#endif
