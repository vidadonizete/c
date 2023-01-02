#include <stdio.h>
#include <assert.h>

#include <simple_hash_table.h>

int main(int argc, char *argv[])
{
    hash_table *hash_table = simple_hash_table_new(16);

    char *string = "abcdefghijklmnopqrstuvwxyz";
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

    for (int i = 0; i < 26; i++)
    {
        char *c = string + i;
        int *data = arr + i;
        simple_hash_table_put(hash_table, c, *data);
        assert(*simple_hash_table_get(hash_table, c) == *data);
    }

    simple_hash_pretty_print(hash_table);

    for (int i = 0; i < 26; i++)
    {
        char *c = string + i;
        int *data = arr + i;
        assert(*simple_hash_table_get(hash_table, c) == *data);
    }

    assert(hash_table->entries == 26);
    assert(hash_table->capacity == 64);

    simple_hash_table_free(&hash_table);
    assert(hash_table == NULL);

    return 0;
}