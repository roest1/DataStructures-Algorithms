#ifndef RUNTIME_DISPATCH_H
#define RUNTIME_DISPATCH_H

#include "hardware/hardware_detection.h"

// Function pointer types
typedef void (*ArrayAddFn)(const float* a, const float* b, float* c, int n);

// Initialize runtime dispatch based on hardware profile
void init_runtime_dispatch(const HardwareProfile* hw);

// Get best function for array addition
ArrayAddFn get_array_add_function(void);

#endif // RUNTIME_DISPATCH_H
