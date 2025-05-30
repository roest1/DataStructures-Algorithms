

 #include "../include/array/array.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include <math.h>
 
 /**
  * Helper function to determine the size of a type
  */
 size_t array_sizeof_type(Type type) {
     switch (type) {
         case INT:
             return sizeof(int);
         case FLOAT:
             return sizeof(float);
         case DOUBLE:
             return sizeof(double);
         case CHAR:
             return sizeof(char);
         case STRING:
             return sizeof(char*);
         case BOOL:
             return sizeof(bool);
         case ARRAY:
             return sizeof(Array*);
         default:
             fprintf(stderr, "Error: Unknown type\n");
             return 0;
     }
 }
 
 /**
  * Helper function to create a new array structure
  */
 Array* array_create(size_t size, Type type, bool is_dynamic) {
     Array* array = (Array*)malloc(sizeof(Array));
     if (!array) {
         fprintf(stderr, "Error: Failed to allocate memory for Array\n");
         return NULL;
     }
 
     // Initialize array properties
     array->type = type;
     array->sizeof_type = array_sizeof_type(type);
     if (array->sizeof_type == 0) {
         free(array);
         return NULL;
     }
     
     array->num_dimensions = 1;  // Starting with 1D arrays
     array->count = size;
     
     // For dynamic arrays, allocate more capacity than needed
     array->capacity = is_dynamic ? (size > 0 ? size * 2 : 8) : size;
     array->is_dynamic = is_dynamic;
     
     // Allocate memory for shape
     array->shape = (size_t*)malloc(sizeof(size_t) * array->num_dimensions);
     if (!array->shape) {
         fprintf(stderr, "Error: Failed to allocate memory for shape\n");
         free(array);
         return NULL;
     }
     array->shape[0] = size;
     
     // Allocate memory for array data
     array->parray = array_allocate(array);
     if (!array->parray) {
         free(array->shape);
         free(array);
         return NULL;
     }
     
     return array;
 }
 
 /**
  * Helper function to allocate memory for array data
  */
 void* array_allocate(Array* array) {
     if (!array) return NULL;
     
     void* data = malloc(array->capacity * array->sizeof_type);
     if (!data) {
         fprintf(stderr, "Error: Failed to allocate memory for array data\n");
         return NULL;
     }
     
     return data;
 }
 
 /**
  * Create an empty array with uninitialized values
  */
 Array* array_empty(size_t size, Type type, bool is_dynamic) {
     return array_create(size, type, is_dynamic);
 }
 
 /**
  * Create an array filled with zeros
  */
 Array* array_zeros(size_t size, Type type, bool is_dynamic) {
     Array* array = array_create(size, type, is_dynamic);
     if (!array) return NULL;
     
     // Initialize all bytes to zero
     memset(array->parray, 0, array->count * array->sizeof_type);
     
     return array;
 }
 
 /**
  * Create an array filled with ones
  */
 Array* array_ones(size_t size, Type type, bool is_dynamic) {
     Array* array = array_create(size, type, is_dynamic);
     if (!array) return NULL;
 
     // Initialize all elements to 1 based on type
     switch (type) {
         case INT: {
             int one = 1;
             for (size_t i = 0; i < size; i++) {
                 memcpy((char*)array->parray + i * array->sizeof_type, &one, array->sizeof_type);
             }
             break;
         }
         case FLOAT: {
             float one = 1.0f;
             for (size_t i = 0; i < size; i++) {
                 memcpy((char*)array->parray + i * array->sizeof_type, &one, array->sizeof_type);
             }
             break;
         }
         case DOUBLE: {
             double one = 1.0;
             for (size_t i = 0; i < size; i++) {
                 memcpy((char*)array->parray + i * array->sizeof_type, &one, array->sizeof_type);
             }
             break;
         }
         case CHAR: {
             char one = '1';
             for (size_t i = 0; i < size; i++) {
                 memcpy((char*)array->parray + i * array->sizeof_type, &one, array->sizeof_type);
             }
             break;
         }
         case BOOL: {
             bool one = true;
             for (size_t i = 0; i < size; i++) {
                 memcpy((char*)array->parray + i * array->sizeof_type, &one, array->sizeof_type);
             }
             break;
         }
         case STRING: {
             // For strings, we need to allocate memory for each string
             char* one_str = strdup("1");
             if (!one_str) {
                 fprintf(stderr, "Error: Failed to allocate memory for string\n");
                 array_free(array);
                 return NULL;
             }
             
             for (size_t i = 0; i < size; i++) {
                 char* str_copy = strdup(one_str);
                 if (!str_copy) {
                     fprintf(stderr, "Error: Failed to allocate memory for string copy\n");
                     // Clean up previously allocated strings
                     for (size_t j = 0; j < i; j++) {
                         char** str_ptr = (char**)array->parray + j;
                         free(*str_ptr);
                     }
                     free(one_str);
                     array_free(array);
                     return NULL;
                 }
                 memcpy((char*)array->parray + i * array->sizeof_type, &str_copy, array->sizeof_type);
             }
             free(one_str);
             break;
         }
         case ARRAY:
             // Arrays of arrays not supported for this function
             fprintf(stderr, "Error: Arrays of arrays not supported for ones()\n");
             array_free(array);
             return NULL;
         default:
             fprintf(stderr, "Error: Unknown type\n");
             array_free(array);
             return NULL;
     }
     
     return array;
 }
 
 /**
  * Create an array filled with a specific value
  */
 Array* array_full(size_t size, Type type, void* value, bool is_dynamic) {
     if (!value) {
         fprintf(stderr, "Error: Value pointer cannot be NULL\n");
         return NULL;
     }
 
     Array* array = array_create(size, type, is_dynamic);
     if (!array) return NULL;
 
     // Fill array with the provided value
     if (type == STRING) {
         // For strings, we need special handling to duplicate each string
         char* str_value = *(char**)value;
         
         for (size_t i = 0; i < size; i++) {
             char* str_copy = strdup(str_value);
             if (!str_copy) {
                 fprintf(stderr, "Error: Failed to allocate memory for string copy\n");
                 // Clean up previously allocated strings
                 for (size_t j = 0; j < i; j++) {
                     char** str_ptr = (char**)array->parray + j;
                     free(*str_ptr);
                 }
                 array_free(array);
                 return NULL;
             }
             memcpy((char*)array->parray + i * array->sizeof_type, &str_copy, array->sizeof_type);
         }
     } else {
         // For other types, simply copy the value to each element
         for (size_t i = 0; i < size; i++) {
             memcpy((char*)array->parray + i * array->sizeof_type, value, array->sizeof_type);
         }
     }
     
     return array;
 }
 
 /**
  * Create an array with evenly spaced values
  */
 Array* array_arange(double start, double stop, double step, Type type, bool is_dynamic) {
     if (step == 0) {
         fprintf(stderr, "Error: Step cannot be zero\n");
         return NULL;
     }
     
     if ((step > 0 && start >= stop) || (step < 0 && start <= stop)) {
         fprintf(stderr, "Error: Invalid range parameters\n");
         return NULL;
     }
     
     // Calculate the number of elements
     size_t size = (size_t)ceil(fabs((stop - start) / step));
     if (size == 0) return NULL;  // Empty array
     
     Array* array = array_create(size, type, is_dynamic);
     if (!array) return NULL;
     
     // Fill array with the sequence
     switch (type) {
         case INT: {
             for (size_t i = 0; i < size; i++) {
                 int value = (int)(start + i * step);
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case FLOAT: {
             for (size_t i = 0; i < size; i++) {
                 float value = (float)(start + i * step);
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case DOUBLE: {
             for (size_t i = 0; i < size; i++) {
                 double value = start + i * step;
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case CHAR: {
             for (size_t i = 0; i < size; i++) {
                 char value = (char)(start + i * step);
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case BOOL:
         case STRING:
         case ARRAY:
             // These types don't make sense for arange
             fprintf(stderr, "Error: Type not supported for arange\n");
             array_free(array);
             return NULL;
         default:
             fprintf(stderr, "Error: Unknown type\n");
             array_free(array);
             return NULL;
     }
     
     return array;
 }
 
 /**
  * Create an array with evenly spaced values over a specified interval
  */
 Array* array_linspace(double start, double stop, size_t num_points, Type type, bool is_dynamic) {
     if (num_points < 2) {
         fprintf(stderr, "Error: Number of points must be at least 2\n");
         return NULL;
     }
     
     Array* array = array_create(num_points, type, is_dynamic);
     if (!array) return NULL;
     
     // Calculate step size
     double step = (stop - start) / (num_points - 1);
     
     // Fill array with the sequence
     switch (type) {
         case INT: {
             for (size_t i = 0; i < num_points; i++) {
                 int value = (int)(start + i * step);
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case FLOAT: {
             for (size_t i = 0; i < num_points; i++) {
                 float value = (float)(start + i * step);
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case DOUBLE: {
             for (size_t i = 0; i < num_points; i++) {
                 double value = start + i * step;
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case CHAR: {
             for (size_t i = 0; i < num_points; i++) {
                 char value = (char)(start + i * step);
                 memcpy((char*)array->parray + i * array->sizeof_type, &value, array->sizeof_type);
             }
             break;
         }
         case BOOL:
         case STRING:
         case ARRAY:
             // These types don't make sense for linspace
             fprintf(stderr, "Error: Type not supported for linspace\n");
             array_free(array);
             return NULL;
         default:
             fprintf(stderr, "Error: Unknown type\n");
             array_free(array);
             return NULL;
     }
     
     // Ensure the last element is exactly the stop value
     switch (type) {
         case INT: {
             int value = (int)stop;
             memcpy((char*)array->parray + (num_points - 1) * array->sizeof_type, &value, array->sizeof_type);
             break;
         }
         case FLOAT: {
             float value = (float)stop;
             memcpy((char*)array->parray + (num_points - 1) * array->sizeof_type, &value, array->sizeof_type);
             break;
         }
         case DOUBLE: {
             memcpy((char*)array->parray + (num_points - 1) * array->sizeof_type, &stop, array->sizeof_type);
             break;
         }
         case CHAR: {
             char value = (char)stop;
             memcpy((char*)array->parray + (num_points - 1) * array->sizeof_type, &value, array->sizeof_type);
             break;
         }
         default:
             break;
     }
     
     return array;
 }
 
 /**
  * Create a copy of an array
  */
 Array* array_copy(Array* source, bool is_dynamic) {
     if (!source) {
         fprintf(stderr, "Error: Source array cannot be NULL\n");
         return NULL;
     }
     
     // Create a new array with the same properties
     Array* array = array_create(source->count, source->type, is_dynamic);
     if (!array) return NULL;
     
     // Copy data from source array
     if (source->type == STRING) {
         // For string arrays, we need to duplicate each string
         for (size_t i = 0; i < source->count; i++) {
             char** src_str_ptr = (char**)source->parray + i;
             char* str_copy = strdup(*src_str_ptr);
             if (!str_copy) {
                 fprintf(stderr, "Error: Failed to allocate memory for string copy\n");
                 // Clean up previously allocated strings
                 for (size_t j = 0; j < i; j++) {
                     char** str_ptr = (char**)array->parray + j;
                     free(*str_ptr);
                 }
                 array_free(array);
                 return NULL;
             }
             memcpy((char*)array->parray + i * array->sizeof_type, &str_copy, array->sizeof_type);
         }
     } else {
         // For other types, just copy the memory
         memcpy(array->parray, source->parray, source->count * source->sizeof_type);
     }
     
     return array;
 }
 
 /**
  * Free memory allocated for an array
  */
 void array_free(Array* array) {
     if (!array) return;
     
     // Free string data if this is a string array
     if (array->type == STRING && array->parray) {
         for (size_t i = 0; i < array->count; i++) {
             char** str_ptr = (char**)array->parray + i;
             free(*str_ptr);
         }
     }
     
     // Free array data
     free(array->parray);
     
     // Free shape array
     free(array->shape);
     
     // Free array struct itself
     free(array);
 }