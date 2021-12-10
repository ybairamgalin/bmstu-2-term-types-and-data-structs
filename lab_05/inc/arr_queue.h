#ifndef _ARR_QUEUE_H_
#define _ARR_QUEUE_H_

#define QUEUE_CAPACITY 1010

#include "request.h"

struct arr_queue {
    request_t values[QUEUE_CAPACITY];
    request_t *head;
    request_t *tail;
};

typedef struct arr_queue arr_queue_t;

arr_queue_t *arr_queue_create();
void arr_queue_free(arr_queue_t *queue);

request_t arr_dequeue(arr_queue_t *queue);
arr_queue_t *arr_enqueue(arr_queue_t *queue, request_t elem);

#endif
