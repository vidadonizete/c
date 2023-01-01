#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <array_list.h>

#define GROW_FACTOR 2

array_list *array_list_new(int capacity)
{
    assert(capacity > 0);
    array_list *list = malloc(sizeof(array_list));
    *list = (array_list){
        .capacity = capacity,
        .length = 0,
        .array = calloc(capacity, sizeof(int)),
    };
    return list;
}

void array_list_free(array_list **self)
{
    free((*self)->array);
    free((*self));
    *self = NULL;
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
    return self->array[--self->length];
}

int array_list_get(array_list *self, int index)
{
    return self->array[index];
}

int array_list_remove(array_list *self, int index)
{
    int data = array_list_get(self, index);
    for (int i = index; i < self->capacity - 1; i++)
    {
        self->array[i] = self->array[i + 1];
    }
    self->length--;
    return data;
}