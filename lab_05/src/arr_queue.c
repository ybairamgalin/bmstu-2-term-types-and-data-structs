#include <stdio.h>
#include <stdlib.h>
#include "arr_queue.h"

arr_queue_t *arr_queue_create()
{
    arr_queue_t *queue = malloc(sizeof(arr_queue_t));

    if (queue == NULL)
        return NULL;

    queue->head = queue->values;
    queue->tail = queue->values;

    return queue;
}

void arr_queue_free(arr_queue_t *queue)
{
    free(queue);
}


request_t arr_dequeue(arr_queue_t *queue)
{
    request_t req = { 0, -1, first};

    if (queue->tail == queue->head)
        return req;

    req = *(queue->head);
    queue->head++;

    if (queue->head >= queue->values + QUEUE_CAPACITY)
        queue->head = queue->values;

    return req;
}

arr_queue_t *arr_enqueue(arr_queue_t *queue, request_t elem)
{
    if (queue == NULL)
        return NULL;

    *(queue->tail) = elem;
    queue->tail++;

    // tail to start when overflow happens
    if (queue->tail >= queue->values + QUEUE_CAPACITY)
        queue->tail = queue->values;

    if (queue->tail == queue->head)
    {
        fprintf(stderr, "arr_enqueue -> overflow occurred\n");
        arr_queue_free(queue);
        exit(1);
    }

    return queue;
}
