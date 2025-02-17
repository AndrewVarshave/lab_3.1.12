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
/*#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10

void stack_init(Stack *stack) {
    stack->data = (Publication*)malloc(INITIAL_CAPACITY * sizeof(Publication));
    if (stack->data == NULL) {
        fprintf(stderr, "Memory allocation failed in stack_init.\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = INITIAL_CAPACITY;
    stack->size = 0;
}

void stack_push(Stack *stack, Publication value) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        Publication *temp = (Publication*)realloc(stack->data, stack->capacity * sizeof(Publication));
        if (temp == NULL) {
            fprintf(stderr, "Memory reallocation failed in stack_push.\n");
            exit(EXIT_FAILURE);
        }
        stack->data = temp;
    }
    stack->data[stack->size] = value;
    stack->size++;
}

Publication stack_pop(Stack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "Stack is empty, cannot pop.\n");
        Publication emptyPub = {"", "", "", "", 0, 0, false, 0, 0};
        return emptyPub;
    }
    stack->size--;
    return stack->data[stack->size];
}

Publication stack_peek(const Stack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "Stack is empty, cannot peek.\n");
        Publication emptyPub = {"", "", "", "", 0, 0, false, 0, 0};
        return emptyPub;
    }
    return stack->data[stack->size - 1];
}

bool stack_is_empty(const Stack *stack) {
    return stack->size == 0;
}

int stack_size(const Stack *stack) {
    return stack->size;
}

void stack_free(Stack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}

Publication* stack_get_data(Stack *stack) {
    return stack->data;
}*/
