#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

my_stack_t* create_stack(int first_value)
{
    struct stack *stack;

    stack = malloc(sizeof(struct stack));

    if (stack == NULL)
        return NULL;

    stack->value = first_value;
    stack->prev = NULL;

    return stack;
}

int peek(my_stack_t *head)
{
    return head->value;
}

my_stack_t* push(my_stack_t **head, int value)
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

my_stack_t* pop(my_stack_t **head)
{
    struct stack *new;

    new = (*head)->prev;
    free(*head);
    *head = new;

    return new;
}

void insert_in_stack(my_stack_t **head, int value)
{
    struct stack *stack = *head;
    struct stack *next = NULL;

    while (value < peek(stack) && stack->prev != NULL)
    {
        next = stack;
        stack = stack->prev;
    }

    push(&stack, value);

    if (next != NULL)
        next->prev = stack;
    else
        *head = stack;
}

my_stack_t* sort(my_stack_t **head)
{
    struct stack *new = create_stack(0);

    while (*head != NULL)
    {
        int value = peek(*head);
        insert_in_stack(&new, value);
        pop(head);
    }

    return new;
}

my_stack_t* merge(my_stack_t **first, my_stack_t **second)
{
    struct stack *new = create_stack(0);

    while ((*first) != NULL && (*second) != NULL);
    {

    }
}

