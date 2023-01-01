#include <assert.h>

#include <array_list.h>

int main(int argc, char *argv[])
{
    array_list arr = array_list_new(0);

    // Initial state
    assert(arr.capacity == 2);
    assert(arr.length == 0);

    // No allocation needed
    array_list_push(&arr, 101);
    assert(arr.capacity == 2);
    assert(arr.length == 1);
    assert(array_list_get(&arr, 0) == 101);

    // No allocation needed
    array_list_push(&arr, 102);
    assert(arr.capacity == 2);
    assert(arr.length == 2);
    assert(array_list_get(&arr, 1) == 102);

    // Re-allocation needed
    array_list_push(&arr, 103);
    assert(arr.capacity == 4);
    assert(arr.length == 3);
    assert(array_list_get(&arr, 2) == 103);

    // Pop result
    assert(array_list_pop(&arr) == 103);
    assert(array_list_pop(&arr) == 102);
    assert(array_list_pop(&arr) == 101);

    return 0;
}