#include <stdio.h>
#include <stdlib.h>
#include <stack.h>

int main(void)
{
    my_stack_t *my_stack = create_stack(1);

    push(&my_stack, 3);
    push(&my_stack, 7);
    push(&my_stack, 5);
    push(&my_stack, 2);
    push(&my_stack, 4);
    push(&my_stack, 6);

    my_stack = sort(&my_stack);

    while (my_stack != NULL)
    {
        printf("%d\n", peek(my_stack));
        pop(&my_stack);
    }

    return EXIT_SUCCESS;
}
