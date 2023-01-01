#ifndef _SIMPLE_HASH_TABLE_H
#define _SIMPLE_HASH_TABLE_H

typedef struct entry entry;

struct entry
{
    char *key;
    int value;
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
    int buckets;
    int entries;
    bucket *buckets_ptr;
} hash_table;

hash_table *simple_hash_table_new(int capacity);

int *simple_hash_table_put(char *key);

int *simple_hash_table_get(char *key);

int *simple_hash_table_remove(char *key);

#endif //_SIMPLE_HASH_TABLE_H