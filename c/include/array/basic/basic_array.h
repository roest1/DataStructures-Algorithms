#ifndef BASIC_ARRAY_H
#define BASIC_ARRAY_H

#include <stddef.h> // For size_t

#define MAX_CAPACITY 100

typedef struct {
    int array[MAX_CAPACITY]; // array 
    size_t length;   // Number of elements currently stored
} StaticIntArray;

/* Create a new, empty IntArray */
StaticIntArray NewStaticIntArray();

/* Clear All */
void ClearStaticIntArray(StaticIntArray *a);

/* Insert value v at index i */
int InsertStaticIntArray(StaticIntArray *a, size_t i, int v);

/* Delete value at index i */
int DeleteStaticIntArray(StaticIntArray *a, size_t i);

/* Get pointer to value *v from index i */
int GetStaticIntArray(const StaticIntArray *a, size_t i, int *v);

/* Flatten arrays a and b into a*/
int FlattenStaticIntArray(StaticIntArray *a, StaticIntArray *b);

/* Print the contents of the array */
void PrintStaticIntArray(const StaticIntArray *a);

#endif