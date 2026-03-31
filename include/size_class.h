#ifndef SIZE_CLASS_H
#define SIZE_CLASS_H

#include <cstddef>

#define CLASS_0_MAX 64 // no type safety but fast ,, than const ....
#define CLASS_1_MAX 256
#define CLASS_2_MAX 4096
#define CLASS_3_MAX 262144
#define CLASS_4_MAX 1048576
#define CLASS_5_MAX 16777216

const int num_classes = 6;

inline int get_size_class(size_t size){   //ummmmmmmmmmmmmmmmmmmmmm
  if(size <= CLASS_0_MAX) return 0;
  else if(size <= CLASS_1_MAX) return 1;
  else if(size <= CLASS_2_MAX) return 2;
  else if(size <= CLASS_3_MAX) return 3;
  else if(size <= CLASS_4_MAX) return 4;
  else if(size <= CLASS_5_MAX) return 5;
  else return -1;
}

#endif
