#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <pthread.h>
#include "queue.h"
#include "arr_queue.h"
#include "service_simulation.h"

#define TICK    1000000LL
#define SECOND  1000000000LL

#define MAX_2ND_TYPE_QUEUE_POS 4

#define PRINT_INFO_GAP 100

static my_queue_t *queue;
static arr_queue_t *arr_queue;
static sim_info_t sim_info;

static int max_first_handling_time;
static int max_second_handling_time;
static int max_first_gen_time;

void set_simulation_parameters(const int first_type_handling_time,
                               const int second_type_handling_time,
                               const int first_type_gen_time)
{
    max_first_handling_time = first_type_handling_time;
    max_second_handling_time = second_type_handling_time;
    max_first_gen_time = first_type_gen_time;
}

static int time_first_type_handle()
{
    return rand() % (max_first_handling_time + 1);
}

static int time_second_type_handle()
{
    return rand() % (max_second_handling_time + 1);
}

static int time_first_type_generation()
{
    return rand() % (max_first_gen_time + 1);
}

static void wait_units(const int units)
{
    long long to_sleep = TICK * (long long)(units);
    struct timespec handle_time = { to_sleep / SECOND, to_sleep % SECOND};
    nanosleep(&handle_time, NULL);
}

static double count_sim_time()
{
    double avg_first_handling_time = (double)max_first_handling_time / 2.0;
    double avg_second_handling_time = (double)max_second_handling_time / 2.0;

    double avg_first_gen_time = (double)max_first_gen_time / 2.0;

    double total_gen_time = avg_first_gen_time * avg_first_gen_time;
    double total_handling_time = avg_first_handling_time * EXPECTED_FIRST_TYPE_REQUESTS +
            (1.0 / 3.0) * EXPECTED_FIRST_TYPE_REQUESTS * avg_second_handling_time;

    return (total_handling_time > total_gen_time) ? total_handling_time : total_gen_time;
}

static void simulation_print_report()
{
    printf("+----------------------------------------------------------+\n");
    printf("|             SIMULATION IS DONE. FINAL REPORT             |\n");


    // +32+10+15+
    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "EXPECTED TIME");
    printf("|%10.1lf", sim_info.expected_sim_time);
    printf("|%14s|\n", "time units");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "SIMULATION TIME");
    printf("|%10.1d", (sim_info.gen_time > sim_info.handle_time) ? (sim_info.gen_time) : sim_info.handle_time);
    printf("|%14s|\n", "time units");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "EXPECTED AND SIMULATION DIFF");
    printf("|%10.1lf", (((sim_info.gen_time > sim_info.handle_time) ? (sim_info.gen_time) : sim_info.handle_time) / sim_info.expected_sim_time - 1.0) * 100.0);
    printf("|%14s|\n", "%");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "HALT TIME");
    printf("|%10d", sim_info.halt_time);
    printf("|%14s|\n", "time units");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "HANDLED FIRST TYPE");
    printf("|%10d", sim_info.handled_first);
    printf("|%14s|\n", "time units");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "HANDLED SECOND TYPE");
    printf("|%10d", sim_info.handled_second);
    printf("|%14s|\n", "time units");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "LIST QUEUE TIME TAKEN");
    printf("|%10lld", sim_info.time_taken_list);
    printf("|%14s|\n", "ticks");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "LIST QUEUE MEMORY TAKEN");
    printf("|%10lu", sizeof(struct queue) + sizeof(my_list_t) * sim_info.max_queue);
    printf("|%14s|\n", "bytes");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "ARR QUEUE TIME TAKEN");
    printf("|%10lld", sim_info.time_taken_arr);
    printf("|%14s|\n", "ticks");

    printf("+--------------------------------+----------+--------------+\n");

    printf("|%32s", "ARR QUEUE MEMORY TAKEN");
    printf("|%10lu", sizeof(arr_queue_t));
    printf("|%14s|\n", "bytes");

    printf("+--------------------------------+----------+--------------+\n");
}

