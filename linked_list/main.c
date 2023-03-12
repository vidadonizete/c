#include <stdlib.h>
#include <assert.h>

#include <linked_list.h>

int main(int argc, char *argv[])
{
    struct linked_list *list = linked_list_new();

    assert(linked_list_is_empty(list) == true);

    linked_list_push(list, 1);
    linked_list_push(list, 2);
    linked_list_push(list, 3);

    assert(linked_list_is_empty(list) == false);

    assert(linked_list_pop(list) == 3);
    assert(linked_list_pop(list) == 2);
    assert(linked_list_pop(list) == 1);

    assert(linked_list_is_empty(list) == true);

    linked_list_free(&list);

    assert(list == NULL);
    
    return 0;
}