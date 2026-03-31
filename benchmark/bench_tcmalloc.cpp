#include <iostream>
#include <chrono>
#include <random>
#include <gperftools/tcmalloc.h>
 
const int ITERATIONS = 1000000;
volatile void* sink;
 
int main() {
  std::mt19937 rnd(11);
      std::uniform_int_distribution<size_t> size_dist(16, 4096);
      auto start = std::chrono::steady_clock::now();
      for (int i = 0; i < ITERATIONS; i++) {
                   size_t alloc_size = size_dist(rnd);
                   sink = tc_malloc(alloc_size);
        tc_free((void*)sink);
    }
    auto end = std::chrono::steady_clock::now();
      double t = std::chrono::duration<double, std::milli>(end - start).count();
      std::cout << "tcmalloc (variable): " << t << " ms\n";
}
