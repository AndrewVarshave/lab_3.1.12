#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

int read_stack_from_csv(Stack *stack, const char *filename);
void write_stack_to_csv(const Stack *stack, const char *filename);
void print_stack_csv(const Stack *stack, FILE *stream);
void print_stack_table(const Stack *stack, FILE *stream);

#endif