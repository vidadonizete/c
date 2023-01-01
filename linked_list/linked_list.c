#include <stdlib.h>

#include <linked_list.h>

linked_list linked_list_new()
{
    return (linked_list){
        .head = NULL,
        .length = 0,
    };
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
    if (self->head == NULL)
        return 0;
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
