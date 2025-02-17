#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

// Вспомогательная функция для вставки узла на правильную позицию в отсортированном списке
void sorted_insert(Stack *stack, Node *newNode, CompareFunc compare) {
    if (stack->top == NULL || compare(newNode->data, stack->top->data) <= 0) {
        newNode->next = stack->top;
        stack->top = newNode;
    } else {
        Node *current = stack->top;
        while (current->next != NULL && compare(newNode->data, current->next->data) > 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void gnome_sort(Stack *stack, CompareFunc compare) { // теперь это insertion sort
    Stack sortedStack;
    stack_init(&sortedStack);

    Node *current = stack->top;
    while (current != NULL) {
        Node *next = current->next; // Сохраняем следующий, потому что current изменится
        sorted_insert(&sortedStack, current, compare);
        current = next;
    }

    // Обновляем исходный стек отсортированными узлами
    stack->top = sortedStack.top;
    stack->size = sortedStack.size;
}

// Вспомогательная функция для вставки узла на правильную позицию в отсортированном в обратном порядке списке
void sorted_insert_desc(Stack *stack, Node *newNode, CompareFunc compare) {
    if (stack->top == NULL || compare(newNode->data, stack->top->data) >= 0) {
        newNode->next = stack->top;
        stack->top = newNode;
    } else {
        Node *current = stack->top;
        while (current->next != NULL && compare(newNode->data, current->next->data) < 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void gnome_sort_desc(Stack *stack, CompareFunc compare) { // теперь это insertion sort desc
     Stack sortedStack;
    stack_init(&sortedStack);

    Node *current = stack->top;
    while (current != NULL) {
        Node *next = current->next; // Сохраняем следующий, потому что current изменится
        sorted_insert_desc(&sortedStack, current, compare);
        current = next;
    }

    // Обновляем исходный стек отсортированными узлами
    stack->top = sortedStack.top;
    stack->size = sortedStack.size;
}
/*#include "sort.h"
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
}*/