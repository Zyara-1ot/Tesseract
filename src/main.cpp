#include <iostream>
#include "arena.h"
#include "free_list.h"
#include "size_class.h"
#include "central_pool.h"
#include "tesseract.h"

int main(){
      std::cout << "size class for 100: " << get_size_class(100) << std::endl;
    std::cout << "size class for 8: " << get_size_class(8) << std::endl;
    void* t1 = allocate(100);
      std::cout << "allocated: " << t1 << std::endl;
    tess_free(t1, 100);
    void* t2 = allocate(100);
      std::cout << "allocated after free: " << t2 << std::endl;
    std::cout << "reuse? " << (t1 == t2 ? "YES!" : "NO") << std::endl;
    return 0;
}
