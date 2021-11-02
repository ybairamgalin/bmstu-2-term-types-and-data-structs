#ifndef _STACK_
#define _STACK_

struct stack {
    int value;
    struct stack* prev;
};

typedef struct stack my_stack_t;

my_stack_t* create_stack(int first_value);
my_stack_t* pop(my_stack_t **head);
my_stack_t* push(my_stack_t **head, int value);
int peek(my_stack_t *head);
my_stack_t* sort(my_stack_t **head);

#endif
