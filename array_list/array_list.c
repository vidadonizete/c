#include <stdlib.h>
#include <stdio.h>

#include <array_list.h>

#define GROW_FACTOR 2

array_list array_list_new(int capacity)
{
    return (array_list){
        .capacity = capacity > 0 ? capacity : 2,
        .length = 0,
        .array = calloc(capacity > 0 ? capacity : 2, sizeof(int)),
    };
}

static void array_list_grow(array_list *self)
{
    int new_capacity = GROW_FACTOR * self->capacity;
    self->capacity = new_capacity;
    self->array = realloc(self->array, new_capacity * sizeof(int));
}

void array_list_push(array_list *self, int data)
{
    if (self->length >= self->capacity)
    {
        array_list_grow(self);
    }
    self->array[self->length++] = data;
}

int array_list_pop(array_list *self)
{
    if (!self->length)
        return 0;
    return self->array[--self->length];
}

int array_list_get(array_list *self, int index)
{
    return self->array[index];
}