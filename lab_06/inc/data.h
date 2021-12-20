#ifndef _DATA_H_
#define _DATA_H_

#define WORD_LNG 30

typedef struct
{
    unsigned int id;
    char word[WORD_LNG];
} data_t;

data_t *data_create(char *word);
void data_free(data_t *data);
void data_print(data_t *data);

#endif
