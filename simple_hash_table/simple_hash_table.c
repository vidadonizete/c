#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <simple_hash_table.h>

#define THRESHOLD 0.75
#define GROW_FACTOR 2

struct hash_table *simple_hash_table_new(int capacity)
{
    struct hash_table *table = malloc(sizeof(struct hash_table));

    table->capacity = capacity;
    table->entries = 0;
    table->buckets = calloc(capacity, sizeof(struct bucket));

    return table;
}

static void simple_hash_table_free_entry(struct entry **entry)
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

void simple_hash_table_free(struct hash_table **self)
{
    for (int i = 0; i < (*self)->capacity; i++)
    {
        struct bucket *bucket = (*self)->buckets + i;
        struct entry *entry = bucket->entry;
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
    size_t key_len = strnlen(key, sizeof(size_t) * 8);

    for (int i = 0; i < key_len; i++)
    {
        char c = *(key + i);
        size_t left_bitwise = c << (i % sizeof(size_t));
        hash_digest ^= left_bitwise;
    }

    return hash_digest % buckets;
}

static struct entry *simple_hash_table_remove_entry(struct bucket *bucket, char *key)
{
    struct entry *entry = bucket->entry;
    struct entry *before = NULL;
    while (entry && strcmp(entry->key, key))
    {
        before = entry;
        entry = entry->next;
    }
    if (entry == NULL)
    {
        return NULL;
    }
    if (before)
    {
        before->next = entry->next;
    }
    else
    {
        bucket->entry = entry->next;
    }
    return entry;
}

static struct entry *simple_hash_table_find_entry(struct bucket *bucket, char *key)
{
    struct entry *entry = bucket->entry;
    while (entry && strcmp(entry->key, key))
    {
        entry = entry->next;
    }
    return entry;
}

static void simple_hash_table_insert_entry(struct bucket *bucket, struct entry *entry)
{
    entry->next = bucket->entry;
    bucket->entry = entry;
}

static struct entry *simple_hash_table_create_entry(char *key, int data)
{
    struct entry *entry = malloc(sizeof(struct entry));

    entry->key = malloc(strlen(key) * sizeof(char));
    entry->data = malloc(sizeof(int));
    entry->next = NULL;

    strcpy(entry->key, key);
    *entry->data = data;

    return entry;
}

static void simple_hash_table_check_health_and_expand(struct hash_table *self)
{
    float load_factor = self->entries / (float)self->capacity;
    if (load_factor < THRESHOLD)
    {
        return;
    }

    int old_capacity = self->capacity;
    int new_capacity = old_capacity * GROW_FACTOR;

    struct bucket *old_buckets = self->buckets;
    struct bucket *new_buckets = calloc(new_capacity, sizeof(struct bucket));

    for (int i = 0; i < old_capacity; i++)
    {
        struct bucket *old_bucket = old_buckets + i;
        struct entry *entry = old_bucket->entry;

        while (entry)
        {
            struct entry *next = entry->next;
            entry->next = NULL;

            size_t index = simple_hash_table_hash_key(new_capacity, entry->key);
            struct bucket *new_bucket = new_buckets + index;

            simple_hash_table_insert_entry(new_bucket, entry);
            entry = next;
        }
    }

    self->capacity = new_capacity;
    self->buckets = new_buckets;

    free(old_buckets);
}

void simple_hash_table_put(struct hash_table *self, char *key, int data)
{
    simple_hash_table_check_health_and_expand(self);

    size_t index = simple_hash_table_hash_key(self->capacity, key);
    struct bucket *bucket = self->buckets + index;

    {
        struct entry *entry = simple_hash_table_remove_entry(bucket, key);
        self->entries += !entry;
        simple_hash_table_free_entry(&entry);
    }

    {
        struct entry *entry = simple_hash_table_create_entry(key, data);
        simple_hash_table_insert_entry(bucket, entry);
    }
}

int *simple_hash_table_get(struct hash_table *self, char *key)
{
    size_t index = simple_hash_table_hash_key(self->capacity, key);
    struct bucket *bucket = self->buckets + index;

    struct entry *entry = simple_hash_table_find_entry(bucket, key);
    return entry == NULL ? NULL : entry->data;
}

void simple_hash_table_remove(struct hash_table *self, char *key)
{
    size_t index = simple_hash_table_hash_key(self->capacity, key);
    struct bucket *bucket = self->buckets + index;

    struct entry *entry = simple_hash_table_remove_entry(bucket, key);
    self->entries -= !!entry;
    simple_hash_table_free_entry(&entry);
}

void simple_hash_pretty_print(struct hash_table *self)
{
    for (int i = 0; i < self->capacity; i++)
    {
        printf("bucket: %d\n", i);
        struct bucket *bucket = self->buckets + i;
        struct entry *entry = bucket->entry;
        while (entry)
        {
            printf("\tentry: %s %d\n", entry->key, *entry->data);
            entry = entry->next;
        }
        printf("\n");
    }
}