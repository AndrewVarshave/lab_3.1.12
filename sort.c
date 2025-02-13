#include "sort.h"
#include <stdio.h>

void swap(Stack *stack, int i, int j) {
    Publication *data = stack_get_data(stack);
    Publication temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}


void gnome_sort(Stack *stack, CompareFunc compare) {
    int size = stack_size(stack);
    Publication *data = stack_get_data(stack);

    int i = 1;

    while (i < size) {
        if (compare(&data[i], &data[i - 1]) >= 0) {
            i++;
        } else {
            swap(stack, i, i - 1);
            if (i > 1) {
                i--;
            } else {
                i = 1;
            }
        }
    }
}

void gnome_sort_desc(Stack *stack, CompareFunc compare) {
      int size = stack_size(stack);
    Publication *data = stack_get_data(stack);

    int i = 1;

    while (i < size) {
        if (compare(&data[i], &data[i - 1]) <= 0) {
            i++;
        } else {
            swap(stack, i, i - 1);
            if (i > 1) {
                i--;
            } else {
                i = 1;
            }
        }
    }
}