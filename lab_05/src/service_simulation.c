#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "queue.h"
#include "service_simulation.h"

#define TICK    1000000LL
#define SECOND  1000000000LL

#define MAX_FIRST_TYPE_HANDLING_UNITS 5
#define MAX_SECOND_TYPE_HANDLING_UNITS 5
#define MAX_FIRST_TYPE_GEN_UNITS 6

#define PRINT_INFO_GAP 100

static int time_first_type_handle()
{
    return rand() % MAX_FIRST_TYPE_HANDLING_UNITS;
}

static int time_second_type_handle()
{
    return rand() % MAX_SECOND_TYPE_HANDLING_UNITS;
}

static int time_first_type_generation()
{
    return rand() % MAX_FIRST_TYPE_GEN_UNITS;
}

#define WAIT_UNITS(units) { \
    long long __to_sleep = TICK * (long long)(units); \
    struct timespec __handle_time = { __to_sleep / SECOND, __to_sleep % SECOND}; \
    nanosleep(&__handle_time, NULL); \
}

static my_queue_t *queue;
static sim_info_t sim_info;

static void simulation_info_header()
{
    printf("+-----------------+--------------------+------------------+---------------------+---------------+-----------+----------------+\n");
    printf("| DONE FIRST TYPE | CREATED FIRST TYPE | DONE SECOND TYPE | CREATED SECOND TYPE | CURRENT QUEUE | AVG QUEUE | AVG QUEUE TIME |\n");
    printf("+-----------------+--------------------+------------------+---------------------+---------------+-----------+----------------+\n");
}

static void simulation_init()
{
    srand(time(NULL));
    queue = queue_create(NULL);
    queue = enqueue(queue, list_create(0, second, 0));
    sim_info.cur_queue = 1;
    sim_info.queue_sum = 0.0;
    sim_info.generated_first = 0;
    sim_info.handled_first = 0;
    sim_info.generated_second = 1;
    sim_info.handled_second = 0;
    sim_info.halt_time = 0;
    sim_info.gen_time = 0;
    sim_info.handle_time = 0;
    sim_info.first_wait_time = 0.0;
    simulation_info_header();
}

static void simulation_destruct()
{
    queue_free(queue);
}

static void simulation_print_report()
{
    printf("Simulation is done. Here is the final data:\n"
           "total simulation time:        %5d time units\n"
           "total halt time:              %5d time units\n"
           "handled first type requests:  %5d requests\n"
           "handled second type requests: %5d requests\n"
           "\n",
           (sim_info.gen_time > sim_info.handle_time) ? (sim_info.gen_time) : sim_info.handle_time,
           sim_info.halt_time, sim_info.handled_first, sim_info.handled_second);
}

static void simulation_print_info()
{
    printf("|%17d|%20d|%18d|%21d|%15d|%11lf|%16lf|\n",
           sim_info.handled_first, sim_info.generated_first,
           sim_info.handled_second, sim_info.generated_second,
           sim_info.cur_queue, sim_info.queue_sum / sim_info.generated_first,
           sim_info.first_wait_time / sim_info.handled_first);
    printf("+-----------------+--------------------+------------------+---------------------+---------------+-----------+----------------+\n");

//    printf("CURRENT QUEUE:     \t%5d requests\n"
//           "1ST TYPE GENERATED:\t%5d requests\n"
//           "1ST TYPE HANDLED:  \t%5d requests\n"
//           "2ND TYPE GENERATED:\t%5d requests\n"
//           "2ND TYPE HANDLED:  \t%5d requests\n"
//           "HALT TIME:         \t%5d units\n"
//           "HANDLE TIME:       \t%5d units\n"
//           "GEN TIME:          \t%5d units\n"
//           "AVG TIME IN QUEUE  \t%5lf units\n"
//           "AVG QUEUE          \t%5lf requests\n"
//           "\n",
//           sim_info.cur_queue, sim_info.generated_first,
//           sim_info.handled_first, sim_info.generated_second,
//           sim_info.handled_second, sim_info.halt_time, sim_info.handle_time,
//           sim_info.gen_time,
//           sim_info.first_wait_time / sim_info.handled_first,
//           sim_info.queue_sum / sim_info.generated_first);
}

#define MAX_2ND_TYPE_QUEUE_POS 4

static void insert_2nd_type()
{
    my_list_t *second_type_new = list_create(-sim_info.generated_second, second, 0);
    queue = insert_max_pos(queue, second_type_new, MAX_2ND_TYPE_QUEUE_POS);
    sim_info.generated_second++;
    sim_info.cur_queue++;
}

static void *req_handler(void *params)
{
    while (sim_info.handled_first < EXPECTED_FIRST_TYPE_REQUESTS)
    {
        if (is_empty(queue))
        {
            WAIT_UNITS(1)
            sim_info.halt_time += 1;
            continue;
        }

        my_list_t *request = dequeue(queue);

        // process req handling
        if (request->type == first)
        {
            int handle_time = time_first_type_handle();
            sim_info.handled_first++;
            sim_info.cur_queue--;
            WAIT_UNITS(handle_time);
            sim_info.handle_time += handle_time;
            sim_info.first_wait_time += sim_info.handle_time - request->start_time;

            if (sim_info.handled_first % PRINT_INFO_GAP == 0)
                simulation_print_info();
        }
        else
        {
            int handle_time = time_second_type_handle();
            sim_info.handled_second++;
            sim_info.cur_queue--;
            WAIT_UNITS(handle_time)
            sim_info.handle_time += handle_time;
            insert_2nd_type();
        }

        list_free(request);
    }

    pthread_exit(EXIT_SUCCESS);
}

static void *req_generator(void *params)
{
    while (sim_info.generated_first < EXPECTED_FIRST_TYPE_REQUESTS)
    {
        int gen_time = time_first_type_generation();

        WAIT_UNITS(gen_time)

        enqueue(queue, list_create(sim_info.generated_first, first,
                                   sim_info.gen_time + gen_time));
        sim_info.queue_sum += sim_info.cur_queue;
        sim_info.generated_first++;
        sim_info.cur_queue++;
        sim_info.gen_time += gen_time;
    }

    pthread_exit(EXIT_SUCCESS);
}

int simulation_start()
{
    simulation_init();

    pthread_t handler;
    pthread_attr_t handler_attr;
    pthread_t generator;
    pthread_attr_t generator_attr;

    pthread_attr_init(&handler_attr);
    pthread_create(&handler, &handler_attr, req_handler, NULL);

    pthread_attr_init(&generator_attr);
    pthread_create(&generator, &generator_attr, req_generator, NULL);

    pthread_join(generator, NULL);
    pthread_join(handler, NULL);

    simulation_print_report();

    simulation_destruct();

    return EXIT_SUCCESS;
}
