#include <stdio.h>
#include <stdlib.h>
#include "../inc/subscriber.h"

int main(void)
{
    setbuf(stdout, NULL);
    int error;

    subscriber_t sub;

    if ((error = input_subscriber(&sub)) != EXIT_SUCCESS)
        return error;

    print_subscriber(sub);

    return EXIT_SUCCESS;
}