static void simulation_print_info()
{
    printf("|%17d|%20d|%18d|%21d|%15d|%11lf|%16lf|\n",
           sim_info.handled_first, sim_info.generated_first,
           sim_info.handled_second, sim_info.generated_second,
           sim_info.cur_queue, sim_info.queue_sum / sim_info.generated_first,
           sim_info.first_wait_time / sim_info.handled_first);
    printf("+-----------------+--------------------+------------------+---------------------+---------------+-----------+----------------+\n");
}

static void simulation_info_header()
{
    printf("+-----------------+--------------------+------------------+---------------------+---------------+-----------+----------------+\n");
    printf("| DONE FIRST TYPE | CREATED FIRST TYPE | DONE SECOND TYPE | CREATED SECOND TYPE | CURRENT QUEUE | AVG QUEUE | AVG QUEUE TIME |\n");
    printf("+-----------------+--------------------+------------------+---------------------+---------------+-----------+----------------+\n");
}

static void simulation_init()
{
    srand(time(NULL));
    set_simulation_parameters(4, 4, 5);

    queue = queue_create(NULL);
    arr_queue = arr_queue_create();

    request_t request = { 0, 0, second };
    queue = enqueue(queue, list_create(0, second, 0));
    arr_queue = arr_enqueue(arr_queue, request);

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
    sim_info.expected_sim_time = count_sim_time();
    sim_info.time_taken_list = 0;
    sim_info.time_taken_arr = 0;
    sim_info.max_queue = 1;
    simulation_info_header();
}

static void simulation_destruct()
{
    queue_free(queue);
    arr_queue_free(arr_queue);
}

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
            wait_units(1);
            sim_info.halt_time += 1;
            continue;
        }

        struct timeval start_list, end_list;
        gettimeofday(&start_list, NULL);
        my_list_t *request = dequeue(queue);
        gettimeofday(&end_list, NULL);
        sim_info.time_taken_list += (end_list.tv_sec - start_list.tv_sec) *
                                    1000000LL + (end_list.tv_usec - start_list.tv_usec);

        struct timeval start_arr, end_arr;
        gettimeofday(&start_arr, NULL);
        request_t request_arr = arr_dequeue(arr_queue);
        gettimeofday(&end_arr, NULL);
        sim_info.time_taken_arr += (end_arr.tv_sec - start_arr.tv_sec) *
                                   1000000LL + (end_arr.tv_usec - start_arr.tv_usec);

        // process req handling
        if (request->type == first)
        {
            int handle_time = time_first_type_handle();
            sim_info.handled_first++;
            sim_info.cur_queue--;

            wait_units(handle_time);

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

            wait_units(handle_time);

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

        wait_units(gen_time);

        struct timeval start_list, end_list;
        gettimeofday(&start_list, NULL);
        enqueue(queue, list_create(sim_info.generated_first, first,
                                   sim_info.gen_time + gen_time));
        gettimeofday(&end_list, NULL);
        sim_info.time_taken_list += (end_list.tv_sec - start_list.tv_sec) *
                                    1000000LL + (end_list.tv_usec - start_list.tv_usec);

        struct timeval start_arr, end_arr;
        request_t request = { sim_info.generated_first, sim_info.gen_time + gen_time, first};
        gettimeofday(&start_arr, NULL);
        arr_enqueue(arr_queue, request);
        gettimeofday(&end_arr, NULL);
        sim_info.time_taken_arr += (end_arr.tv_sec - start_arr.tv_sec) *
                1000000LL + (end_arr.tv_usec - start_arr.tv_usec);

        sim_info.queue_sum += sim_info.cur_queue;
        sim_info.generated_first++;
        sim_info.cur_queue++;
        sim_info.gen_time += gen_time;

        if (sim_info.max_queue < sim_info.cur_queue)
            sim_info.max_queue = sim_info.cur_queue;
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
