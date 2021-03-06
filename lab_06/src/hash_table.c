#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int total_comparisons_hash = 0;

static int my_strcmp(const char *restrict first, const char *restrict second)
{
    total_comparisons_hash++;

    return strcmp(first, second);
}

static unsigned int hash_ly(const char *restrict str)
{
    unsigned int hash = 0;

    for(; *str; str++)
        hash = (hash * 1664525) + (unsigned char)(*str) + 1013904223;

    return hash;
}

static unsigned int hash_faq6(const char *restrict str) __attribute__((unused));

static unsigned int hash_faq6(const char *restrict str)
{
    unsigned int hash = 0;

    for (; *str; str++)
    {
        hash += (unsigned char)(*str);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

static value_list_t *list_push_back(value_list_t *list, data_t *data)
{
    value_list_t *new_elem = malloc(sizeof(value_list_t));

    if (new_elem == NULL)
        return NULL;

    new_elem->next = NULL;
    new_elem->data = data;

    if (list == NULL)
        return new_elem;

    value_list_t *head = list;

    for ( ; list->next != NULL; list = list->next);

    list->next = new_elem;

    return head;
}

void hash_table_set(hash_table_t *table, data_t *data)
{
    if (table == NULL)
        return;

    unsigned int index = table->hash_foo(data->word) % HASH_TABLE_CAPACITY;

    table->values[index] = list_push_back(table->values[index], data);
}

hash_table_t *hash_table_create(data_t *data)
{
    hash_table_t *table = malloc(sizeof(hash_table_t));

    if (table == NULL)
        return NULL;

    for (size_t i = 0; i < HASH_TABLE_CAPACITY; i++)
        table->values[i] = NULL;

    table->hash_foo = hash_faq6;

    if (data)
        hash_table_set(table, data);

    return table;
}

data_t *hash_table_get(hash_table_t *table, const char *restrict key)
{
    unsigned int index = table->hash_foo(key) % HASH_TABLE_CAPACITY;

    value_list_t *head = table->values[index];

    for ( ; head; head = head->next)
        if (my_strcmp(head->data->word, key) == 0)
            return head->data;

    return NULL;
}

static long hash_table_depth(hash_table_t *table)
{
    long max_depth = 0;

    for (int i = 0; i < HASH_TABLE_CAPACITY; i++)
    {
        value_list_t *head = table->values[i];
        long cur_depth = 0;

        for ( ; head; head = head->next)
            cur_depth++;

        if (cur_depth > max_depth)
            max_depth = cur_depth;
    }

    return max_depth;
}

hash_table_t *has_table_restruct(hash_table_t *table, const long depth)
{
    printf("Current depth: %ld\n", hash_table_depth(table));

    if (depth > hash_table_depth(table))
    {
        printf("Restruct not required\n");
        return table;
    }

    hash_table_t *new_table = hash_table_create(NULL);

    if (table->hash_foo == hash_ly)
        new_table->hash_foo = hash_faq6;
    else if (table->hash_foo == hash_faq6)
        new_table->hash_foo = hash_ly;

    for (int i = 0; i < HASH_TABLE_CAPACITY; i++)
    {
        value_list_t *head = table->values[i];

        for ( ; head; head = head->next)
            hash_table_set(new_table, head->data);
    }

    long cmp = hash_table_depth(new_table) - hash_table_depth(table);

    if (cmp > 0)
    {
        printf("More cmps than before...\n");
    }
    else if (cmp < 0)
    {
        printf("Less cmps than before\n");
    }
    else
    {
        printf("Seems to have no effect\n");
    }

    return new_table;
}

void hash_table_print(const hash_table_t *table)
{
    for (size_t i = 0; i < HASH_TABLE_CAPACITY; i++)
    {
        printf("table[%ld] -> ", i);

        value_list_t *list = table->values[i];

        for ( ; list; list = list->next)
            printf("%s (%d) -> ", list->data->word, list->data->id);

        printf("NULL\n");
    }
}

void hash_table_remove(hash_table_t *table, const char *restrict key)
{
    unsigned int index = table->hash_foo(key) % HASH_TABLE_CAPACITY;

    value_list_t *head = table->values[index];
    value_list_t *prev = NULL;

    for ( ; head; head = head->next)
    {
        if (strcmp(head->data->word, key) == 0)
        {
            if (prev)
            {
                prev->next = head->next;
                return;
            }

            table->values[index] = head->next;
        }

        prev = head;
    }
}
