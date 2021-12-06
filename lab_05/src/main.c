#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "service_simulation.h"

#include "arr_queue.h"
#include "request.h"

int main(void)
{
//    arr_queue_t *queue = arr_queue_create();
//
//    request_t req1 = { 1, 10, first};
//    request_t req2 = { 2, 20, first};
//    request_t req3 = { 3, 30, first};
//    request_t req4 = { 4, 40, first};
//
//    queue = arr_enqueue(queue, req1);
//    queue = arr_enqueue(queue, req2);
//    queue = arr_enqueue(queue, req3);
//    queue = arr_enqueue(queue, req4);
//
//    request_t old = arr_dequeue(queue);
//    old = arr_dequeue(queue);
//    old = arr_dequeue(queue);
//    old = arr_dequeue(queue);
//
//    old.start_time == 0;

    simulation_start();

    return EXIT_SUCCESS;
}
