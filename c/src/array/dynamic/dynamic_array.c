#include "array/dynamic/dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>

DynamicIntArray NewDynamicIntArray() 
{ // Initialize with default parameters
    DynamicIntArray arr;
    arr.parray = NULL;
    arr.length = 0;
    arr.capacity = 0;
    return arr;
}

void FreeDynamicIntArray(DynamicIntArray *a) 
{ // Deconstructor
    free(a->parray); // remove off heap
    a->parray = NULL; // ensure no danglin pointer
    a->length = 0;
    a->capacity = 0;
}

int AllocateDynamicIntArray(DynamicIntArray *a, size_t n) 
{ // allocates enough space for n more ints in this array
    if (n <= a->capacity) return 1; // already enough space for this number of elements

    int *new_parray = realloc(a->parray, n * sizeof(int));
    if (!new_parray) {
        printf("[AllocateDynamicIntArray] Memory allocation failed.\n");
        return 0;
    }
    a->parray = new_parray;
    a->capacity = n;
    return 1;
}

int DeallocateDynamicIntArray(DynamicIntArray *a)
{
    if (a->length == 0) {
        FreeDynamicIntArray(a); // array is empty so just delete it
    }

    AllocateDynamicIntArray(a, a->length);
    return 1;
}

int InsertDynamicIntArray(DynamicIntArray *a, size_t i, int v) 
{
    if (i > a->length) {
        printf("[InsertDynamicIntArray] Insertion failed: invalid index %zu\n", i);
        return 0;
    }

    // Allocate more space for the array 
    if (a->length >= a->capacity) {

        /*
        new_capacity = old_capacity + 1 leads to realloc() being called every time if capacity
        is not already properly allocated

        Could switch to old_capacity * 2 to prevent this behavior
        */
        if (!AllocateDynamicIntArray(a, a->capacity + 1)) return 0; // memory fail 
    }
    /*
    make room for insert

    Insert at end happens in O(1)
    Insert in middle happens in O(n/2)
    Insert at beginning happens in O(n)
    */ 
    if (i < a->length) {
        for (size_t j = a->length; j > i; j++) {
            a->parray[j] = a->parray[j - 1];
        }
    }

    a->parray[i] = v;
    a->length++;
    return 1; 
}

int DeleteDynamicIntArray(DynamicIntArray *a, size_t i) 
{
    if (i >= a->length) {
        printf("[DeleteInArray] Deletion failed: invalid index %zu\n", i);
        return 0;
    }

    /* Shift latter elements left to fill the index i */
    for (size_t j = i; j < a->length - 1; j++) {
        a->parray[j] = a->parray[j + 1];
    }

    a->length--; 
    return 1; 
}

int GetDynamicIntArray(const DynamicIntArray *a, size_t i, int *v) 
{
    if (i >= a->length) {
        printf("[GetDynamicIntArray] Access failed: invalid index %zu\n", i);
        return 0;
    }

    *v = a->parray[i];
    return 1;
}

int FlattenDynamicIntArray(DynamicIntArray *a, DynamicIntArray *b) 
{
    if (!AllocateDynamicIntArray(a, a->length + b->length)) return 0;

    for (size_t i = 0; i < b->length; i++) {
        a->parray[a->length + i] = b->parray[i];
    }
    a->length += b->length;
    return 1;
}

void PrintDynamicIntArray(const DynamicIntArray *a) 
{
    printf("[ ");
    for (size_t i = 0; i < a->length; i++) {
        printf("%d ", a->parray[i]);
    }
    printf("]\n");
}
