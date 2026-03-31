#include <iostream>
#include <chrono>
#include <cstdlib>

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

int main() {
      const int NUM_REQUESTS = 10000000;
      volatile long sum = 0;
      
      auto start = std::chrono::steady_clock::now();
      
      for (int i = 0; i < NUM_REQUESTS; i++) {
                   HttpRequest req(1024, 4096, 8192);
                   req.headers[0] = 'G';
        req.body[0] = 'p';
        req.response[0] = 'H';
        sum += (long)req.headers;
    }
    
    auto end = std::chrono::steady_clock::now();
      
      double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
      std::cout << "malloc web server (" << NUM_REQUESTS << " requests): " 
              << elapsed << " ms\n";
    std::cout << "Per-request: " << (elapsed / NUM_REQUESTS) * 1000 << " microseconds\n";
    std::cout << "Throughput: " << (NUM_REQUESTS / (elapsed / 1000)) << " requests/sec\n";
    std::cout << "sum: " << sum << "\n";
    
    return 0;
}
