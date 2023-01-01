#include <stdio.h>

#include <simple_hash_table.h>

int main(int argc, char *argv[])
{
    hash_table *hash_table = simple_hash_table_new(16);
    printf("Hello world");
    return 0;
}