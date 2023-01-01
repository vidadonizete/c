#include <stdlib.h>

#include <linked_list.h>

linked_list *linked_list_new()
{
    linked_list *list = malloc(sizeof(linked_list));
    *list = (linked_list){
        .head = NULL,
        .length = 0,
    };
    return list;
}

void linked_list_free(linked_list **self)
{
    linked_node *node = (*self)->head;
    while (node)
    {
        linked_node *next = node->next;
        free(node);
        node = next;
    }
    free((*self));
    *self = NULL;
}

static linked_node *linked_list_new_node(int data)
{
    linked_node *node = malloc(sizeof(linked_node));
    node->data = data;
    node->next = NULL;
    return node;
}

void linked_list_push(linked_list *self, int data)
{
    linked_node *node = linked_list_new_node(data);
    node->next = self->head;
    self->head = node;
    self->length++;
}

int linked_list_pop(linked_list *self)
{
    linked_node *node = self->head;
    self->head = node->next;
    self->length--;
    int data = node->data;
    free(node);
    return data;
}

int linked_list_get(linked_list *self, int index)
{
    // how much to move to the right on linked list
    //(obviously it depends on how you see it on your mind)
    //  -->>
    //  head {
    //      data
    //      next: {
    //          data
    //          next: {
    //              ...
    //          }
    //      }
    //  }
    int offset = self->length - index - 1;
    linked_node *node = self->head;
    while (offset--)
        node = node->next;
    return node->data;
}

int linked_list_remove(linked_list *self, int index)
{
    int offset = self->length - index - 1;
    linked_node *node;
    if (offset == 0)
    {
        node = self->head;
        self->head = node->next;
    }
    else
    {
        int before_offset = offset - 1;
        linked_node *before = self->head;
        while (before_offset--)
            before = before->next;

        node = before->next;
        before->next = node->next;
    }

    self->length--;
    int data = node->data;
    free(node);
    return data;
}