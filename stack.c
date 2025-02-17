#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void stack_init(Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

void stack_push(Stack *stack, Publication value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed in stack_push.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

Publication stack_pop(Stack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "Stack is empty, cannot pop.\n");
        Publication emptyPub = {"", "", "", "", 0, 0, false, 0, 0};
        return emptyPub;
    }

    Node *temp = stack->top;
    Publication value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return value;
}

Publication stack_peek(const Stack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "Stack is empty, cannot peek.\n");
        Publication emptyPub = {"", "", "", "", 0, 0, false, 0, 0};
        return emptyPub;
    }
    return stack->top->data;
}

bool stack_is_empty(const Stack *stack) {
    return stack->top == NULL;
}

int stack_size(const Stack *stack) {
    return stack->size;
}

void stack_free(Stack *stack) {
    Node *current = stack->top;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    stack->top = NULL;
    stack->size = 0;
}

