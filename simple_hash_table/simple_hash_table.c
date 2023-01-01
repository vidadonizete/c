#include <stdlib.h>
#include <string.h>

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

//its a hash by division
//whatever shit trying to calculate some "unique" hash based on
//string char
static size_t simple_hash_table_hash_key(int buckets, char *key)
{
    size_t hash_digest = 0;
    size_t size_t_size_in_bytes = sizeof(size_t);
    size_t key_len = strnlen(key, size_t_size_in_bytes);

    for (int i = 0; i < key_len; i++)
    {
        hash_digest ^= *(key + i) << (i % size_t_size_in_bytes);
    }
    return hash_digest % buckets;
}

int *simple_hash_table_put(hash_table *self, char *key, int data)
{
    size_t index = simple_hash_table_hash_key(self->buckets, key);
}

int *simple_hash_table_get(hash_table *self, char *key)
{
}

int *simple_hash_table_remove(hash_table *self, char *key)
{
}