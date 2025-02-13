#ifndef SORT_H
#define SORT_H

#include "stack.h"
#include "publication.h"

typedef int (*CompareFunc)(const Publication *a, const Publication *b);

void gnome_sort(Stack *stack, CompareFunc compare);
void gnome_sort_desc(Stack *stack, CompareFunc compare);

#endif