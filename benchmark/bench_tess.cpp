#include <iostream>
#include <chrono>
#include "../include/tesseract.h"
#include <random>

const int ITERATIONS = 1000000;

volatile void* sink;

std::mt19937 rng(42);  // fixed seed for reproducibility
std::uniform_int_distribution<size_t> size_dist(16, 4096);

int main() {
      auto start = std::chrono::steady_clock::now();

  for (int i = 0; i < ITERATIONS; i++) {
        size_t alloc_size = size_dist(rng);  // 16 to 4096, random
         sink = allocate(alloc_size);
             tess_free((void*)sink, alloc_size);
             }
    auto end = std::chrono::steady_clock::now();

      double t = std::chrono::duration<double, std::milli>(end - start).count();
      std::cout << t << "\n";
}
