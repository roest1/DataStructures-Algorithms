/**
 * hardware_detection.c - Implementation of hardware detection for performance optimization
 * 
 * Detects and reports hardware features relevant for high-performance computing, including:
 * - CPU instruction sets (SSE2, AVX, AVX2, AVX-512, NEON, SVE)
 * - CPU cores and threads (physical and logical)
 * - Cache sizes (L1, L2, L3, line size)
 * - GPU availability (CUDA)
 * - GPU compute capability (for CUDA to pick optimal kernels)
 * - RAM
 * - Memory bandwidth (for deciding between CPU/GPU or blocking strategy)
 */

 #include "../../include/hardware/hardware_detection.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <math.h>
 
 // Platform-specific includes
 #ifdef _WIN32
     #include <windows.h>
     #include <intrin.h>
 #else
     #include <unistd.h>
     #include <sys/sysinfo.h>
     #include <sys/utsname.h>
     #ifdef __APPLE__
         #include <sys/sysctl.h>
     #endif
 #endif
 
 // Function prototypes for internal use
 static void detect_cpu_features(CPUFeatures* cpu_features);
 static void detect_cpu_cores(CPUCores* cpu_cores);
 static void detect_cache_sizes(CacheInfo* cache_info);
 static void detect_memory_info(MemoryInfo* memory_info);
 static void detect_gpu_info(GPUInfo* gpu_info);
 
 // For non-MSV compilers use manual cpuid inline assembly
 #if !defined(_MSC_VER) && (defined(__x86_64__) || defined(__i386))
 static inline void __cpuid(int cpu_info[4], int function_id) {
     __asm__ __volatile__ (
         "cpuid"
         : "=a" (cpu_info[0]), "=b" (cpu_info[1]), "=c" (cpu_info[2]), "=d" (cpu_info[3])
         : "a" (function_id), "c" (0)
     );
 }
 
 static inline void __cpuidex(int cpu_info[4], int function_id, int subfunction_id) {
     __asm__ __volatile__ (
         "cpuid"
         : "=a" (cpu_info[0]), "=b" (cpu_info[1]), "=c" (cpu_info[2]), "=d" (cpu_info[3])
         : "a" (function_id), "c" (subfunction_id)
     );
 }
 #endif
 
 /**
  * Detect and fill all fields of the hardware profile
  */
 HardwareProfile detect_hardware_profile(void) {
     HardwareProfile hw = {0}; // Initialize to all zeros
     
     detect_cpu_features(&hw.cpu_features);
     detect_cpu_cores(&hw.cpu_cores);
     detect_cache_sizes(&hw.cache_info);
     detect_memory_info(&hw.memory_info);
     detect_gpu_info(&hw.gpu_info);
     
     return hw;
 }
 
 /**
  * Detect CPU instruction set support using CPUID
  */
 static void detect_cpu_features(CPUFeatures* cpu_features) {
     // Initialize to all false
     memset(cpu_features, 0, sizeof(CPUFeatures));
     
 #if defined(__x86_64__) || defined(_M_X64) || defined(__i386) || defined(_M_IX86)
     // x86/x64 CPU detection
     int cpu_info[4] = {0};
     
     // Function 1: EDX and ECX contain feature bits
     __cpuid(cpu_info, 1);
     
     // EDX flags
     cpu_features->mmx = (cpu_info[3] & (1 << 23)) != 0;
     cpu_features->sse = (cpu_info[3] & (1 << 25)) != 0;
     cpu_features->sse2 = (cpu_info[3] & (1 << 26)) != 0;
     
     // ECX flags
     cpu_features->sse3 = (cpu_info[2] & (1 << 0)) != 0;
     cpu_features->ssse3 = (cpu_info[2] & (1 << 9)) != 0;
     cpu_features->sse4_1 = (cpu_info[2] & (1 << 19)) != 0;
     cpu_features->sse4_2 = (cpu_info[2] & (1 << 20)) != 0;
     cpu_features->fma = (cpu_info[2] & (1 << 12)) != 0;
     
     // Function 7: EBX and ECX contain extended feature bits
     __cpuidex(cpu_info, 7, 0);
     
     // EBX flags
     cpu_features->avx2 = (cpu_info[1] & (1 << 5)) != 0;
     cpu_features->avx512f = (cpu_info[1] & (1 << 16)) != 0;
     
     // Detect AVX via XSAVE/OSXSAVE and AVX bit
     __cpuid(cpu_info, 1);
     bool osxsave = (cpu_info[2] & (1 << 27)) != 0;
     cpu_features->avx = osxsave && (cpu_info[2] & (1 << 28)) != 0;
     
     // Additional check for AVX: ensure OS supports AVX context save/restore
     if (cpu_features->avx) {
         // Check OS support for saving AVX registers
         unsigned long long xcr0 = 0;
 #if defined(_MSC_VER)
         xcr0 = _xgetbv(0);
 #else
         __asm__ volatile("xgetbv" : "=a"(xcr0) : "c"(0) : "edx");
 #endif
         // Bit 2 indicates AVX register support
         cpu_features->avx = (xcr0 & 6) == 6;
         
         // For AVX-512, we need bits 5,6,7 (ZMM_Hi256, Hi16_ZMM, OPMASK)
         if (cpu_features->avx512f) {
             cpu_features->avx512f = (xcr0 & 0xE0) == 0xE0;
         }
     }
     
 #elif defined(__arm__) || defined(__aarch64__)
     // ARM architecture detection
     
     // Simple detection based on compile-time flags
     #if defined(__ARM_NEON) || defined(__ARM_NEON__)
         cpu_features->neon = true;
     #endif
     
     #if defined(__ARM_FEATURE_SVE)
         cpu_features->sve = true;
     #endif
     
     // Alternative: parse /proc/cpuinfo for more detailed ARM feature detection on Linux
     #if defined(__linux__)
     FILE* fp = fopen("/proc/cpuinfo", "r");
     if (fp) {
         char line[512];
         while (fgets(line, sizeof(line), fp)) {
             if (strstr(line, "Features") != NULL) {
                 if (strstr(line, "neon") != NULL || strstr(line, "asimd") != NULL) {
                     cpu_features->neon = true;
                 }
                 if (strstr(line, "sve") != NULL) {
                     cpu_features->sve = true;
                 }
                 break;
             }
         }
         fclose(fp);
     }
     #endif
 #endif
 }
 
 /**
  * Detect number of CPU cores
  */
 static void detect_cpu_cores(CPUCores* cpu_cores) {
 #ifdef _WIN32
     // Windows detection
     SYSTEM_INFO sysInfo;
     GetSystemInfo(&sysInfo);
     cpu_cores->logical_cores = sysInfo.dwNumberOfProcessors;
     
     // For physical cores, need to query more advanced info
     DWORD buffer_size = 0;
     GetLogicalProcessorInformation(NULL, &buffer_size);
     
     if (buffer_size > 0) {
         SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)malloc(buffer_size);
         GetLogicalProcessorInformation(buffer, &buffer_size);
         
         DWORD processor_core_count = 0;
         DWORD num_elements = buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
         
         for (DWORD i = 0; i < num_elements; i++) {
             if (buffer[i].Relationship == RelationProcessorCore) {
                 processor_core_count++;
             }
         }
         
         cpu_cores->physical_cores = processor_core_count;
         free(buffer);
     } else {
         cpu_cores->physical_cores = cpu_cores->logical_cores; // Fallback
     }
     
 #elif defined(__APPLE__)
     // macOS detection
     int num_cpu_u;
     size_t len = sizeof(num_cpu_u);
     sysctlbyname("hw.physicalcpu", &cpu_cores->physical_cores, &len, NULL, 0);
     sysctlbyname("hw.logicalcpu", &cpu_cores->logical_cores, &len, NULL, 0);
     
 #else
     // Linux and other Unix-like systems
     FILE* fp;
     char line[256];
     
     // Get logical cores
     cpu_cores->logical_cores = sysconf(_SC_NPROCESSORS_ONLN);
     
     // Try to determine physical cores by parsing /proc/cpuinfo
     int cores_per_socket = 0;
     int physical_id = -1;
     int last_physical_id = -1;
     int socket_count = 0;
     
     fp = fopen("/proc/cpuinfo", "r");
     if (fp) {
         while (fgets(line, sizeof(line), fp)) {
             if (strstr(line, "cpu cores")) {
                 sscanf(line, "cpu cores : %d", &cores_per_socket);
             } else if (strstr(line, "physical id")) {
                 sscanf(line, "physical id : %d", &physical_id);
                 if (physical_id != last_physical_id) {
                     socket_count++;
                     last_physical_id = physical_id;
                 }
             }
         }
         fclose(fp);
         
         if (cores_per_socket > 0 && socket_count > 0) {
             cpu_cores->physical_cores = cores_per_socket * socket_count;
         } else {
             // Fallback if we can't parse details
             cpu_cores->physical_cores = cpu_cores->logical_cores;
         }
     } else {
         cpu_cores->physical_cores = cpu_cores->logical_cores; // Fallback
     }
 #endif
 
     // Sanity check: physical cores should be at least 1
     if (cpu_cores->physical_cores < 1) cpu_cores->physical_cores = 1;
     if (cpu_cores->logical_cores < 1) cpu_cores->logical_cores = 1;
 
     // Sanity check: logical cores should be at least equal to physical cores
     if (cpu_cores->logical_cores < cpu_cores->physical_cores)
         cpu_cores->logical_cores = cpu_cores->physical_cores;
 }
 
 /**
  * Detect cache sizes
  */
 static void detect_cache_sizes(CacheInfo* cache_info) {
     // Initialize to all -1 (unknown)
     cache_info->l1_data_cache_size_kb = -1;
     cache_info->l1_instruction_cache_size_kb = -1;
     cache_info->l2_cache_size_kb = -1;
     cache_info->l3_cache_size_kb = -1;
     cache_info->cache_line_size_bytes = -1;
     
 #ifdef _WIN32
     // Windows cache detection through CPUID
     int cpu_info[4] = {0};
     
     // Try to get cache information from CPUID leaf 4
     int cache_level = 0;
     int i = 0;
     do {
         __cpuidex(cpu_info, 4, i);
         int cache_type = cpu_info[0] & 0x1F;
         if (cache_type == 0) break; // No more caches
         
         cache_level = (cpu_info[0] >> 5) & 0x7;
         int ways = ((cpu_info[1] >> 22) & 0x3FF) + 1;
         int partitions = ((cpu_info[1] >> 12) & 0x3FF) + 1;
         int line_size = (cpu_info[1] & 0xFFF) + 1;
         int sets = cpu_info[2] + 1;
         int cache_size = ways * partitions * line_size * sets / 1024; // In KB
         
         // Update cache info based on level and type
         if (cache_level == 1) {
             if (cache_type == 1) { // Data cache
                 cache_info->l1_data_cache_size_kb = cache_size;
                 cache_info->cache_line_size_bytes = line_size;
             } else if (cache_type == 2) { // Instruction cache
                 cache_info->l1_instruction_cache_size_kb = cache_size;
             }
         } else if (cache_level == 2) {
             cache_info->l2_cache_size_kb = cache_size;
             if (cache_info->cache_line_size_bytes < 0) {
                 cache_info->cache_line_size_bytes = line_size;
             }
         } else if (cache_level == 3) {
             cache_info->l3_cache_size_kb = cache_size;
         }
         
         i++;
     } while (i < 10); // Just to prevent infinite loop
     
     // If CPUID leaf 4 didn't give us the info, try leaf 2
     if (cache_info->l1_data_cache_size_kb < 0 || cache_info->l2_cache_size_kb < 0) {
         __cpuid(cpu_info, 2);
         
         // Parse the descriptors from EAX, EBX, ECX, EDX
         // This is complex and vendor-specific - just an example structure
         // Intel's descriptors are documented in their manuals
         
         // Fallback: use reasonable defaults
         if (cache_info->l1_data_cache_size_kb < 0)
             cache_info->l1_data_cache_size_kb = 32; // Common L1 size
         
         if (cache_info->l2_cache_size_kb < 0)
             cache_info->l2_cache_size_kb = 256; // Common L2 size
         
         if (cache_info->cache_line_size_bytes < 0)
             cache_info->cache_line_size_bytes = 64; // Common cache line size
     }
     
 #elif defined(__APPLE__)
     // macOS cache detection
     size_t len;
     int64_t cache_size;
     
     // L1 data cache
     len = sizeof(cache_size);
     if (sysctlbyname("hw.l1dcachesize", &cache_size, &len, NULL, 0) == 0) {
         cache_info->l1_data_cache_size_kb = (int)(cache_size / 1024); // Convert to KB
     }
     
     // L1 instruction cache
     if (sysctlbyname("hw.l1icachesize", &cache_size, &len, NULL, 0) == 0) {
         cache_info->l1_instruction_cache_size_kb = (int)(cache_size / 1024);
     }
     
     // L2 cache
     if (sysctlbyname("hw.l2cachesize", &cache_size, &len, NULL, 0) == 0) {
         cache_info->l2_cache_size_kb = (int)(cache_size / 1024);
     }
     
     // L3 cache
     if (sysctlbyname("hw.l3cachesize", &cache_size, &len, NULL, 0) == 0) {
         cache_info->l3_cache_size_kb = (int)(cache_size / 1024);
     }
     
     // Cache line size
     int line_size;
     len = sizeof(line_size);
     if (sysctlbyname("hw.cachelinesize", &line_size, &len, NULL, 0) == 0) {
         cache_info->cache_line_size_bytes = line_size;
     }
     
 #else
     // Linux cache detection
     FILE* fp;
     
     // Use /sys/devices/system/cpu/cpu0/cache/index*/ directories
     char cache_path[128];
     int cache_level, cache_size;
     char cache_type[64];
     
     for (int index = 0; index < 4; index++) { // Try indexes 0-3
         snprintf(cache_path, sizeof(cache_path), 
                  "/sys/devices/system/cpu/cpu0/cache/index%d/level", index);
         
         fp = fopen(cache_path, "r");
         if (!fp) continue;
         
         fscanf(fp, "%d", &cache_level);
         fclose(fp);
         
         // Get cache type (data, instruction, or unified)
         snprintf(cache_path, sizeof(cache_path), 
                  "/sys/devices/system/cpu/cpu0/cache/index%d/type", index);
         fp = fopen(cache_path, "r");
         if (!fp) continue;
         
         fscanf(fp, "%s", cache_type);
         fclose(fp);
         
         // Get cache size
         snprintf(cache_path, sizeof(cache_path), 
                  "/sys/devices/system/cpu/cpu0/cache/index%d/size", index);
         fp = fopen(cache_path, "r");
         if (!fp) continue;
         
         if (fscanf(fp, "%dK", &cache_size) != 1) {
             // Try alternative format
             rewind(fp);
             if (fscanf(fp, "%d", &cache_size) != 1) {
                 cache_size = -1;
             }
         }
         fclose(fp);
         
         // Get cache line size
         snprintf(cache_path, sizeof(cache_path), 
                  "/sys/devices/system/cpu/cpu0/cache/index%d/coherency_line_size", index);
         fp = fopen(cache_path, "r");
         int line_size = -1;
         if (fp) {
             fscanf(fp, "%d", &line_size);
             fclose(fp);
         }
         
         // Store the information based on level and type
         if (cache_level == 1) {
             if (strcmp(cache_type, "Data") == 0) {
                 cache_info->l1_data_cache_size_kb = cache_size;
                 cache_info->cache_line_size_bytes = line_size;
             } else if (strcmp(cache_type, "Instruction") == 0) {
                 cache_info->l1_instruction_cache_size_kb = cache_size;
             } else if (strcmp(cache_type, "Unified") == 0) {
                 cache_info->l1_data_cache_size_kb = cache_size;
                 cache_info->l1_instruction_cache_size_kb = cache_size;
                 cache_info->cache_line_size_bytes = line_size;
             }
         } else if (cache_level == 2) {
             cache_info->l2_cache_size_kb = cache_size;
             if (cache_info->cache_line_size_bytes < 0) {
                 cache_info->cache_line_size_bytes = line_size;
             }
         } else if (cache_level == 3) {
             cache_info->l3_cache_size_kb = cache_size;
         }
     }
 #endif
 
     // Fallback values for common architectures if detection failed
     if (cache_info->cache_line_size_bytes < 0) 
         cache_info->cache_line_size_bytes = 64;  // Most common value for modern CPUs
     
     if (cache_info->l1_data_cache_size_kb < 0) 
         cache_info->l1_data_cache_size_kb = 32;  // Common L1 D-cache size
     
     if (cache_info->l1_instruction_cache_size_kb < 0) 
         cache_info->l1_instruction_cache_size_kb = 32;  // Common L1 I-cache size
     
     if (cache_info->l2_cache_size_kb < 0) 
         cache_info->l2_cache_size_kb = 256;  // Common L2 cache size
 }
 
 /**
  * Detect RAM information
  */
 static void detect_memory_info(MemoryInfo* memory_info) {
     memory_info->total_ram_mb = 0;  // Initialize to zero
 
 #ifdef _WIN32
     // Windows RAM detection
     MEMORYSTATUSEX memInfo;
     memInfo.dwLength = sizeof(MEMORYSTATUSEX);
     if (GlobalMemoryStatusEx(&memInfo)) {
         memory_info->total_ram_mb = (long)(memInfo.ullTotalPhys / (1024 * 1024));
     }
     
 #elif defined(__APPLE__)
     // macOS RAM detection
     int64_t mem_size;
     size_t len = sizeof(mem_size);
     
     if (sysctlbyname("hw.memsize", &mem_size, &len, NULL, 0) == 0) {
         memory_info->total_ram_mb = (long)(mem_size / (1024 * 1024));
     }
     
 #else
     // Linux RAM detection
     struct sysinfo info;
     
     if (sysinfo(&info) == 0) {
         memory_info->total_ram_mb = (long)((info.totalram * info.mem_unit) / (1024 * 1024));
     }
 #endif
 
     // Fallback: provide a sane default value if detection failed
     if (memory_info->total_ram_mb <= 0) {
         memory_info->total_ram_mb = 1024;  // Assume at least 1GB of RAM
     }
 }
 
 /**
  * Detect GPU information (CUDA)
  */
 static void detect_gpu_info(GPUInfo* gpu_info) {
     // Initialize to defaults
     gpu_info->has_cuda_gpu = false;
     strcpy(gpu_info->gpu_name, "Unknown");
     gpu_info->compute_capability_major = -1;
     gpu_info->compute_capability_minor = -1;
     
 #ifdef _WIN32
     // Windows GPU detection would need to use CUDA runtime API or NVML
     // For now, check if nvidia-smi exists
     FILE* fp = _popen("where nvidia-smi", "r");
     if (fp) {
         char buffer[512];
         if (fgets(buffer, sizeof(buffer), fp) != NULL) {
             // If nvidia-smi exists, try to get GPU info
             _pclose(fp);
             fp = _popen("nvidia-smi --query-gpu=name,driver_version,compute_capability --format=csv,noheader 2>NUL", "r");
             if (!fp) {
                _popen("nvidia-smi --query-gpu=name --format=csv,noheader 2>/dev/null", "r");
             }
             if (fp) {
                 if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                     buffer[strcspn(buffer, "\n")] = 0; // Remove newline
                     gpu_info->has_cuda_gpu = true;
                     
                     // Parse the CSV format
                     char* token = strtok(buffer, ",");
                     if (token) {
                         strncpy(gpu_info->gpu_name, token, sizeof(gpu_info->gpu_name) - 1);
                         
                         // Skip driver version
                         token = strtok(NULL, ",");
                         
                         // Get compute capability
                         token = strtok(NULL, ",");
                         if (token) {
                             sscanf(token, "%d.%d", 
                                    &gpu_info->compute_capability_major, 
                                    &gpu_info->compute_capability_minor);
                         }
                     }
                 }
                 _pclose(fp);
             }
         } else {
             _pclose(fp);
         }
     }
     
 #else
     // Try to detect NVIDIA GPU with nvidia-smi
     FILE* fp = popen("nvidia-smi --query-gpu=name,driver_version,compute_capability --format=csv,noheader 2>/dev/null", "r");
     
     if (fp) {
         char buffer[512];
         if (fgets(buffer, sizeof(buffer), fp) != NULL) {
             buffer[strcspn(buffer, "\n")] = 0; // Remove newline
             gpu_info->has_cuda_gpu = true;
             
             // Parse the GPU name and compute capability
             char* token = strtok(buffer, ",");
             if (token) {
                 strncpy(gpu_info->gpu_name, token, sizeof(gpu_info->gpu_name) - 1);
                 
                 // Move to driver version (skip)
                 token = strtok(NULL, ",");
                 
                 // Get compute capability
                 token = strtok(NULL, ",");
                 if (token) {
                     sscanf(token, "%d.%d", 
                            &gpu_info->compute_capability_major, 
                            &gpu_info->compute_capability_minor);
                 }
             }
         }
         pclose(fp);
     }
     
     // If nvidia-smi failed, try a more basic approach with lspci
     if (!gpu_info->has_cuda_gpu) {
         fp = popen("lspci | grep -i nvidia 2>/dev/null", "r");
         if (fp) {
             char buffer[512];
             if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                 buffer[strcspn(buffer, "\n")] = 0; // Remove newline
                 gpu_info->has_cuda_gpu = true;
                 
                 // Extract just the device name part
                 char* name_start = strstr(buffer, "NVIDIA");
                 if (name_start) {
                     strncpy(gpu_info->gpu_name, name_start, sizeof(gpu_info->gpu_name) - 1);
                 } else {
                     strncpy(gpu_info->gpu_name, buffer, sizeof(gpu_info->gpu_name) - 1);
                 }
             }
             pclose(fp);
         }
     }
 #endif
 
     // If we detected a NVIDIA GPU but couldn't determine compute capability,
     // provide default minimum values
     if (gpu_info->has_cuda_gpu && gpu_info->compute_capability_major < 0) {
         gpu_info->compute_capability_major = 1;
         gpu_info->compute_capability_minor = 0;
     }
 }
 
 /**
  * Estimate memory bandwidth
  */
 double estimate_memory_bandwidth(const HardwareProfile* hw) {
     // Naive bandwidth test - allocate a large array and time access
     const size_t buffer_size = 1024 * 1024 * 128; // 128 MB
     const int iterations = 10;
     
     // First check if we have enough RAM
     if (hw->memory_info.total_ram_mb < 256) {
         return -1.0; // Not enough memory to run test
     }
     
     double* buffer = (double*)malloc(buffer_size);
     if (!buffer) {
         return -1.0; // Failed to allocate memory
     }
     
     // Initialize buffer
     for (size_t i = 0; i < buffer_size / sizeof(double); i++) {
         buffer[i] = (double)i;
     }
     
     // Measure read bandwidth
     clock_t start = clock();
     
     // Perform reads
     volatile double sum = 0.0;
     for (int iter = 0; iter < iterations; iter++) {
         for (size_t i = 0; i < buffer_size / sizeof(double); i++) {
             sum += buffer[i];
         }
     }
     
     clock_t end = clock();
     double elapsed_seconds = (double)(end - start) / CLOCKS_PER_SEC;
     
     // Calculate bandwidth in MB/s
     double bytes_processed = (double)buffer_size * iterations;
     double bandwidth_mbps = bytes_processed / (1024 * 1024) / elapsed_seconds;
     
     free(buffer);
     return bandwidth_mbps;
 }
 
 /**
  * Print a summary of detected hardware
  */
 void print_hardware_profile(const HardwareProfile* hw) {
     printf("====================================================\n");
     printf("            HARDWARE PROFILE SUMMARY                \n");
     printf("====================================================\n\n");
     
     printf("=== CPU INFORMATION ===\n");
     printf("Physical cores: %d\n", hw->cpu_cores.physical_cores);
     printf("Logical cores:  %d\n", hw->cpu_cores.logical_cores);
     
     printf("\n=== CPU INSTRUCTION SETS ===\n");
     printf("MMX:      %s\n", hw->cpu_features.mmx ? "Yes" : "No");
     printf("SSE:      %s\n", hw->cpu_features.sse ? "Yes" : "No");
     printf("SSE2:     %s\n", hw->cpu_features.sse2 ? "Yes" : "No");
     printf("SSE3:     %s\n", hw->cpu_features.sse3 ? "Yes" : "No");
     printf("SSSE3:    %s\n", hw->cpu_features.ssse3 ? "Yes" : "No");
     printf("SSE4.1:   %s\n", hw->cpu_features.sse4_1 ? "Yes" : "No");
     printf("SSE4.2:   %s\n", hw->cpu_features.sse4_2 ? "Yes" : "No");
     printf("AVX:      %s\n", hw->cpu_features.avx ? "Yes" : "No");
     printf("AVX2:     %s\n", hw->cpu_features.avx2 ? "Yes" : "No");
     printf("AVX-512F: %s\n", hw->cpu_features.avx512f ? "Yes" : "No");
     printf("FMA:      %s\n", hw->cpu_features.fma ? "Yes" : "No");
     printf("NEON:     %s\n", hw->cpu_features.neon ? "Yes" : "No");
     printf("SVE:      %s\n", hw->cpu_features.sve ? "Yes" : "No");
     
     printf("\n=== CACHE INFORMATION ===\n");
     if (hw->cache_info.l1_data_cache_size_kb > 0) {
         printf("L1 Data:       %d KB\n", hw->cache_info.l1_data_cache_size_kb);
     } else {
         printf("L1 Data:       Unknown\n");
     }
     
     if (hw->cache_info.l1_instruction_cache_size_kb > 0) {
         printf("L1 Instruction: %d KB\n", hw->cache_info.l1_instruction_cache_size_kb);
     } else {
         printf("L1 Instruction: Unknown\n");
     }
     
     if (hw->cache_info.l2_cache_size_kb > 0) {
         if (hw->cache_info.l2_cache_size_kb >= 1024) {
             printf("L2:            %.1f MB\n", hw->cache_info.l2_cache_size_kb / 1024.0);
         } else {
             printf("L2:            %d KB\n", hw->cache_info.l2_cache_size_kb);
         }
     } else {
         printf("L2:            Unknown\n");
     }
     
     if (hw->cache_info.l3_cache_size_kb > 0) {
         if (hw->cache_info.l3_cache_size_kb >= 1024) {
             printf("L3:            %.1f MB\n", hw->cache_info.l3_cache_size_kb / 1024.0);
         } else {
             printf("L3:            %d KB\n", hw->cache_info.l3_cache_size_kb);
         }
     } else {
         printf("L3:            Unknown\n");
     }
     
     if (hw->cache_info.cache_line_size_bytes > 0) {
         printf("Cache Line:     %d bytes\n", hw->cache_info.cache_line_size_bytes);
     } else {
         printf("Cache Line:     Unknown\n");
     }
     
     printf("\n=== MEMORY INFORMATION ===\n");
     printf("Total RAM:     %ld MB (%.1f GB)\n", hw->memory_info.total_ram_mb, 
            hw->memory_info.total_ram_mb / 1024.0);
     
     printf("\n=== GPU INFORMATION ===\n");
     if (hw->gpu_info.has_cuda_gpu) {
         printf("CUDA GPU:      Yes\n");
         printf("GPU Name:      %s\n", hw->gpu_info.gpu_name);
         
         if (hw->gpu_info.compute_capability_major > 0) {
             printf("Compute:       %d.%d\n", 
                    hw->gpu_info.compute_capability_major,
                    hw->gpu_info.compute_capability_minor);
         } else {
             printf("Compute:       Unknown\n");
         }
     } else {
         printf("CUDA GPU:      No\n");
     }
     
     printf("\n=== OPTIMIZATION RECOMMENDATIONS ===\n");
     // CPU instruction set recommendations
     printf("Vectorization: ");
     if (hw->cpu_features.avx512f) {
         printf("Use AVX-512\n");
     } else if (hw->cpu_features.avx2) {
         printf("Use AVX2\n");
     } else if (hw->cpu_features.avx) {
         printf("Use AVX\n");
     } else if (hw->cpu_features.sse4_2) {
         printf("Use SSE4.2\n");
     } else if (hw->cpu_features.sse2) {
         printf("Use SSE2\n");
     } else if (hw->cpu_features.neon) {
         printf("Use NEON\n");
     } else {
         printf("Use scalar code\n");
     }
     
     // Threading recommendations
     printf("Threading:     ");
     if (hw->cpu_cores.logical_cores >= 16) {
         printf("Use %d threads for compute-bound tasks\n", hw->cpu_cores.logical_cores);
         printf("              Use %d threads for memory-bound tasks\n", hw->cpu_cores.physical_cores);
     } else if (hw->cpu_cores.logical_cores >= 4) {
         printf("Use thread pool with %d threads\n", hw->cpu_cores.logical_cores);
     } else {
         printf("Limited benefit, focus on vectorization\n");
     }
     
     // Cache optimization
     printf("Memory:        ");
     if (hw->cache_info.cache_line_size_bytes > 0) {
         printf("Align data to %d-byte boundaries\n", 
                hw->cache_info.cache_line_size_bytes);
     } else {
         printf("Use 64-byte alignment (default cache line)\n");
     }
     
     if (hw->cache_info.l1_data_cache_size_kb > 0) {
         printf("              Use cache blocking ~%d KB for L1\n", 
                hw->cache_info.l1_data_cache_size_kb / 2);
     }
     
     // GPU recommendations
     if (hw->gpu_info.has_cuda_gpu) {
         printf("GPU:           Consider offloading compute-intensive tasks to GPU\n");
         if (hw->gpu_info.compute_capability_major >= 6) {
             printf("              Use Tensor Cores for matrix operations (if supported)\n");
         }
     }
     
     printf("====================================================\n");
 }