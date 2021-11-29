#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

my_list_t *list_create(int id, type_t type, int start_time)
{
    my_list_t *list = malloc(sizeof(my_list_t));

    if (list == NULL)
        return NULL;

    list->id = id;
    list->type = type;
    list->start_time = start_time;
    list->next = NULL;

    return list;
}

void list_free(my_list_t *list)
{
    free(list);
}

void list_free_all(my_list_t *list)
{
    while (list)
    {
        my_list_t *prev = list;
        list = list->next;
        list_free(prev);
    }
}

my_queue_t *queue_create(my_list_t *elem)
{
    my_queue_t *queue = malloc(sizeof(my_queue_t));

    if (queue == NULL)
        return NULL;

    queue->head = elem;
    queue->tail = elem;

    return queue;
}

void queue_free(my_queue_t *queue)
{
    list_free_all(queue->head);
    free(queue);
}

my_queue_t *enqueue(my_queue_t *queue, my_list_t *elem)
{
    if (queue->tail== NULL)
    {
        queue->head = elem;
        queue->tail = elem;

        return queue;
    }

    queue->tail->next = elem;
    queue->tail = queue->tail->next;

    return queue;
}

my_queue_t *insert_max_pos(my_queue_t *queue, my_list_t *elem, const int pos)
{
    if (queue->head == NULL)
    {
        queue = enqueue(queue, elem);
        return queue;
    }

    my_list_t *head = queue->head;

    for (int i = 0; i < pos - 2 && head->next; i++, head = head->next);

    elem->next = head->next;
    head->next = elem;

    if (elem->next == NULL)
        queue->tail = elem;

    return queue;
}

my_list_t *dequeue(my_queue_t *queue)
{
    if (queue->head == NULL)
        return NULL;

    my_list_t *elem = queue->head;

    if (queue->head == queue->tail)
        queue->head = queue->tail = NULL;
    else
        queue->head = queue->head->next;

    return elem;
}

void print_queue(my_queue_t *queue)
{
    my_list_t *head = queue->head;

    for (int i = 0; head; i++, head = head->next)
        printf("POSITION = %d; id = %d;\n", i, head->id);
}

int is_empty(my_queue_t *queue)
{
    if (queue->head == NULL)
        return 1;

    return 0;
}
