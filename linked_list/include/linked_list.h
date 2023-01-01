#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

typedef struct linked_node linked_node;

struct linked_node
{
    int data;
    linked_node *next;
};

typedef struct linked_list
{
    int length;
    linked_node *head;
} linked_list;

linked_list *linked_list_new();

void linked_list_free(linked_list **self);

void linked_list_push(linked_list *self, int data);

int linked_list_pop(linked_list *self);

int linked_list_get(linked_list *self, int index);

int linked_list_remove(linked_list *self, int index);

#endif //_LINKED_LIST_H