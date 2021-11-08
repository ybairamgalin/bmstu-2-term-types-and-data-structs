#ifndef _STACK_H_
#define _STACK_H_

#define MAX_ARR_STACK_SZ 100

struct stack {
    int value;
    struct stack *prev;
};

struct arr_stack {
    int values[MAX_ARR_STACK_SZ];
    int count_in_stack;
};

typedef struct stack my_stack_t;
typedef struct arr_stack arr_stack_t;

my_stack_t* stack_pop(my_stack_t **head);
my_stack_t* stack_push(my_stack_t **head, int value);
int stack_peek(my_stack_t *head);
my_stack_t* stack_sort(my_stack_t **head);
my_stack_t* stack_merge(my_stack_t **first, my_stack_t **second);
my_stack_t* stack_input();
void stack_show_freed(my_stack_t *new);
int stack_start();
int arr_stack_start();

#endif
