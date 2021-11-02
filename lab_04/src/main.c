#include <stdio.h>
#include <stdlib.h>
#include <stack.h>

int main(void)
{
    my_stack_t *my_stack_1 = NULL;
    my_stack_t *my_stack_2 = NULL;

    push(&my_stack_1, 1);
    push(&my_stack_1, 3);
    push(&my_stack_1, 7);
    push(&my_stack_1, 5);
    push(&my_stack_1, 2);
    push(&my_stack_1, 4);
    push(&my_stack_1, 6);
    push(&my_stack_1, 11);
    push(&my_stack_1, 12);
    push(&my_stack_1, 13);

    push(&my_stack_2, 1);
    push(&my_stack_2, 6);
    push(&my_stack_2, 4);
    push(&my_stack_2, 2);
    push(&my_stack_2, 5);
    push(&my_stack_2, 7);
    push(&my_stack_2, 3);
    push(&my_stack_2, 10);
    push(&my_stack_2, 14);

    my_stack_1 = sort(&my_stack_1);
    my_stack_2 = sort(&my_stack_2);

    my_stack_t *merged;
    merged = merge(&my_stack_1, &my_stack_2);

    while (merged != NULL)
    {
        printf("%d\n", peek(merged));
        pop(&merged);
    }

    return EXIT_SUCCESS;
}
