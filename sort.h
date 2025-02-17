#ifndef SORT_H
#define SORT_H

#include "stack.h"
#include "publication.h"

typedef int (*CompareFunc)(Publication a, Publication b);

void gnome_sort(Stack *stack, CompareFunc compare);

#endif