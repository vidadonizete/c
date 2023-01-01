#include <assert.h>

#include <linked_list.h>

int main(int argc, char *argv[])
{
    linked_list list = linked_list_new();

    assert(list.length == 0);

    linked_list_push(&list, 101);
    assert(list.length == 1);
    assert(linked_list_get(&list, 0) == 101);

    linked_list_push(&list, 102);
    assert(list.length == 2);
    assert(linked_list_get(&list, 1) == 102);

    linked_list_push(&list, 103);
    assert(list.length == 3);
    assert(linked_list_get(&list, 2) == 103);

    linked_list_push(&list, 104);
    assert(list.length == 4);
    assert(linked_list_get(&list, 3) == 104);

    assert(linked_list_get(&list, 0) == 101);
    assert(linked_list_get(&list, 1) == 102);
    assert(linked_list_get(&list, 2) == 103);
    assert(linked_list_get(&list, 3) == 104);

    assert(linked_list_pop(&list) == 104);
    assert(linked_list_pop(&list) == 103);
    assert(linked_list_pop(&list) == 102);
    assert(linked_list_pop(&list) == 101);

    assert(list.length == 0);

    return 0;
}