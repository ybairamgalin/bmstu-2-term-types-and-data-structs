#include <stdlib.h>
#include "queue.h"

my_queue_t *queue_create()
{
    my_queue_t *queue = malloc(sizeof(my_queue_t));

    if (queue == NULL)
        return NULL;

    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

my_queue_t *enqueue(my_queue_t *queue, my_list_t *elem)
{
    if (queue->head == NULL)
}

my_queue_t *dequeue(my_queue_t *queue)
{

}