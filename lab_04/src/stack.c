#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include <sys/time.h>
#include "stack.h"

#define MAX_FREES_ALLOWED 1000

static int all_stacks_sz = 0;
static int max_all_stacks_sz = 0;

int stack_peek(my_stack_t *head)
{
    return head->value;
}

my_stack_t* stack_push(my_stack_t **head, int value)
{
    struct stack *new;

    if (all_stacks_sz + 1 > MAX_STACK_SZ)
    {
        printf("Stack overflow\n");
        *head = NULL;
        return NULL;
    }

    new = malloc(sizeof(struct stack));

    if (new == NULL)
        return NULL;

    new->value = value;
    new->prev = *head;
    *head = new;
    all_stacks_sz++;

    if (all_stacks_sz > max_all_stacks_sz)
        max_all_stacks_sz = all_stacks_sz;

    return new;
}

void stack_show_freed(my_stack_t *new)
{
    static struct stack *freed[MAX_FREES_ALLOWED];
    static int count = 0;

    if (new == NULL)
    {
        printf("\nFreed chunks in memory:\n");

        for (int i = 0; i < count; i++)
            printf("from %p to %p\n", freed[i], freed[i] + 1);

        return;
    }

    for (int i = 0; i < count; i++)
        if (new == freed[i])
            return;

    freed[count++] = new;
}

my_stack_t* stack_pop(my_stack_t **head)
{
    struct stack *new;

    if (head == NULL)
    {
        printf("Stack is empty\n");
        return NULL;
    }

    new = (*head)->prev;
    stack_show_freed(*head);
    free(*head);
    *head = new;
    all_stacks_sz--;

    return new;
}

void insert_in_stack(my_stack_t **head, int value)
{
    struct stack *stack = *head;
    struct stack *tmp = NULL;

    while (stack != NULL && stack_peek(stack) > value)
    {
        stack_push(&tmp, stack_peek(stack));
        stack_pop(&stack);
    }

    stack_push(&stack, value);

    while (tmp != NULL)
    {
        stack_push(&stack, stack_peek(tmp));
        stack_pop(&tmp);
    }

    *head = stack;
}

my_stack_t* stack_sort(my_stack_t **head)
{
    struct stack *new = NULL;

    while (*head != NULL)
    {
        int value = stack_peek(*head);
        insert_in_stack(&new, value);
        stack_pop(head);
    }

    return new;
}

my_stack_t* stack_merge(my_stack_t **first, my_stack_t **second)
{
    struct stack *new = NULL;

    while (*first != NULL && *second != NULL)
    {
        if (stack_peek(*first) >= stack_peek(*second))
        {
            stack_push(&new, stack_peek(*first));
            stack_pop(first);
        }
        else
        {
            stack_push(&new, stack_peek(*second));
            stack_pop(second);
        }
    }

    if (*first != NULL)
        while (*first != NULL)
        {
            stack_push(&new, stack_peek(*first));
            stack_pop(first);
        }

    if (*second != NULL)
        while (*second != NULL)
        {
            stack_push(&new, stack_peek(*second));
            stack_pop(second);
        }

    return new;
}

my_stack_t* stack_input()
{
    struct stack *stack = NULL;

    printf("Input stack mode\n\n");
    char user_input[128];

    do {
        printf("Input next value or NULL to stop: ");

        if (fgets(user_input, sizeof(user_input), stdin) == NULL)
            return NULL;

        if (user_input[strlen(user_input) - 1] != '\n')
            return NULL;

        user_input[strlen(user_input) - 1] = '\0';

        if (strcmp(user_input, "NULL") == 0)
            break;

        char *end;
        long value = strtol(user_input, &end, 10);

        if (end == user_input)
        {
            printf("Input error\n");
            continue;
        }

        if (value > INT_MAX)
        {
            printf("Value is too big\n");
            continue;
        }

        stack_push(&stack, (int)value);

        if (stack == NULL)
        {
            return NULL;
        }

    } while (1);

    return stack;
}

arr_stack_t *arr_stack_create()
{
    arr_stack_t *stack = malloc(sizeof(arr_stack_t));
    stack->count_in_stack = 0;

    return stack;
}

void arr_stack_free(arr_stack_t **stack)
{
    free (*stack);
}

arr_stack_t *arr_stack_push(arr_stack_t **stack, int value)
{
    if ((*stack)->count_in_stack + 1 > MAX_ARR_STACK_SZ)
    {
        printf("Stack overflow\n");
        return NULL;
    }

    (*stack)->values[((*stack)->count_in_stack)++] = value;

    return *stack;
}

arr_stack_t *arr_stack_pop(arr_stack_t **stack)
{
    if ((*stack)->count_in_stack > 0)
        ((*stack)->count_in_stack)--;
    else
        return NULL;

    return *stack;
}

int arr_stack_peek(arr_stack_t *stack)
{
    return (stack->values[stack->count_in_stack - 1]);
}

