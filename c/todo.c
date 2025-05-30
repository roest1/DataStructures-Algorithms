// Instead of repeating POSIX vs Windows logic everywhere, create in a new file:
#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdlib.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* aligned_malloc(size_t size, size_t alignment);
void aligned_free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif // MEMORY_UTILS_H

#include "../../include/utils/memory.h"

#ifdef _WIN32
#include <malloc.h>
#endif

void* aligned_malloc(size_t size, size_t alignment) {
#ifdef _WIN32
    return _aligned_malloc(size, alignment);
#else
    void* ptr = NULL;
    if (posix_memalign(&ptr, alignment, size) != 0) {
        return NULL;
    }
    return ptr;
#endif
}

void aligned_free(void* ptr) {
#ifdef _WIN32
    _aligned_free(ptr);
#else
    free(ptr);
#endif
}

// add benchmark
#include "../../include/hardware/hardware_detection.h"
#include "../../include/runtime/runtime_dispatch.h"
#include "../../include/utils/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void benchmark_array_add(ArrayAddFn fn, const char* label, int array_size, int num_runs) {
    float* a = (float*)aligned_malloc(array_size * sizeof(float), 64);
    float* b = (float*)aligned_malloc(array_size * sizeof(float), 64);
    float* c = (float*)aligned_malloc(array_size * sizeof(float), 64);

    for (int i = 0; i < array_size; i++) {
        a[i] = (float)i;
        b[i] = (float)(i * 2);
    }

    clock_t start = clock();

    for (int run = 0; run < num_runs; run++) {
        fn(a, b, c, array_size);
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%s: %.2f million elements/sec\n", label,
           (array_size * num_runs) / (elapsed * 1e6));

    aligned_free(a);
    aligned_free(b);
    aligned_free(c);
}

int main(void) {
    printf("===================================================\n");
    printf("               ARRAY ADD BENCHMARKS                \n");
    printf("===================================================\n");

    HardwareProfile hw = detect_hardware_profile();
    init_runtime_dispatch(&hw);

    int array_size = 10 * 1000 * 1000; // 10 million
    int num_runs = 5;

    printf("\nBenchmarking...\n");

    benchmark_array_add(array_add_scalar, "Scalar", array_size, num_runs);

    if (hw.cpu_features.sse2) {
        benchmark_array_add(array_add_sse2, "SSE2", array_size, num_runs);
    }

    if (hw.cpu_features.avx) {
        benchmark_array_add(array_add_avx, "AVX", array_size, num_runs);
    }

    if (hw.cpu_features.avx2) {
        benchmark_array_add(array_add_avx2, "AVX2", array_size, num_runs);
    }

    if (hw.cpu_features.avx512f) {
        benchmark_array_add(array_add_avx512, "AVX-512", array_size, num_runs);
    }

    printf("\n===================================================\n");
    return 0;
}


