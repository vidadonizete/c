#ifndef ARRAY_LIST
#define ARRAY_LIST

typedef struct array_list {
    int capacity;
    int length;
    int* array;
} array_list;

array_list array_list_new(int capacity);

void array_list_push(array_list* self, int item);

int array_list_pop(array_list* self);

#define array_list_foreach(function, array_list) \
for (int i = 0; i < array_list.length; i++) { \
    function(i, array_list.array[i]); \
}

#endif //ARRAY_LIST