int stack_start()
{
    printf("Stack 1\n");
    my_stack_t *my_stack_1 = stack_input();

    if (my_stack_1 == NULL)
    {
        printf("Error occurred\n");
        return EXIT_FAILURE;
    }

    printf("\nStack 2\n");
    my_stack_t *my_stack_2 = stack_input();

    if (my_stack_2 == NULL)
    {
        printf("Error occurred\n");
        return EXIT_FAILURE;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

    my_stack_1 = stack_sort(&my_stack_1);
    my_stack_2 = stack_sort(&my_stack_2);

    my_stack_t *sorted = stack_merge(&my_stack_1, &my_stack_2);

    gettimeofday(&end, NULL);

    int64_t elapsed_time = (end.tv_sec - start.tv_sec) *
                           1000000LL + (end.tv_usec - start.tv_usec);

    printf("\nSorted! Here is what we got:\n");

    while (sorted != NULL)
    {
        printf("value = %d at %p\n", stack_peek(sorted), sorted);
        stack_pop(&sorted);
    }

    stack_show_freed(NULL);

    printf("\nSUMMARY\nTIME TAKEN:\t\t%10lld TICKS\nMEMORY TAKEN:\t%10lu BYTES",
           elapsed_time, sizeof(my_stack_t) * max_all_stacks_sz);

    return EXIT_SUCCESS;
}

arr_stack_t *arr_stack_expand(arr_stack_t **dest, arr_stack_t **src)
{
    while ((*src)->count_in_stack > 0)
    {
        arr_stack_push(dest, arr_stack_peek(*src));
        arr_stack_pop(src);
    }

    return *dest;
}

static int cmp(const void *first, const void *second)
{
    int *fir = (int*)first;
    int *sec = (int*)second;

    if (*fir > *sec)
        return -1;
    if (*fir == *sec)
        return 0;

    return 1;
}

void arr_stack_insert(arr_stack_t **head, int value)
{
    struct arr_stack *stack = *head;
    struct arr_stack *tmp = arr_stack_create();

    while (stack->count_in_stack != 0 && arr_stack_peek(stack) < value)
    {
        arr_stack_push(&tmp, arr_stack_peek(stack));
        arr_stack_pop(&stack);
    }

    arr_stack_push(&stack, value);

    while ((*tmp).count_in_stack != 0)
    {
        arr_stack_push(&stack, arr_stack_peek(tmp));
        arr_stack_pop(&tmp);
    }

    *head = stack;
}

arr_stack_t *arr_stack_sort(arr_stack_t **stack)
{
    arr_stack_t *new = arr_stack_create();

     while ((*stack)->count_in_stack != 0)
     {
         int value = arr_stack_peek(*stack);
         arr_stack_insert(&new, value);
         arr_stack_pop(stack);
     }

    return new;
}

arr_stack_t *arr_stack_input()
{
    arr_stack_t *stack = arr_stack_create();
    printf("Input stack mode\n\n");
    char user_input[128];

    do {
        printf("Input next value or NULL to stop: ");

        if (fgets(user_input, sizeof(user_input), stdin) == NULL)
            return NULL;

        if (user_input[strlen(user_input) - 1] != '\n')
            return NULL;

        user_input[strlen(user_input) - 1] = '\0';

        if (strcmp(user_input, "NULL") == 0)
            break;

        char *end;
        long value = strtol(user_input, &end, 10);

        if (end == user_input)
        {
            printf("Input error\n");
            continue;
        }

        if (value > INT_MAX)
        {
            printf("Value is too big\n");
            continue;
        }

        arr_stack_push(&stack, (int)value);
    } while (1);

    return stack;
}

int arr_stack_start()
{
    arr_stack_t *stack_1 = arr_stack_create();
    arr_stack_t *stack_2 = arr_stack_create();

    printf("Stack 1\n");
    stack_1 = arr_stack_input();

    if (stack_1 == NULL)
    {
        printf("An error occurred\n");
        return EXIT_FAILURE;
    }

    printf("Stack 2\n");
    stack_2 = arr_stack_input();

    if (stack_2 == NULL)
    {
        printf("An error occurred\n");
        return EXIT_FAILURE;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

    arr_stack_expand(&stack_1, &stack_2);
    stack_1 = arr_stack_sort(&stack_1);

    gettimeofday(&end, NULL);

    int64_t elapsed_time = (end.tv_sec - start.tv_sec) *
                    1000000LL + (end.tv_usec - start.tv_usec);

    printf("\nSorted! Here is what we got\n");

    while (stack_1->count_in_stack != 0)
    {
        printf("value = %d\n", arr_stack_peek(stack_1));
        arr_stack_pop(&stack_1);
    }

    arr_stack_free(&stack_1);
    arr_stack_free(&stack_2);

    printf("\nSUMMARY\nTIME TAKEN:\t\t%10lld TICKS\nMEMORY TAKEN:\t%10lu BYTES",
           elapsed_time, sizeof(arr_stack_t) * 2);

    return EXIT_SUCCESS;
}
