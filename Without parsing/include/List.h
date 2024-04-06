#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    struct Node *prev;
    int coeff;
    int deg;
    struct Node *next;
} List;

/*** inquire in list ***/

int empty_list(List **list) {
    return *list == NULL;
}

int size_list(List **list) {
    List *temp = *list;
    int size = 0;

    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}

List * front(List **list) {
    return *list;
}

List * back(List **list) {
    List *temp = *list;
    while (temp->next != NULL) temp = temp->next;
    return temp;
}

/*** make changes in list ***/

List * createNode(int coeff, int deg) {
    List *node = (List *)malloc(sizeof(List));
    if (!node) return NULL;

    node->prev = NULL;
    node->coeff = coeff;
    node->deg = deg;
    node->next = NULL;
    return node;
}

int push_front(List **list, int coeff, int deg) {
    List *node = createNode(coeff, deg);
    if (!node) return 1;

    if (empty_list(list)) {
        *list = node;
    } else {
        node->next = *list;
        (*list)->prev = node;
        *list = node;
    }
    return 0;
}

int push_back(List **list, int coeff, int deg) {
    List *node = createNode(coeff, deg);
    if (!node) return 1;

    if (empty_list(list)) {
        *list = node;
    } else {
        List *temp = *list;
        while (temp->next != NULL) temp = temp->next;
        temp->next = node;
        node->prev = temp;
    }

    return 0;
}

void pop_front(List **list) {
    if (empty_list(list)) return;

    *list = (*list)->next;
    (*list)->prev->next = NULL;
    free((*list)->prev);
    (*list)->prev = NULL;
}

void pop_back(List **list) {
    if (empty_list(list)) return;

    List *temp = *list;
    while (temp->next->next != NULL) temp = temp->next;
    temp->next->prev = NULL;
    free(temp->next);
    temp->next = NULL;
}

/*** view list ***/

void print_list(List **list) {
    if (empty_list(list)) return;

    List *temp = *list;

    printf("Coefficient\tDegree\n");
    while (temp != NULL) {
        printf("%d\t%d\n", temp->coeff, temp->deg);
        temp = temp->next;
    }
}