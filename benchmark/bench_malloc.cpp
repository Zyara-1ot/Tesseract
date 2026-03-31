#include <iostream>
#include <chrono>
#include <cstdlib>

const int ITERATIONS = 1000000;
volatile void* sink;

std::mt19937 rnd(11); 
std::uniform_int_distribution<size_t> size_dist(16, 4096);
int main() {
    auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < ITERATIONS; i++) {
            size_t alloc_size = size_dist(rnd);
             sink = malloc(alloc_size);
                     free((void*)sink);
                         }
    auto end = std::chrono::steady_clock::now();
    double t = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << t << "\n";
}
