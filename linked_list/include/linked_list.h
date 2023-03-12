#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdbool.h>

struct linked_node
{
    int data;
    struct linked_node *next;
};

struct linked_list
{
    struct linked_node *head;
};

struct linked_list *linked_list_new();

void linked_list_free(struct linked_list **self);

void linked_list_push(struct linked_list *self, int data);

int linked_list_pop(struct linked_list *self);

bool linked_list_is_empty(struct linked_list *self);

#endif //_LINKED_LIST_H