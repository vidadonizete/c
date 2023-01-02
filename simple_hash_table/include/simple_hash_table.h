#ifndef _SIMPLE_HASH_TABLE_H
#define _SIMPLE_HASH_TABLE_H

typedef struct entry entry;

struct entry
{
    char *key;
    int *data;
    entry *next;
};

typedef struct bucket
{
    int size;
    entry *head;
    entry *tail;
} bucket;

typedef struct hash_table
{
    int capacity;
    int entries;
    bucket *buckets;
} hash_table;

hash_table *simple_hash_table_new(int capacity);

void simple_hash_table_free(hash_table **self);

void simple_hash_table_put(hash_table *self, char *key, int data);

int *simple_hash_table_get(hash_table *self, char *key);

void simple_hash_table_remove(hash_table *self, char *key);

#endif //_SIMPLE_HASH_TABLE_H