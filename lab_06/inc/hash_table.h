#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#define MAX_WORD_LNG 30

#define HASH_TABLE_CAPACITY 31

#include "data.h"

typedef unsigned int (*hash_foo_t)(const char *restrict str);

struct value_list {
    data_t *data;
    struct value_list *next;
};

typedef struct value_list value_list_t;

typedef struct {
    value_list_t *values[HASH_TABLE_CAPACITY];
    hash_foo_t hash_foo;
} hash_table_t;

hash_table_t *hash_table_create(data_t *data);
void hash_table_set(hash_table_t *table, data_t *data);
data_t *hash_table_get(hash_table_t *table, const char *restrict key);
void hash_table_remove(hash_table_t *table, const char *restrict key);

hash_table_t *has_table_restruct(hash_table_t *table, const long depth);

void hash_table_print(const hash_table_t *table);
#endif
