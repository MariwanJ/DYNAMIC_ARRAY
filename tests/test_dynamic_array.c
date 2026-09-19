#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#include <../src/dynamic.h>

/* Unit Tests*/
#define TEST_ASSERT(condition)                       \
    do                                               \
    {                                                \
        if (!(condition))                            \
        {                                            \
            fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            return 0;                                \
        }                                            \
    } while (0)

/* Test pussing int */
static int test_push_int_array(void)
{
    dynamicA D;
    INIT_DYNAMIC_ARRAY(&D);
    int values[] = {42, 32, 22, 545, 22, 33};
    PUSH_ITEM(&D, CREATE_ELEMENT(values, TYPE_INT, ARRAY_LENGTH(values)));
    TEST_ASSERT(D.count == 1);
    TEST_ASSERT(D.items[0].type == TYPE_INT);
    TEST_ASSERT(D.items[0].count == 6);

    int *data = D.items[0].data;
    TEST_ASSERT(data[0] == 42);
    TEST_ASSERT(data[1] == 32);
    TEST_ASSERT(data[5] == 33);

    free(D.items[0].data);
    free(D.items);
    return 1;
}

/* Test pussing double */
static int test_push_double_array(void)
{
    dynamicA D;

    INIT_DYNAMIC_ARRAY(&D);

    double values[] = {1.2, 3.4, 5.6};

    PUSH_ITEM(
        &D,
        CREATE_ELEMENT(values, TYPE_DOUBLE, ARRAY_LENGTH(values)));

    TEST_ASSERT(D.count == 1);
    TEST_ASSERT(D.items[0].type == TYPE_DOUBLE);
    TEST_ASSERT(D.items[0].count == 3);

    double *data = D.items[0].data;

    TEST_ASSERT(data[0] == 1.2);
    TEST_ASSERT(data[1] == 3.4);
    TEST_ASSERT(data[2] == 5.6);

    free(D.items[0].data);
    free(D.items);

    return 1;
}

/* Test pussing string */
static int test_push_string(void)
{
    dynamicA D;

    INIT_DYNAMIC_ARRAY(&D);

    char str[] = "Hello";

    PUSH_ITEM(
        &D,
        CREATE_ELEMENT(str, TYPE_CHAR, ARRAY_LENGTH(str)));

    TEST_ASSERT(D.count == 1);
    TEST_ASSERT(D.items[0].type == TYPE_CHAR);

    char *data = D.items[0].data;

    TEST_ASSERT(strcmp(data, "Hello") == 0);

    free(D.items[0].data);
    free(D.items);

    return 1;
}

/* Test ownership, dynamic array owns the values, local value is not owned by the array*/
static int test_push_makes_copy(void)
{
    dynamicA D;
    INIT_DYNAMIC_ARRAY(&D);
    int values[] = {10, 20, 30};
    PUSH_ITEM(&D, CREATE_ELEMENT(values, TYPE_INT, ARRAY_LENGTH(values)));

    /* Change the original */
    values[0] = 999;
    int *data = D.items[0].data;
    /* D should still contain the original value */
    TEST_ASSERT(data[0] == 10);

    free(D.items[0].data);
    free(D.items);

    return 1;
}
/* Test passing dynamic array */
static int test_push_heap_array(void)
{
    dynamicA D;

    INIT_DYNAMIC_ARRAY(&D);
    int *values = malloc(4 * sizeof *values);
    TEST_ASSERT(values != NULL);
    values[0] = 100;
    values[1] = 200;
    values[2] = 300;
    values[3] = 400;

    PUSH_ITEM(&D, CREATE_ELEMENT(values, TYPE_INT, 4));

    /* Original memory can be freed */
    free(values);

    int *data = D.items[0].data;

    TEST_ASSERT(D.count == 1);
    TEST_ASSERT(data[0] == 100);
    TEST_ASSERT(data[1] == 200);
    TEST_ASSERT(data[2] == 300);
    TEST_ASSERT(data[3] == 400);

    free(D.items[0].data);
    free(D.items);

    return 1;
}

int main(void)
{
    int passed = 0;
    int total = 5;

    passed += test_push_int_array();
    passed += test_push_double_array();
    passed += test_push_string();
    passed += test_push_makes_copy();
    passed += test_push_heap_array();

    printf("\nTests: %d/%d passed\n", passed, total);

    return passed == total ? 0 : 1;
}