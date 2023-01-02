#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <simple_hash_table.h>

#define THRESHOLD 0.75
#define GROW_FACTOR 2

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
    size_t key_len = strnlen(key, sizeof(size_t) * 8);

    for (int i = 0; i < key_len; i++)
    {
        char c = *(key + i);
        size_t left_bitwise = c << (i % sizeof(size_t));
        hash_digest ^= left_bitwise;
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
    entry *entry = malloc(sizeof(struct entry));

    entry->key = malloc(strlen(key) * sizeof(char));
    entry->data = malloc(sizeof(int));
    entry->next = NULL;

    strcpy(entry->key, key);
    *entry->data = data;

    return entry;
}

static void simple_hash_table_check_health_and_expand(hash_table *self)
{
    float load_factor = self->entries / (float)self->capacity;
    if (load_factor < THRESHOLD)
    {
        return;
    }

    int old_capacity = self->capacity;
    int new_capacity = old_capacity * GROW_FACTOR;

    bucket *old_buckets = self->buckets;
    bucket *new_buckets = calloc(new_capacity, sizeof(bucket));

    for (int i = 0; i < old_capacity; i++)
    {
        bucket *old_bucket = old_buckets + i;
        entry *entry = old_bucket->head;

        while (entry)
        {
            struct entry *next = entry->next;
            entry->next = NULL;

            size_t index = simple_hash_table_hash_key(new_capacity, entry->key);
            bucket *new_bucket = new_buckets + index;

            simple_hash_table_insert_entry(new_bucket, entry);
            entry = next;
        }
    }

    self->capacity = new_capacity;
    self->buckets = new_buckets;

    free(old_buckets);
}

void simple_hash_table_put(hash_table *self, char *key, int data)
{
    simple_hash_table_check_health_and_expand(self);

    size_t index = simple_hash_table_hash_key(self->capacity, key);
    bucket *bucket = self->buckets + index;

    {
        entry *entry = simple_hash_table_remove_entry(bucket, key);
        self->entries += !entry;
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
    return entry == NULL ? NULL : entry->data;
}

void simple_hash_table_remove(hash_table *self, char *key)
{
    size_t index = simple_hash_table_hash_key(self->capacity, key);
    bucket *bucket = self->buckets + index;

    entry *entry = simple_hash_table_remove_entry(bucket, key);
    self->entries -= !!entry;
    simple_hash_table_free_entry(&entry);
}

void simple_hash_pretty_print(hash_table *self)
{
    for (int i = 0; i < self->capacity; i++)
    {
        printf("bucket: %d\n", i);
        bucket *bucket = self->buckets + i;
        entry *entry = bucket->head;
        while (entry)
        {
            printf("\tentry: %s %d\n", entry->key, *entry->data);
            entry = entry->next;
        }
        printf("\n");
    }
}