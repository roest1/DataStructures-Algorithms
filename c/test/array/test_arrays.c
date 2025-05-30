// #include "array/basic/basic_array.h"
// #include "array/dynamic/dynamic_array.h"
// #include <stdio.h>
// #include <stdlib.h>

/*
#define ASSERT(cond, msg) \
    do { \
        if (cond) { \
            printf("[PASS] %s\n", msg); \
        } else { \
            printf("[FAIL] %s\n", msg); \
        } \
    } while(0)
*/
// void TestStaticIntArray() {
//     printf("\n--- Testing StaticIntArray ---\n");

//     StaticIntArray a = NewStaticIntArray();
//     StaticIntArray b = NewStaticIntArray();
//     int value;

//     // Insert elements
//     ASSERT(InsertStaticIntArray(&a, 0, 10), "Insert 10 at index 0");
//     ASSERT(InsertStaticIntArray(&a, 1, 20), "Insert 20 at index 1");
//     ASSERT(InsertStaticIntArray(&a, 2, 30), "Insert 30 at index 2");
//     PrintStaticIntArray(&a);

//     // Get element
//     ASSERT(GetStaticIntArray(&a, 1, &value) && value == 20, "Get element at index 1 == 20");

//     // Delete element
//     ASSERT(DeleteStaticIntArray(&a, 1), "Delete element at index 1");
//     ASSERT(a.length == 2, "Length after deletion == 2");
//     PrintStaticIntArray(&a);

//     // Flatten
//     ASSERT(InsertStaticIntArray(&b, 0, 40), "Insert 40 into b");
//     ASSERT(InsertStaticIntArray(&b, 1, 50), "Insert 50 into b");
//     ASSERT(FlattenStaticIntArray(&a, &b), "Flatten b into a");
//     ASSERT(a.length == 4, "Length after flatten == 4");
//     PrintStaticIntArray(&a);

//     // Clear array
//     ClearStaticIntArray(&a);
//     ASSERT(a.length == 0, "Clear array resets length to 0");
// }

// void TestDynamicIntArray() {
//     printf("\n--- Testing DynamicIntArray ---\n");

//     DynamicIntArray a = NewDynamicIntArray();
//     DynamicIntArray b = NewDynamicIntArray();
//     int value;

//     // Insert elements
//     ASSERT(InsertDynamicIntArray(&a, 0, 100), "Insert 100 at index 0");
//     ASSERT(InsertDynamicIntArray(&a, 1, 200), "Insert 200 at index 1");
//     ASSERT(InsertDynamicIntArray(&a, 2, 300), "Insert 300 at index 2");
//     PrintDynamicIntArray(&a);

//     // Get element
//     ASSERT(GetDynamicIntArray(&a, 1, &value) && value == 200, "Get element at index 1 == 200");

//     // Delete element
//     ASSERT(DeleteDynamicIntArray(&a, 1), "Delete element at index 1");
//     ASSERT(a.length == 2, "Length after deletion == 2");
//     PrintDynamicIntArray(&a);

//     // Flatten
//     ASSERT(InsertDynamicIntArray(&b, 0, 400), "Insert 400 into b");
//     ASSERT(InsertDynamicIntArray(&b, 1, 500), "Insert 500 into b");
//     ASSERT(FlattenDynamicIntArray(&a, &b), "Flatten b into a");
//     ASSERT(a.length == 4, "Length after flatten == 4");
//     PrintDynamicIntArray(&a);

//     // Free memory
//     FreeDynamicIntArray(&a);
//     FreeDynamicIntArray(&b);
// }

