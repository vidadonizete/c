#ifndef _SIMPLE_HASH_TABLE_H
#define _SIMPLE_HASH_TABLE_H

struct entry
{
    char *key;
    int *data;
    struct entry *next;
};

struct bucket
{
    struct entry *entry;
};

struct hash_table
{
    int capacity;
    int entries;
    struct bucket *buckets;
};

struct hash_table *simple_hash_table_new(int capacity);

void simple_hash_table_free(struct hash_table **self);

void simple_hash_table_put(struct hash_table *self, char *key, int data);

int *simple_hash_table_get(struct hash_table *self, char *key);

void simple_hash_table_remove(struct hash_table *self, char *key);

void simple_hash_pretty_print(struct hash_table *self);

#endif //_SIMPLE_HASH_TABLE_H