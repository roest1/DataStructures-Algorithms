#ifndef MULTI_DIMENSIONAL_ARRAY_H
#define MULTI_DIMENSIONAL_ARRAY_H

/* This multi-dimensional array is dynamic */
#include <stddef.h> // for size_t

typedef struct {
    int *parray;
    size_t *num_dims; // number of dimensions
    size_t dim_sizes; // size of each dimension

}

/* Eventuall plan to support 

-slicing
-fancy indexing (non-contiguous slices)
-masked arrays
-broadcasting
-axis operations
-transpose
-flatten/reshape
-split/stack/concat
-matrix math
-copy vs view
-memory ownership (flags if array owns buffer or not)
*/


#endif