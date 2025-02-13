#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "publication.h"

typedef struct {
    Publication *data;
    int capacity;
    int size;
} Stack;

void stack_init(Stack *stack);
void stack_push(Stack *stack, Publication value);
Publication stack_pop(Stack *stack);
Publication stack_peek(const Stack *stack);
bool stack_is_empty(const Stack *stack);
int stack_size(const Stack *stack);
void stack_free(Stack *stack);

Publication* stack_get_data(Stack *stack);


#endif