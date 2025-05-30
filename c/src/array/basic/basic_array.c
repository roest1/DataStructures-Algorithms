#include "array/basic/basic_array.h"
#include <stdio.h>
#include <stdlib.h>

StaticIntArray NewStaticIntArray() 
{ // Initialize with default parameters
    StaticIntArray arr;
    arr.length = 0;
    return arr;
}

void ClearStaticIntArray(StaticIntArray *a)
{
    a->length = 0;
}

int InsertStaticIntArray(StaticIntArray *a, size_t i, int v) 
{
    if (i > a->length) {
        printf("[InsertIntArray] Insertion failed: invalid index %zu\n", i);
        return 0;
    }
    if (a->length >= MAX_CAPACITY) {
        printf("[InsertStaticIntArray] Insert failed becaue array is max size\n");
        return 0;
    }

    /*
    make room for insert

    Insert at end happens in O(1)
    Insert in middle happens in O(n/2)
    Insert at beginning happens in O(n)
    */ 
    if (i < a->length) {
        for (int j = a->length; j > i; j++) {
            a->array[j] = a->array[j - 1];
        }
    }

    a->array[i] = v;
    a->length++;
    return 1; 
}

int DeleteStaticIntArray(StaticIntArray *a, size_t i) 
{
    if (i >= a->length) {
        printf("[DeleteStaticIntArray] Deletion failed: invalid index %zu\n", i);
        return 0;
    }

    /* Shift latter elements left to fill the index i */
    for (size_t j = i; j < a->length - 1; j++) {
        a->array[j] = a->array[j + 1];
    }

    a->length--; 
    return 1; 
}

int GetStaticIntArray(const StaticIntArray *a, size_t i, int *v) 
{
    if (i >= a->length) {
        printf("[GetStaticIntArray] Access failed: invalid index %zu\n", i);
        return 0;
    }

    *v = a->array[i];
    return 1;
}

int FlattenStaticIntArray(StaticIntArray *a, StaticIntArray *b) 
{
    if (a->length + b->length > MAX_CAPACITY) {
        printf("[FlattenStaticIntArray] Failed: combined arrays exceed max capacity\n");
        return 0;
    }

    for (size_t i = 0; i < b->length; i++) {
        a->array[a->length + i] = b->array[i];
    }
    a->length += b->length;
    return 1;
}

void PrintStaticIntArray(const StaticIntArray *a) 
{
    printf("[ ");
    for (size_t i = 0; i < a->length; i++) {
        printf("%d ", a->array[i]);
    }
    printf("]\n");
}
