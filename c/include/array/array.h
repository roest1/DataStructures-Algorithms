
/*
for Array library in C (mimic numpy and pandas)

1. Support any type
2. Support any number of dimensions
3. Support random types (ie: ['a', 1, 2.3, "aye", ""])
4. Static and dynamic 
5. Slice
6. Fancy index (ie (python): a[1:2:10])
7. Axis operations
8. Reshape, flatten, ravel
9. transpose 2d array
10. copy/view
11. print
12. math

TODO: 1D first

For static and dynamic implementations
-Create
-Resize
-Get
-Set
-Slice
-Fancy Index
-Copy/View
-Print
-Math

multi dimensionals will just call these 1d functions because all arrays are 1d contiguous in memory

path: c/include/array/array.h
*/

 #ifndef ARRAY_H
 #define ARRAY_H
 
 #include <stddef.h>
 #include <stdbool.h>
 #include <stdlib.h>
 
 /**
  * @brief Enum representing the supported data types for array elements
  */
 typedef enum {
     INT,
     FLOAT,
     DOUBLE,
     CHAR,
     STRING,
     BOOL,
     ARRAY
 } Type;
 
 /**
  * @brief Struct representing an array with type information
  */
 typedef struct Array {
     void *parray;           // pointer to array of data
     Type type;              // type of data
     size_t sizeof_type;     // size of each element in bytes
     size_t *shape;          // int[] for size of each dimension
     size_t num_dimensions;  // number of dimensions
     size_t count;           // total number of elements
     size_t capacity;        // total number of elements that can be stored
     bool is_dynamic;        // whether the array is dynamically resizable
 } Array;
 
 /**
  * @brief Create an empty array with uninitialized values
  * 
  * @param size Number of elements in the array
  * @param type Data type of elements
  * @param is_dynamic Whether the array can be resized
  * @return Array* Pointer to the newly created array
  */
 Array* array_empty(size_t size, Type type, bool is_dynamic);
 
 /**
  * @brief Create an array filled with zeros
  * 
  * @param size Number of elements in the array
  * @param type Data type of elements
  * @param is_dynamic Whether the array can be resized
  * @return Array* Pointer to the newly created array
  */
 Array* array_zeros(size_t size, Type type, bool is_dynamic);
 
 /**
  * @brief Create an array filled with ones
  * 
  * @param size Number of elements in the array
  * @param type Data type of elements
  * @param is_dynamic Whether the array can be resized
  * @return Array* Pointer to the newly created array
  */
 Array* array_ones(size_t size, Type type, bool is_dynamic);
 
 /**
  * @brief Create an array filled with a specific value
  * 
  * @param size Number of elements in the array
  * @param type Data type of elements
  * @param value Pointer to the value to fill the array with
  * @param is_dynamic Whether the array can be resized
  * @return Array* Pointer to the newly created array
  */
 Array* array_full(size_t size, Type type, void* value, bool is_dynamic);
 
 /**
  * @brief Create an array with evenly spaced values
  * 
  * @param start Start value
  * @param stop Stop value (exclusive)
  * @param step Step size
  * @param type Data type of elements
  * @param is_dynamic Whether the array can be resized
  * @return Array* Pointer to the newly created array
  */
 Array* array_arange(double start, double stop, double step, Type type, bool is_dynamic);
 
 /**
  * @brief Create an array with evenly spaced values over a specified interval
  * 
  * @param start Start value
  * @param stop Stop value (inclusive)
  * @param num_points Number of points
  * @param type Data type of elements
  * @param is_dynamic Whether the array can be resized
  * @return Array* Pointer to the newly created array
  */
 Array* array_linspace(double start, double stop, size_t num_points, Type type, bool is_dynamic);
 
 /**
  * @brief Create a copy of an array
  * 
  * @param array Array to copy
  * @param is_dynamic Whether the new array can be resized
  * @return Array* Pointer to the newly created array
  */
 Array* array_copy(Array* array, bool is_dynamic);
 
 /**
  * @brief Free memory allocated for an array
  * 
  * @param array Array to free
  */
 void array_free(Array* array);
 
 /**
  * @brief Helper function to get the size of a specified type
  * 
  * @param type Data type
  * @return size_t Size of the type in bytes
  */
 size_t array_sizeof_type(Type type);
 
 /**
  * @brief Helper function to create a new array structure
  * 
  * @param size Number of elements
  * @param type Data type
  * @param is_dynamic Whether the array can be resized
  * @return Array* Pointer to the newly created array structure
  */
 Array* array_create(size_t size, Type type, bool is_dynamic);
 
 /**
  * @brief Helper function to allocate memory for array data
  * 
  * @param array Array structure to allocate memory for
  * @return void* Pointer to allocated memory
  */
 void* array_allocate(Array* array);
 
 #endif // ARRAY_H