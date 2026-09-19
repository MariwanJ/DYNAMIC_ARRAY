//
// MIT License
//
// Copyright (c) 2026
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Author :Mariwan Jalal
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
/*
 This library allows you to create and manage dynamic arrays in C.
Memory is allocated dynamically, and the array automatically grows when it reaches its current
capacity.
The library also provides functionality for freeing the allocated memory
The dynamic array takes ownership of the objects stored in it by copying their data into the array,
regardless of whether the original objects are allocated on the stack or the heap.
This helps prevent memory leaks and ensures that the dynamic array manages its own memory safely.
The library also provides functionality for printing the items stored in the array.
**Note:** This library uses macros rather than functions for its operations.
*/

#define ARRAY_LENGTH(X) (sizeof(X) / sizeof((X)[0]))
#define INITIAL_CAPACITY 2

typedef enum
{
    TYPE_INT,
    TYPE_UINT,
    TYPE_LONG,
    TYPE_ULONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} Type;

#define TYPE_SIZE(T)                                                          \
    ((T) == TYPE_INT ? sizeof(int) : (T) == TYPE_UINT ? sizeof(unsigned int)  \
                                 : (T) == TYPE_LONG   ? sizeof(long)          \
                                 : (T) == TYPE_ULONG  ? sizeof(unsigned long) \
                                 : (T) == TYPE_FLOAT  ? sizeof(float)         \
                                 : (T) == TYPE_DOUBLE ? sizeof(double)        \
                                 : (T) == TYPE_CHAR   ? sizeof(char)          \
                                 : (T) == TYPE_STRING ? sizeof(char)          \
                                                      : 0)

typedef struct
{
    void *data;
    Type type;
    size_t count;
} item;

typedef struct dynamicA
{
    item *items;
    size_t capacity;
    size_t count;
} dynamicA;

/*
 * Create one item / element.
 *
 * X must be an existing object because &(X) is used.
 */
#define CREATE_ELEMENT(X, T, N) \
    ((item){                    \
        .data = (X),            \
        .type = (T),            \
        .count = (N)})
/*
 * Push an item into the dynamic array.
 *
 * X must be an item. , NOTE: push let dynamic array to own the object
 */
#define PUSH_ITEM(D, X)                                                                            \
    do                                                                                             \
    {                                                                                              \
        if ((D) != NULL)                                                                           \
        {                                                                                          \
            if ((D)->count >= (D)->capacity)                                                       \
            {                                                                                      \
                size_t new_capacity = ((D)->capacity == 0) ? INITIAL_CAPACITY : (D)->capacity * 2; \
                item *new_items = realloc((D)->items, new_capacity * sizeof *(D)->items);          \
                if (new_items == NULL)                                                             \
                {                                                                                  \
                    fprintf(stderr, "Out of memory\n");                                            \
                    break;                                                                         \
                }                                                                                  \
                (D)->items = new_items;                                                            \
                (D)->capacity = new_capacity;                                                      \
            }                                                                                      \
            item temp = (X);                                                                       \
            size_t bytes = temp.count * TYPE_SIZE(X.type);                                         \
            temp.data = malloc(bytes);                                                             \
            if (temp.data == NULL)                                                                 \
            {                                                                                      \
                fprintf(stderr, "Out of memory\n");                                                \
                break;                                                                             \
            }                                                                                      \
            memcpy(temp.data, (X).data, bytes);                                                    \
            (D)->items[(D)->count++] = temp;                                                       \
        }                                                                                          \
    } while (0)
/*
 * Pop an item from the dynamic array.
 *
 * val must be an item variable.
 */
#define pop_item(D, val)                    \
    do                                      \
    {                                       \
        if ((D) == NULL || (D)->count == 0) \
        {                                   \
            (val) = (item){0};              \
            break;                          \
        }                                   \
        (val) = (D)->items[--(D)->count];   \
        (D)->items[(D)->count] = (item){0}; \
    } while (0)

/*
 * Free the dynamic array.
 *
 * IMPORTANT:
 * This frees item.data for every element.
 * Therefore the dynamic array must own the data.
 */
#define FREE_DYNAMIC_ARRAY(D)                       \
    do                                              \
    {                                               \
        if ((D) != NULL)                            \
        {                                           \
            for (size_t i = 0; i < (D)->count; ++i) \
            {                                       \
                free((D)->items[i].data);           \
                (D)->items[i].data = NULL;          \
            }                                       \
                                                    \
            free((D)->items);                       \
            (D)->items = NULL;                      \
            (D)->capacity = 0;                      \
            (D)->count = 0;                         \
        }                                           \
    } while (0)

/*
 * Initialize an existing dynamic array.
 */
#define INIT_DYNAMIC_ARRAY(D)                                           \
    do                                                                  \
    {                                                                   \
        if ((D) != NULL)                                                \
        {                                                               \
            (D)->count = 0;                                             \
            (D)->capacity = INITIAL_CAPACITY;                           \
            (D)->items = malloc(INITIAL_CAPACITY * sizeof *(D)->items); \
                                                                        \
            if ((D)->items == NULL)                                     \
                (D)->capacity = 0;                                      \
        }                                                               \
    } while (0)

#define PRINT_ITEM(X)                                    \
    do                                                   \
    {                                                    \
        if ((X) == NULL || (X)->data == NULL)            \
            break;                                       \
                                                         \
        switch ((X)->type)                               \
        {                                                \
        case TYPE_INT:                                   \
        {                                                \
            int *data = (X)->data;                       \
            for (size_t i = 0; i < (X)->count; ++i)      \
                printf("Value[%zu]: %d\n", i, data[i]);  \
            break;                                       \
        }                                                \
                                                         \
        case TYPE_UINT:                                  \
        {                                                \
            unsigned int *data = (X)->data;              \
            for (size_t i = 0; i < (X)->count; ++i)      \
                printf("Value[%zu]: %u\n", i, data[i]);  \
            break;                                       \
        }                                                \
                                                         \
        case TYPE_LONG:                                  \
        {                                                \
            long *data = (X)->data;                      \
            for (size_t i = 0; i < (X)->count; ++i)      \
                printf("Value[%zu]: %ld\n", i, data[i]); \
            break;                                       \
        }                                                \
                                                         \
        case TYPE_ULONG:                                 \
        {                                                \
            unsigned long *data = (X)->data;             \
            for (size_t i = 0; i < (X)->count; ++i)      \
                printf("Value[%zu]: %lu\n", i, data[i]); \
            break;                                       \
        }                                                \
                                                         \
        case TYPE_FLOAT:                                 \
        {                                                \
            float *data = (X)->data;                     \
            for (size_t i = 0; i < (X)->count; ++i)      \
                printf("Value[%zu]: %f\n", i, data[i]);  \
            break;                                       \
        }                                                \
                                                         \
        case TYPE_DOUBLE:                                \
        {                                                \
            double *data = (X)->data;                    \
            for (size_t i = 0; i < (X)->count; ++i)      \
                printf("Value[%zu]: %f\n", i, data[i]);  \
            break;                                       \
        }                                                \
        case TYPE_CHAR:                                  \
        {                                                \
            char *data = (X)->data;                      \
            printf("String: %s\n", data);                \
            break;                                       \
        }                                                \
                                                         \
        default:                                         \
            printf("Unknown type\n");                    \
            break;                                       \
        }                                                \
    } while (0)
