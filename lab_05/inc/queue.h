#ifndef _QUEUE_H_
#define _QUEUE_H_

struct list
{
    void *data;
    struct list *next;
};

typedef struct list my_list_t;

struct queue
{
    my_list_t *head;
    my_list_t *tail;
};

typedef struct queue my_queue_t;

my_queue_t *queue_create();
my_queue_t *enqueue(my_queue_t *queue, my_list_t *elem);
my_queue_t *dequeue(my_queue_t *queue);

#endif
