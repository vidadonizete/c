#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <simple_hash_table.h>

#define THRESHOLD 0.75

hash_table *simple_hash_table_new(int capacity)
{
    hash_table *table = malloc(sizeof(hash_table));

    table->capacity = capacity;
    table->entries = 0;
    table->buckets = calloc(capacity, sizeof(bucket));

    return table;
}

static void simple_hash_table_free_entry(entry **entry)
{
    if (entry == NULL || *entry == NULL)
    {
        return;
    }
    free((*entry)->key);
    free((*entry)->data);
    free(*entry);

    *entry = NULL;
}

void simple_hash_table_free(hash_table **self)
{
    for (int i = 0; i < (*self)->capacity; i++)
    {
        bucket *bucket = (*self)->buckets + i;
        entry *entry = bucket->head;
        while (entry)
        {
            struct entry *next = entry->next;
            simple_hash_table_free_entry(&entry);
            entry = next;
        }
    }
    free((*self)->buckets);
    free(*self);
    *self = NULL;
}

// its a hash by division algorithm
// whatever shit trying to calculate some "unique" hash based on
// string char
static size_t simple_hash_table_hash_key(int buckets, char *key)
{
    size_t hash_digest = 0;
    size_t key_len = strnlen(key, sizeof(size_t));

    for (int i = 0; i < key_len; i++)
    {
        hash_digest ^= *(key + i) << (i % sizeof(size_t));
    }

    return hash_digest % buckets;
}

static entry *simple_hash_table_remove_entry(bucket *bucket, char *key)
{
    if (bucket->head == NULL)
    {
        assert(bucket->tail == NULL);
        return NULL;
    }

    entry *before = NULL;
    entry *entry = bucket->head;

    while (entry && strcmp(entry->key, key))
    {
        before = entry;
        entry = entry->next;
    }

    if (!entry)
    {
        return NULL;
    }
    else if (bucket->head == bucket->tail)
    {
        assert(bucket->head->next == NULL);
        assert(bucket->tail->next == NULL);

        bucket->head = NULL;
        bucket->tail = NULL;
    }
    else if (bucket->head == entry)
    {
        bucket->head = entry->next;
    }
    else if (bucket->tail == entry)
    {
        assert(before);
        assert(entry->next == NULL);

        before->next = NULL;
        bucket->tail = before;
    }
    else
    {
        before->next = entry->next;
    }

    return entry;
}

static entry *simple_hash_table_find_entry(bucket *bucket, char *key)
{
    if (bucket->head == NULL)
    {
        return NULL;
    }
    entry *entry = bucket->head;
    while (entry && strcmp(entry->key, key))
    {
        entry = entry->next;
    }
    return entry;
}

static void simple_hash_table_insert_entry(bucket *bucket, entry *entry)
{
    if (bucket->tail == NULL)
    {
        assert(bucket->head == NULL);
        bucket->head = entry;
        bucket->tail = entry;
    }
    else
    {
        assert(bucket->head);
        bucket->tail->next = entry;
        bucket->tail = entry;
    }
}

static entry *simple_hash_table_create_entry(char *key, int data)
{
    entry *entry = malloc(sizeof(entry));

    entry->key = calloc(strlen(key), sizeof(char));
    entry->data = malloc(sizeof(int));
    entry->next = NULL;

    strcpy(entry->key, key);
    *entry->data = data;

    return entry;
}

void simple_hash_table_put(hash_table *self, char *key, int data)
{
    size_t index = simple_hash_table_hash_key(self->capacity, key);
    bucket *bucket = self->buckets + index;

    {
        entry *entry = simple_hash_table_remove_entry(bucket, key);
        simple_hash_table_free_entry(&entry);
    }

    {
        entry *entry = simple_hash_table_create_entry(key, data);
        simple_hash_table_insert_entry(bucket, entry);
    }
}

int *simple_hash_table_get(hash_table *self, char *key)
{
    size_t index = simple_hash_table_hash_key(self->capacity, key);
    bucket *bucket = self->buckets + index;
    entry *entry = simple_hash_table_find_entry(bucket, key);
    if (entry == NULL)
    {
        return NULL;
    }
    return entry->data;
}

void simple_hash_table_remove(hash_table *self, char *key)
{
    size_t index = simple_hash_table_hash_key(self->capacity, key);
    bucket *bucket = self->buckets + index;
    entry *entry = simple_hash_table_remove_entry(bucket, key);
    simple_hash_table_free_entry(&entry);
}