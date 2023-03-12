#include <stdlib.h>
#include <linked_list.h>

struct linked_list *linked_list_new()
{
    struct linked_list *list = malloc(sizeof(struct linked_list));
    list->head = NULL;
    return list;
}

void linked_list_free(struct linked_list **self)
{
    struct linked_node *node = (*self)->head;
    while (node)
    {
        struct linked_node *next = node->next;
        free(node);
        node = next;
    }
    *self = NULL;
}

static struct linked_node *linked_list_new_node(int data)
{
    struct linked_node *node = malloc(sizeof(struct linked_node));
    node->data = data;
    node->next = NULL;
    return node;
}

void linked_list_push(struct linked_list *self, int data)
{
    struct linked_node *node = linked_list_new_node(data);
    node->next = self->head;
    self->head = node;
}

int linked_list_pop(struct linked_list *self)
{
    struct linked_node *node = self->head;
    if (!node)
        exit(1);
    self->head = node->next;
    int data = node->data;
    free(node);
    return data;
}

bool linked_list_is_empty(struct linked_list *self)
{
    return self->head == NULL;
}