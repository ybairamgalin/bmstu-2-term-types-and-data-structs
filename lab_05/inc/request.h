#ifndef _REQUEST_H_
#define _REQUEST_H_

enum type
{
    first,
    second
};

typedef enum type type_t;

struct request {
    int id;
    int start_time;
    type_t type;
};

typedef struct request request_t;

request_t request_create(int id, int start_time, type_t type);


#endif
