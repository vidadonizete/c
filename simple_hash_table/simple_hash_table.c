#include <stdlib.h>

#include <simple_hash_table.h>

hash_table *simple_hash_table_new(int capacity)
{
    hash_table *table = malloc(sizeof(hash_table));
    table->buckets = capacity;
    table->entries = 0;
    table->buckets_ptr = calloc(capacity, sizeof(bucket));
    return table;
}

int *simple_hash_table_put(char *key)
{
    
}

int *simple_hash_table_get(char *key)
{
}

int *simple_hash_table_remove(char *key)
{
}