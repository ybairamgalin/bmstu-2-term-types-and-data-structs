#include <stdlib.h>
#include "request.h"

request_t request_create(int id, int start_time, type_t type)
{
    request_t request = { id, start_time, type };
    return request;
}
