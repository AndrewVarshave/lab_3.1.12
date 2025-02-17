#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

Publication stack_get(const Stack *stack, int index){
    Node* current = stack->top;
    int current_index = stack->size - 1;

    while(current != NULL){
        if(current_index == index){
            return current->data;
        }
        current = current->next;
        current_index--;
    }

    Publication emptyPub = {"", "", "", "", 0, 0, false, 0, 0};
    return emptyPub;
}

void stack_swap(Stack *stack, int index1, int index2) {
    if (index1 < 0 || index1 >= stack->size || index2 < 0 || index2 >= stack->size) {
        fprintf(stderr, "Error: Index out of bounds in stack_swap.\n");
        return;
    }
    
    Node *node1 = stack->top;
    int i = stack->size - 1;
    while (node1 != NULL && i != index1) {
        node1 = node1->next;
        i--;
    }

    Node *node2 = stack->top;
    i = stack->size - 1;
    while (node2 != NULL && i != index2) {
        node2 = node2->next;
        i--;
    }


    if(node1 == NULL || node2 == NULL) return;
    Publication tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;


}


void gnome_sort(Stack *stack, CompareFunc compare) {
    int size = stack_size(stack);
    int i = 0;

    while (i < size) {
        if (i == 0 || compare(stack_get(stack, i), stack_get(stack, i - 1)) >= 0) {
            i++;
        } else {
            stack_swap(stack, i, i - 1);
            i--;
        }
    }
}