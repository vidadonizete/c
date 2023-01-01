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

void simple_hash_table_free(hash_table **self)
{
}

int *simple_hash_table_put(hash_table *self, char *key, int data)
{
}

int *simple_hash_table_get(hash_table *self, char *key)
{
}

int *simple_hash_table_remove(hash_table *self, char *key)
{
}