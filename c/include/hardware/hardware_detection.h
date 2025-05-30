// hardware_detection.h - Clean and focused hardware detection header
// Only for optimizing an array library and future ML library

#ifndef HARDWARE_DETECTION_H
#define HARDWARE_DETECTION_H

#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

//====================
// Structs
//====================

typedef struct {
    bool mmx;
    bool sse;
    bool sse2;
    bool sse3;
    bool ssse3;
    bool sse4_1;
    bool sse4_2;
    bool avx;
    bool avx2;
    bool avx512f;
    bool fma;
    bool neon;  // For ARM
    bool sve;   // For ARM
} CPUFeatures;

typedef struct {
    int l1_data_cache_size_kb;
    int l1_instruction_cache_size_kb;
    int l2_cache_size_kb;
    int l3_cache_size_kb;
    int cache_line_size_bytes;
} CacheInfo;

typedef struct {
    int physical_cores;
    int logical_cores;
} CPUCores;

typedef struct {
    long total_ram_mb;
} MemoryInfo;

typedef struct {
    bool has_cuda_gpu;
    char gpu_name[256];
    int compute_capability_major;
    int compute_capability_minor;
} GPUInfo;

typedef struct {
    CPUFeatures cpu_features;
    CacheInfo cache_info;
    CPUCores cpu_cores;
    MemoryInfo memory_info;
    GPUInfo gpu_info;
} HardwareProfile;

//====================
// Functions
//====================

// Detect and fill all fields of the hardware profile
HardwareProfile detect_hardware_profile(void);

// Print a summary of detected hardware
void print_hardware_profile(const HardwareProfile* hw);

// Optional: Rough estimate of memory bandwidth (MB/s)
double estimate_memory_bandwidth(const HardwareProfile* hw);


#ifdef __cplusplus
}
#endif

#endif // HARDWARE_DETECTION_H
