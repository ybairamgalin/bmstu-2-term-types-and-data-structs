#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data.h"

static unsigned int cur_id = 0;

data_t *data_create(char *word)
{
    data_t *data = malloc(sizeof(data_t));

    if (data == NULL)
        return NULL;

    strcpy(data->word, word);
    data->id = cur_id++;

    return data;
}

void data_free(data_t *data)
{
    free(data);
}

void data_print(data_t *data)
{
    if (!data)
    {
        printf("Nothing found\n\n");
        return;
    }

    printf("Found: id = %d, str = %s\n\n", data->id, data->word);
}
