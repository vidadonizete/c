#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "array_list.h"

static void array_list_foreach_function(int index, int item) {
    printf("index: %d, value: %d\n", index, item);
}

int main(int argc, char* argv[]) {
    array_list arr = array_list_new(0);
    char buffer[256];
    #define BGETS fgets(buffer, 256, stdin)

    while (1) {
        printf("1 for push\n2 for pop\n3 for foreach: ");
        BGETS;
        printf("\n");
        
        switch(buffer[0]) {
            case '1': {
                printf("Place your number:\n");
                BGETS;
                array_list_push(&arr, atoi(buffer));
                break;
            }
            case '2': {
                int pop = array_list_pop(&arr);
                printf("pop: %d\n", pop);
                break;
            }
            case '3': {
                array_list_foreach(array_list_foreach_function, arr);
                break;
            }
        }
    }
}

