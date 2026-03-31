#include <iostream>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <vector>

struct HttpRequest {
    char* headers;
    char* body;
    char* response;
    HttpRequest(size_t header_size, size_t body_size, size_t resp_size) {
        headers = (char*)malloc(header_size);
        body = (char*)malloc(body_size);
        response = (char*)malloc(resp_size);
    }
    ~HttpRequest() {
        free(headers);
        free(body);
        free(response);
    }
};
void worker(int thread_id, int num_requests) {
  volatile long sum = 0;
      for (int i = 0; i < num_requests; i++) {
                   HttpRequest req(1024, 4096, 8192);
                   req.headers[0] = 'G';
                   req.body[0] = 'p';
                   req.response[0] = 'H';
                   sum += (long)req.headers;
               }
}
int main() {
      const int NUM_THREADS = 8;
      const int REQUESTS_PER_THREAD = 1000000;
      std::vector<std::thread> threads;
      auto start = std::chrono::steady_clock::now();
      for (int t = 0; t < NUM_THREADS; t++) {
                   threads.emplace_back(worker, t, REQUESTS_PER_THREAD);
    }
    for (auto& th : threads) {
                 th.join();
    }
    auto end = std::chrono::steady_clock::now();
      double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
      int total_requests = NUM_THREADS * REQUESTS_PER_THREAD;
      std::cout << "malloc web server (" << total_requests << " requests, " << NUM_THREADS << " threads): " 
              << elapsed << " ms\n";
    std::cout << "Throughput: " << (total_requests / (elapsed / 1000)) << " requests/sec\n";
    return 0;
}
