# TESSERACT

A cache aware, tensor optimized memory allocator in C++

Normal allocators don't know your cache exists. TESSERACT does.

---

## Why

Standard `malloc` and `new` are general purpose. They don't know:
- my cache line is 64 bytes
- my L3 boundary is at 8MB  
- False sharing between threads costs 3.5x throughput
- TLB pressure kills performance beyond 4MB working set

---

## What it does

- **Cache-line aligned allocation** ~ every pointer at 64-byte boundary
- **Size-class slab allocator** ~ O(1) allocation and free
- **Thread-local caches** ~ zero lock contention on the hot path
- **Arena-based** ~ one `mmap` at startup, no OS calls during allocation
- **Tensor-aware** ~ size classes tuned for common tensor shapes
- **NUMA-aware** ~ allocates on the node closest to the calling thread

---

## Architecture
```
┌─────────────────────────────────────┐
│         TESSERACT API               │
│   allocate(size) / free(ptr, size)  │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│      Thread Local Cache             │
│   Per-thread free lists             │
│   Zero contention, zero sharing     │
└──────────────┬──────────────────────┘
               │ empty/full
┌──────────────▼──────────────────────┐
│      Central Pool                   │
│   Segregated free lists             │
│   One mutex per size class          │
└──────────────┬──────────────────────┘
               │ needs more memory
┌──────────────▼──────────────────────┐
│      Arena                          │
│   mmap'd 1GB at startup             │
│   Bump pointer allocation           │
│   64-byte aligned always            │
└─────────────────────────────────────┘
```

---

## Size Classes
```
Class 1  →  1  -  64  bytes   (small tensors, scalars)
Class 2  →  65 -  256 bytes   (small vectors)
Class 3  →  257 - 4096 bytes  (medium tensors)
Class 4  →  4KB - 256KB       (typical weight matrices)
Class 5  →  256KB - 1MB       (large feature maps)
Class 6  →  1MB - 16MB        (very large tensors)
```

---

## Benchmarks

### Micro-benchmark: 1M Random-Size Allocations

| Allocator | Time | Speedup |
|-----------|------|---------|
| tesseract | 14.19ms | 1.0x |
| tcmalloc | 21.57ms | 1.52x slower |
| jemalloc | 50.68ms | 3.57x slower |
| malloc | 52.21ms | 3.68x slower |

### Real Workload: Web Server (10M HTTP Requests)

| Allocator | Time | Throughput |
|-----------|------|-----------|
| tesseract | 247ms | 40.4M req/sec |
| malloc | 962ms | 10.4M req/sec |
| **Speedup** | **3.89x** | - |

**Results:** tesseract beats malloc 3.68x on micro-benchmarks and 3.89x on realistic web server load. Outperforms both tcmalloc and jemalloc.

---

## Build

