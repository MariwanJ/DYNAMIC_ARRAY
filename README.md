# Dynamic Array Library in C

This library simplifies the creation and management of dynamic arrays in C.

It provides a simple and efficient way to manage arrays whose size can change at runtime, without requiring the user to manually allocate, resize, or free the underlying memory.

The dynamic array **owns the objects stored in it**. When an object is added to the array, the library copies its data into memory managed by the dynamic array. This applies whether the original object is allocated on the stack or on the heap.

By keeping its own copy of each object, the dynamic array avoids ownership and lifetime problems. A stack-allocated object may cease to exist when its scope ends, while a heap-allocated object may be freed elsewhere. Storing only pointers to these objects could therefore leave the array with dangling pointers or lead to double-free errors.

Because the dynamic array owns its copies, it is responsible for managing and freeing the memory associated with the stored objects. This gives the array a consistent ownership model and makes memory management safer and more predictable.


- **Dynamic Resizing**: Automatically doubles or halves the array size as needed, ensuring optimal performance.
- **Type Safety**: Ensures that all elements are of the same type using templates.
- **Memory Management**: Handles memory allocation and deallocation safely.

## Usage
To use this dynamic array library in your C project:
1. Include the header file: `#include <dynamic.h>`
2. Look at the sample project provided for further info.

## Building the project
To build the project, you can use either build.sh or build.bat. In both cases, make sure to have a C compiler installed on your system.

Author : Mariwan Jalal