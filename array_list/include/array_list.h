#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

typedef struct array_list
{
    int capacity;
    int length;
    int *array;
} array_list;

array_list *array_list_new(int capacity);

void array_list_free(array_list **self);

void array_list_push(array_list *self, int data);

int array_list_pop(array_list *self);

int array_list_get(array_list *self, int index);

int array_list_remove(array_list *self, int index);

#define array_list_foreach(function, array_list) \
    for (int i = 0; i < array_list.length; i++)  \
    {                                            \
        function(i, array_list.array[i]);        \
    }

#endif // _ARRAY_LIST_H