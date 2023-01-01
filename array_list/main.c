#include <stdlib.h>
#include <assert.h>

#include <array_list.h>

int main(int argc, char *argv[])
{
    array_list *list = array_list_new(2);
    assert(list->capacity == 2);
    assert(list->length == 0);

    array_list_push(list, 101);
    assert(list->capacity == 2);
    assert(list->length == 1);
    assert(array_list_get(list, 0) == 101);

    array_list_push(list, 102);
    assert(list->capacity == 2);
    assert(list->length == 2);
    assert(array_list_get(list, 1) == 102);

    array_list_push(list, 103);
    assert(list->capacity == 4);
    assert(list->length == 3);
    assert(array_list_get(list, 2) == 103);

    array_list_push(list, 104);
    assert(list->capacity == 4);
    assert(list->length == 4);
    assert(array_list_get(list, 3) == 104);

    assert(array_list_pop(list) == 104);
    assert(array_list_pop(list) == 103);
    assert(array_list_pop(list) == 102);
    assert(array_list_pop(list) == 101);
    assert(list->length == 0);

    array_list_push(list, 101);
    array_list_push(list, 102);
    array_list_push(list, 103);
    assert(list->length == 3);

    assert(array_list_remove(list, 0) == 101);
    assert(array_list_get(list, 0) == 102);

    assert(array_list_remove(list, 0) == 102);
    assert(array_list_get(list, 0) == 103);

    assert(list->length == 1);

    array_list_free(&list);
    assert(list == NULL);

    return 0;
}