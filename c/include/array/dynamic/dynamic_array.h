#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h> // For size_t

typedef struct {
    int *parray;     // Pointer to array data
    size_t length;   // Number of elements currently stored
    size_t capacity; // Total elements that can be stored
} DynamicIntArray;

/* Create a new, empty IntArray */
DynamicIntArray NewDynamicIntArray();

/* Free the memory used by an DynamicIntArray */
void FreeDynamicIntArray(DynamicIntArray *a);

/* Makes sure enought memory is allocated to store n ints */
int AllocateDynamicIntArray(DynamicIntArray *a, size_t n);

/* Trims allocated memory to only the needed amount */
int DeallocateDynamicIntArray(DynamicIntArray *a);

/* Insert value v at index i */
int InsertDynamicIntArray(DynamicIntArray *a, size_t i, int v);

/* Delete value at index i */
int DeleteDynamicIntArray(DynamicIntArray *a, size_t i);

/* Get pointer to value *v from index i */
int GetDynamicIntArray(const DynamicIntArray *a, size_t i, int *v);

/* Flatten arrays a and b into a*/
int FlattenDynamicIntArray(DynamicIntArray *a, DynamicIntArray *b);

/* Print the contents of the array */
void PrintDynamicIntArray(const DynamicIntArray *a);

#endif