/**
 * test_hardware_detection.c - Test program for hardware detection library
 * 
 * This program demonstrates how to use the hardware detection library
 * to optimize application behavior based on available hardware features.
 */

 #include "../../include/hardware/hardware_detection.h"
 #include "../../include/runtime/runtime_dispatch.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <math.h>

 // Benchmark different implementations to verify performance gains
 void benchmark_array_operations(const HardwareProfile* hw) {
     printf("\n=== BENCHMARK: ARRAY ADDITION ===\n");
     
     const int array_size = 10000000; // 10 million elements
     const int num_runs = 5;
     
     // Allocate arrays with aligned memory for better vectorization
     size_t alignment = hw->cache_info.cache_line_size_bytes > 0 ? 
                        hw->cache_info.cache_line_size_bytes : 64;
                        
     float *a, *b, *c;
     
 #ifdef _WIN32
     // Windows aligned allocation
     a = (float*)_aligned_malloc(array_size * sizeof(float), alignment);
     b = (float*)_aligned_malloc(array_size * sizeof(float), alignment);
     c = (float*)_aligned_malloc(array_size * sizeof(float), alignment);
 #else
     // POSIX aligned allocation
     posix_memalign((void**)&a, alignment, array_size * sizeof(float));
     posix_memalign((void**)&b, alignment, array_size * sizeof(float));
     posix_memalign((void**)&c, alignment, array_size * sizeof(float));
 #endif
 
     if (!a || !b || !c) {
         printf("Memory allocation failed\n");
         return;
     }
     
     // Initialize arrays
     for (int i = 0; i < array_size; i++) {
         a[i] = (float)i;
         b[i] = (float)(i * 2);
     }
     
     // Get the optimized function from runtime dispatch
     ArrayAddFn add_fn = get_array_add_function();
     
     // Run the benchmark
     printf("Running array addition benchmark (%d elements, %d runs)...\n", 
            array_size, num_runs);
     
     clock_t start = clock();
     
     for (int run = 0; run < num_runs; run++) {
         add_fn(a, b, c, array_size);
     }
     
     clock_t end = clock();
     double elapsed_seconds = (double)(end - start) / CLOCKS_PER_SEC;
     
     printf("Time: %.4f seconds\n", elapsed_seconds);
     printf("Performance: %.2f million elements/second\n", 
            (array_size * num_runs) / (elapsed_seconds * 1000000));
     
     // Verify correctness (check a few elements)
     printf("Verification: ");
     bool correct = true;
     for (int i = 0; i < 100; i++) {
         int idx = i * (array_size / 100);
         if (c[idx] != a[idx] + b[idx]) {
             printf("Error at index %d: expected %.2f, got %.2f\n", 
                    idx, a[idx] + b[idx], c[idx]);
             correct = false;
             break;
         }
     }
     
     if (correct) {
         printf("PASSED\n");
     }
     
     // Clean up
 #ifdef _WIN32
     _aligned_free(a);
     _aligned_free(b);
     _aligned_free(c);
 #else
     free(a);
     free(b);
     free(c);
 #endif
 }
 
 // Suggest optimal block sizes for matrix operations
 void suggest_matrix_blocking(const HardwareProfile* hw) {
     printf("\n=== MATRIX OPERATION RECOMMENDATIONS ===\n");
     
     if (hw->cache_info.l1_data_cache_size_kb <= 0 || 
         hw->cache_info.l2_cache_size_kb <= 0) {
         printf("Cache information not available for optimal blocking.\n");
         return;
     }
     
     // Calculate optimal block sizes based on cache
     int l1_block_size = sqrt(hw->cache_info.l1_data_cache_size_kb * 1024 / (3 * sizeof(float)));
     int l2_block_size = sqrt(hw->cache_info.l2_cache_size_kb * 1024 / (3 * sizeof(float)));
     
     // Align to cache line size
     int cache_line_floats = hw->cache_info.cache_line_size_bytes / sizeof(float);
     if (cache_line_floats > 0) {
         l1_block_size = (l1_block_size / cache_line_floats) * cache_line_floats;
         l2_block_size = (l2_block_size / cache_line_floats) * cache_line_floats;
     }
     
     // Suggest block sizes
     printf("For matrix operations (multiplication, etc.):\n");
     printf("- L1 optimal block size: %d x %d\n", l1_block_size, l1_block_size);
     printf("- L2 optimal block size: %d x %d\n", l2_block_size, l2_block_size);
     
     // Thread parallelism recommendation for matrix ops
     printf("\nFor parallelizing matrix operations:\n");
     if (hw->cpu_cores.logical_cores >= 4) {
         printf("- Use %d threads (physical cores) for best performance\n", 
                hw->cpu_cores.physical_cores);
     } else {
         printf("- Limited thread parallelism available (%d cores)\n", 
                hw->cpu_cores.logical_cores);
     }
     
     // GPU recommendation
     if (hw->gpu_info.has_cuda_gpu && hw->gpu_info.compute_capability_major >= 3) {
         printf("- For large matrices (>2048x2048), consider using GPU acceleration\n");
     }
 }
 
 int main(void) {
     printf("===================================================\n");
     printf("     HARDWARE DETECTION FOR ARRAY OPTIMIZATION     \n");
     printf("===================================================\n\n");
     
     // Detect hardware features
     HardwareProfile hw = detect_hardware_profile();
     
     // Print detected hardware profile
     print_hardware_profile(&hw);
     
     // Measure memory bandwidth
     printf("\n=== MEMORY BANDWIDTH TEST ===\n");
     double bandwidth = estimate_memory_bandwidth(&hw);
     if (bandwidth > 0) {
         printf("Estimated memory bandwidth: %.2f MB/s (%.2f GB/s)\n", 
                bandwidth, bandwidth / 1024.0);
     } else {
         printf("Could not estimate memory bandwidth\n");
     }
     
     // Initialize runtime dispatch based on detected features
     init_runtime_dispatch(&hw);
     
     // Get the selected function name for information
    //  ArrayAddFn selected_fn = get_array_add_function();
     printf("\n=== SELECTED IMPLEMENTATIONS ===\n");
     printf("Array addition: ");
     
     // This requires some way to identify which function was selected
     // We'll just make an educated guess based on CPU features
     if (hw.cpu_features.avx512f) {
         printf("AVX-512 implementation\n");
     } else if (hw.cpu_features.avx2) {
         printf("AVX2 implementation\n");
     } else if (hw.cpu_features.avx) {
         printf("AVX implementation\n");
     } else if (hw.cpu_features.sse2) {
         printf("SSE2 implementation\n");
     } else {
         printf("Scalar implementation\n");
     }
     
     // Run benchmark
     benchmark_array_operations(&hw);
     
     // Suggest optimal matrix blocking
     suggest_matrix_blocking(&hw);
     
     printf("\n===================================================\n");
     printf("Hardware detection completed successfully!\n");
     printf("===================================================\n");
     
     return 0;
 }