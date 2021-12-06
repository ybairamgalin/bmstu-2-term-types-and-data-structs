#ifndef _SERVICE_SIMULATION_H_
#define _SERVICE_SIMULATION_H_

#define EXPECTED_FIRST_TYPE_REQUESTS 1000

typedef struct sim_info sim_info_t;

struct sim_info
{
    double expected_sim_time;
    int cur_queue;
    double queue_sum;
    int generated_first;
    int handled_first;
    int generated_second;
    int handled_second;
    double first_wait_time;
    int gen_time;
    int handle_time;
    int halt_time;
};

int simulation_start();

#endif
