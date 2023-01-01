#include <stdio.h>
#include <assert.h>

#include <simple_hash_table.h>

int main(int argc, char *argv[])
{
    hash_table *hash_table = simple_hash_table_new(16);

    simple_hash_table_put(hash_table, "doni", 123);
    simple_hash_table_put(hash_table, "clodosvaldo", 321);

    assert(*simple_hash_table_get(hash_table, "doni") == 123);
    assert(*simple_hash_table_get(hash_table, "clodosvaldo") == 321);

    simple_hash_table_free(&hash_table);
    assert(hash_table == NULL);

    return 0;
}