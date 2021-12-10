#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct list my_list_t;

#include "request.h"

struct list
{
    int id;
    type_t type;
    int start_time;
    struct list *next;
};

typedef struct queue my_queue_t;

struct queue
{
    my_list_t *head;
    my_list_t *tail;
};





my_queue_t *queue_create(my_list_t *elem);
void queue_free(my_queue_t *queue);

my_queue_t *enqueue(my_queue_t *queue, my_list_t *elem);
my_list_t *dequeue(my_queue_t *queue);
my_queue_t *insert_max_pos(my_queue_t *queue, my_list_t *elem, const int pos);

int is_empty(my_queue_t *queue);
void print_queue(my_queue_t *queue);

my_list_t *list_create(int id, type_t type, int start_time);
void list_free_all(my_list_t *list);
void list_free(my_list_t *list);

#endif
