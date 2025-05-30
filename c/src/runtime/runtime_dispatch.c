/**
 * runtime_dispatch.c - Implementation of runtime dispatch based on detected hardware
 * 
 * This file contains the implementation of runtime dispatch for selecting the optimal
 * function implementations based on the detected hardware features.
 */

 #include "../../include/runtime/runtime_dispatch.h"
 #include <stdio.h>
 
 // Declarations of all implementation variants
 void array_add_scalar(const float* a, const float* b, float* c, int n);
 void array_add_sse2(const float* a, const float* b, float* c, int n);
 void array_add_avx(const float* a, const float* b, float* c, int n);
 void array_add_avx2(const float* a, const float* b, float* c, int n);
 void array_add_avx512(const float* a, const float* b, float* c, int n);
 
 // Selected function pointers (default to scalar implementations)
 static ArrayAddFn array_add_fn = array_add_scalar;
 
 /**
  * Initialize runtime dispatch based on detected hardware features
  */
 void init_runtime_dispatch(const HardwareProfile* hw) {
     printf("Initializing runtime dispatch for optimal performance...\n");
     
     // Select array addition implementation based on CPU features
     if (hw->cpu_features.avx512f) {
         printf("- Using AVX-512 instructions for array operations\n");
         array_add_fn = array_add_avx512;
     } else if (hw->cpu_features.avx2) {
         printf("- Using AVX2 instructions for array operations\n");
         array_add_fn = array_add_avx2;
     } else if (hw->cpu_features.avx) {
         printf("- Using AVX instructions for array operations\n");
         array_add_fn = array_add_avx;
     } else if (hw->cpu_features.sse2) {
         printf("- Using SSE2 instructions for array operations\n");
         array_add_fn = array_add_sse2;
     } else {
         printf("- Using scalar operations (no SIMD)\n");
         array_add_fn = array_add_scalar;
     }
 }
 
 /**
  * Get the optimal function for array addition
  */
 ArrayAddFn get_array_add_function(void) {
     return array_add_fn;
 }
 
 /**
  * Implementation of array addition functions for different instruction sets
  * These are just example implementations - in a real library, these would be
  * highly optimized for each instruction set.
  */
 
 // Scalar implementation (fallback)
 void array_add_scalar(const float* a, const float* b, float* c, int n) {
     for (int i = 0; i < n; i++) {
         c[i] = a[i] + b[i];
     }
 }
 
 // SSE2 implementation
 #ifdef __SSE2__
 #include <emmintrin.h>
 #endif
 
 void array_add_sse2(const float* a, const float* b, float* c, int n) {
 #ifdef __SSE2__
     int i;
     // Process blocks of 4 floats (SSE2 works with 128-bit vectors = 4x32-bit floats)
     for (i = 0; i <= n - 4; i += 4) {
         __m128 va = _mm_load_ps(&a[i]);
         __m128 vb = _mm_load_ps(&b[i]);
         __m128 vc = _mm_add_ps(va, vb);
         _mm_store_ps(&c[i], vc);
     }
     
     // Handle remaining elements
     for (; i < n; i++) {
         c[i] = a[i] + b[i];
     }
 #else
     // Fallback to scalar if SSE2 not available at compile time
     array_add_scalar(a, b, c, n);
 #endif
 }
 
 // AVX implementation
 #ifdef __AVX__
 #include <immintrin.h>
 #endif
 
 void array_add_avx(const float* a, const float* b, float* c, int n) {
 #ifdef __AVX__
     int i;
     // Process blocks of 8 floats (AVX works with 256-bit vectors = 8x32-bit floats)
     for (i = 0; i <= n - 8; i += 8) {
         __m256 va = _mm256_load_ps(&a[i]);
         __m256 vb = _mm256_load_ps(&b[i]);
         __m256 vc = _mm256_add_ps(va, vb);
         _mm256_store_ps(&c[i], vc);
     }
     
     // Handle remaining elements
     for (; i < n; i++) {
         c[i] = a[i] + b[i];
     }
 #else
     // Fallback to SSE2 if AVX not available at compile time
     array_add_sse2(a, b, c, n);
 #endif
 }
 
 // AVX2 implementation
 #ifdef __AVX2__
 #include <immintrin.h>
 #endif
 
 void array_add_avx2(const float* a, const float* b, float* c, int n) {
 #ifdef __AVX2__
     // For this simple operation, AVX2 and AVX are the same
     // In more complex operations, AVX2 provides enhanced integer operations
     array_add_avx(a, b, c, n);
 #else
     // Fallback to AVX if AVX2 not available at compile time
     array_add_avx(a, b, c, n);
 #endif
 }
 
 // AVX-512 implementation
 #ifdef __AVX512F__
 #include <immintrin.h>
 #endif
 
 void array_add_avx512(const float* a, const float* b, float* c, int n) {
 #ifdef __AVX512F__
     int i;
     // Process blocks of 16 floats (AVX-512 works with 512-bit vectors = 16x32-bit floats)
     for (i = 0; i <= n - 16; i += 16) {
         __m512 va = _mm512_load_ps(&a[i]);
         __m512 vb = _mm512_load_ps(&b[i]);
         __m512 vc = _mm512_add_ps(va, vb);
         _mm512_store_ps(&c[i], vc);
     }
     
     // Handle remaining elements
     for (; i < n; i++) {
         c[i] = a[i] + b[i];
     }
 #else
     // Fallback to AVX2 if AVX-512 not available at compile time
     array_add_avx2(a, b, c, n);
 #endif
 }