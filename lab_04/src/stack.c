#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "stack.h"

#define MAX_FREES_ALLOWED 1000

int stack_peek(my_stack_t *head)
{
    return head->value;
}

my_stack_t* stack_push(my_stack_t **head, int value)
{
    struct stack *new;

    new = malloc(sizeof(struct stack));

    if (new == NULL)
        return NULL;

    new->value = value;
    new->prev = *head;
    *head = new;

    return new;
}

void stack_show_freed(my_stack_t *new)
{
    static struct stack *freed[MAX_FREES_ALLOWED];
    static int count = 0;

    if (new == NULL)
    {
        printf("\nFreed zones in memory:\n");

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

    new = (*head)->prev;
    stack_show_freed(*head);
    free(*head);
    *head = new;

    return new;
}

void insert_in_stack(my_stack_t **head, int value)
{
    struct stack *stack = *head;
    struct stack *next = NULL;
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
        printf("Stack overflow");
        return NULL;
    }

    (*stack)->values[((*stack)->count_in_stack)++] = value;

    return *stack;
}

arr_stack_t *arr_stack_pop(arr_stack_t **stack)
{
    if ((*stack)->count_in_stack > 0)
        ((*stack)->count_in_stack)--;

    return *stack;
}

int arr_stack_peek(arr_stack_t *stack)
{
    return (stack->values[stack->count_in_stack]);
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

    my_stack_1 = stack_sort(&my_stack_1);
    my_stack_2 = stack_sort(&my_stack_2);

    my_stack_t *sorted = stack_merge(&my_stack_1, &my_stack_2);

    printf("\nSorted! Here is what we got:\n");

    while (sorted != NULL)
    {
        printf("value = %d at %p\n", stack_peek(sorted), sorted);
        stack_pop(&sorted);
    }

    stack_show_freed(NULL);

    return EXIT_SUCCESS;
}