// int main() {
//     TestStaticIntArray();
//     TestDynamicIntArray();
//     return 0;
// }

 #include "../../include/array/array.h"
 #include <stdio.h>
 #include <string.h>
 
 /**
  * Helper function to print an integer array
  */
 void print_int_array(Array* array) {
     if (!array || array->type != INT) {
         printf("Not an integer array\n");
         return;
     }
     
     printf("Int Array [");
     for (size_t i = 0; i < array->count; i++) {
         int value;
         memcpy(&value, (char*)array->parray + i * array->sizeof_type, array->sizeof_type);
         printf("%d", value);
         if (i < array->count - 1) printf(", ");
     }
     printf("]\n");
 }
 
 /**
  * Helper function to print a float array
  */
 void print_float_array(Array* array) {
     if (!array || array->type != FLOAT) {
         printf("Not a float array\n");
         return;
     }
     
     printf("Float Array [");
     for (size_t i = 0; i < array->count; i++) {
         float value;
         memcpy(&value, (char*)array->parray + i * array->sizeof_type, array->sizeof_type);
         printf("%.2f", value);
         if (i < array->count - 1) printf(", ");
     }
     printf("]\n");
 }
 
 /**
  * Helper function to print a double array
  */
 void print_double_array(Array* array) {
     if (!array || array->type != DOUBLE) {
         printf("Not a double array\n");
         return;
     }
     
     printf("Double Array [");
     for (size_t i = 0; i < array->count; i++) {
         double value;
         memcpy(&value, (char*)array->parray + i * array->sizeof_type, array->sizeof_type);
         printf("%.2f", value);
         if (i < array->count - 1) printf(", ");
     }
     printf("]\n");
 }
 
 /**
  * Helper function to print a char array
  */
 void print_char_array(Array* array) {
     if (!array || array->type != CHAR) {
         printf("Not a char array\n");
         return;
     }
     
     printf("Char Array [");
     for (size_t i = 0; i < array->count; i++) {
         char value;
         memcpy(&value, (char*)array->parray + i * array->sizeof_type, array->sizeof_type);
         printf("'%c'", value);
         if (i < array->count - 1) printf(", ");
     }
     printf("]\n");
 }
 
 /**
  * Helper function to print a string array
  */
 void print_string_array(Array* array) {
     if (!array || array->type != STRING) {
         printf("Not a string array\n");
         return;
     }
     
     printf("String Array [");
     for (size_t i = 0; i < array->count; i++) {
         char* value;
         memcpy(&value, (char*)array->parray + i * array->sizeof_type, array->sizeof_type);
         printf("\"%s\"", value);
         if (i < array->count - 1) printf(", ");
     }
     printf("]\n");
 }
 
 /**
  * Helper function to print a boolean array
  */
 void print_bool_array(Array* array) {
     if (!array || array->type != BOOL) {
         printf("Not a boolean array\n");
         return;
     }
     
     printf("Boolean Array [");
     for (size_t i = 0; i < array->count; i++) {
         bool value;
         memcpy(&value, (char*)array->parray + i * array->sizeof_type, array->sizeof_type);
         printf("%s", value ? "true" : "false");
         if (i < array->count - 1) printf(", ");
     }
     printf("]\n");
 }
 
 /**
  * Helper function to print array info
  */
 void print_array_info(Array* array, const char* name) {
     if (!array) {
         printf("%s: NULL\n", name);
         return;
     }
     
     printf("--- %s Info ---\n", name);
     printf("Type: ");
     switch (array->type) {
         case INT: printf("INT"); break;
         case FLOAT: printf("FLOAT"); break;
         case DOUBLE: printf("DOUBLE"); break;
         case CHAR: printf("CHAR"); break;
         case STRING: printf("STRING"); break;
         case BOOL: printf("BOOL"); break;
         case ARRAY: printf("ARRAY"); break;
         default: printf("UNKNOWN"); break;
     }
     printf("\n");
     
     printf("Size: %zu\n", array->count);
     printf("Capacity: %zu\n", array->capacity);
     printf("Sizeof Type: %zu bytes\n", array->sizeof_type);
     printf("Is Dynamic: %s\n", array->is_dynamic ? "Yes" : "No");
     printf("Dimensions: %zu (", array->num_dimensions);
     for (size_t i = 0; i < array->num_dimensions; i++) {
         printf("%zu", array->shape[i]);
         if (i < array->num_dimensions - 1) printf(", ");
     }
     printf(")\n");
     
     // Print array content based on type
     switch (array->type) {
         case INT:
             print_int_array(array);
             break;
         case FLOAT:
             print_float_array(array);
             break;
         case DOUBLE:
             print_double_array(array);
             break;
         case CHAR:
             print_char_array(array);
             break;
         case STRING:
             print_string_array(array);
             break;
         case BOOL:
             print_bool_array(array);
             break;
         default:
             printf("Content: (Not printable)\n");
             break;
     }
     printf("\n");
 }
 
 int main() {
     printf("===== Array Library Test =====\n\n");
     
     // Test array_empty
     printf("Testing array_empty()...\n");
     Array* empty_array = array_empty(5, INT, false);
     print_array_info(empty_array, "Empty Array");
     
     // Test array_zeros
     printf("Testing array_zeros()...\n");
     Array* zeros_array = array_zeros(5, INT, false);
     print_array_info(zeros_array, "Zeros Array");
     
     // Test array_ones
     printf("Testing array_ones()...\n");
     Array* ones_array = array_ones(5, INT, false);
     print_array_info(ones_array, "Ones Array");
     
     // Test array_ones with different types
     printf("Testing array_ones() with different types...\n");
     Array* ones_float = array_ones(5, FLOAT, false);
     print_array_info(ones_float, "Ones Float Array");
     
     Array* ones_double = array_ones(5, DOUBLE, false);
     print_array_info(ones_double, "Ones Double Array");
     
     Array* ones_char = array_ones(5, CHAR, false);
     print_array_info(ones_char, "Ones Char Array");
     
     Array* ones_bool = array_ones(5, BOOL, false);
     print_array_info(ones_bool, "Ones Bool Array");
     
     Array* ones_string = array_ones(5, STRING, false);
     print_array_info(ones_string, "Ones String Array");
     
     // Test array_full
     printf("Testing array_full()...\n");
     int value = 42;
     Array* full_array = array_full(5, INT, &value, false);
     print_array_info(full_array, "Full Array (42)");
     
     // Test array_full with different types
     printf("Testing array_full() with different types...\n");
     float float_val = 3.14f;
     Array* full_float = array_full(5, FLOAT, &float_val, false);
     print_array_info(full_float, "Full Float Array (3.14)");
     
     char char_val = 'A';
     Array* full_char = array_full(5, CHAR, &char_val, false);
     print_array_info(full_char, "Full Char Array ('A')");
     
     bool bool_val = true;
     Array* full_bool = array_full(5, BOOL, &bool_val, false);
     print_array_info(full_bool, "Full Bool Array (true)");
     
     char* str_val = "hello";
     Array* full_string = array_full(5, STRING, &str_val, false);
     print_array_info(full_string, "Full String Array (\"hello\")");
     
     // Test array_arange
     printf("Testing array_arange()...\n");
     Array* arange_array = array_arange(0, 10, 2, INT, false);
     print_array_info(arange_array, "Arange Array (0 to 10, step 2)");
     
     // Test array_arange with different types
     printf("Testing array_arange() with different types...\n");
     Array* arange_float = array_arange(0.5, 5.5, 1.0, FLOAT, false);
     print_array_info(arange_float, "Arange Float Array (0.5 to 5.5, step 1.0)");
     
     Array* arange_double = array_arange(0.5, 5.5, 1.0, DOUBLE, false);
     print_array_info(arange_double, "Arange Double Array (0.5 to 5.5, step 1.0)");
     
     // Test array_linspace
     printf("Testing array_linspace()...\n");
     Array* linspace_array = array_linspace(0, 10, 6, INT, false);
     print_array_info(linspace_array, "Linspace Array (0 to 10, 6 points)");
     
     // Test array_linspace with different types
     printf("Testing array_linspace() with different types...\n");
     Array* linspace_float = array_linspace(0.0, 1.0, 5, FLOAT, false);
     print_array_info(linspace_float, "Linspace Float Array (0.0 to 1.0, 5 points)");
     
     Array* linspace_double = array_linspace(0.0, 1.0, 5, DOUBLE, false);
     print_array_info(linspace_double, "Linspace Double Array (0.0 to 1.0, 5 points)");
     
     // Test dynamic arrays
     printf("Testing dynamic arrays...\n");
     Array* dynamic_array = array_zeros(5, INT, true);
     print_array_info(dynamic_array, "Dynamic Zeros Array");
     
     // Test array_copy
     printf("Testing array_copy()...\n");
     Array* copied_array = array_copy(full_array, false);
     print_array_info(copied_array, "Copied Array (from Full Array)");
     
     // Test array_copy with dynamic
     printf("Testing array_copy() with dynamic target...\n");
     Array* dynamic_copy = array_copy(full_array, true);
     print_array_info(dynamic_copy, "Dynamic Copied Array");
     
     // Clean up
     printf("Cleaning up...\n");
     array_free(empty_array);
     array_free(zeros_array);
     array_free(ones_array);
     array_free(ones_float);
     array_free(ones_double);
     array_free(ones_char);
     array_free(ones_bool);
     array_free(ones_string);
     array_free(full_array);
     array_free(full_float);
     array_free(full_char);
     array_free(full_bool);
     array_free(full_string);
     array_free(arange_array);
     array_free(arange_float);
     array_free(arange_double);
     array_free(linspace_array);
     array_free(linspace_float);
     array_free(linspace_double);
     array_free(dynamic_array);
     array_free(copied_array);
     array_free(dynamic_copy);
     
     printf("\nAll tests completed successfully!\n");
     
     return 0;
 }