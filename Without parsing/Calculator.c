#include "./include/List.h"
#include <stdio.h>
#include <math.h>

void exit_program(char *ch) {
    printf("%s", ch);
    exit(1);
}

void input_polynomial(List **list) {
    int max_deg, deg, coeff;

    printf("Enter highest degree: ");
    scanf("%d", &max_deg);
    if (max_deg >= 0) {
        for (deg = max_deg; deg >= 0; --deg) {
            printf("Coeff of x^%d: ", deg);
            scanf("%d", &coeff);
            push_back(list, coeff, deg);
        }
    } else {
        exit_program("Invalid degree!");
    }
}

void print_polynomial(List **list) {
    if (empty_list(list)) {
        printf("Empty list!\n");
        return;
    }

    List *itr = front(list);
    int no_coeff, size;

    no_coeff = 1;
    size = size_list(list);

    while (itr != NULL) {
        if (itr->coeff != 0) no_coeff = 0;  // if any coeff is not zero
        if (!no_coeff) {
            if (itr->deg == size - 1 && itr->coeff > 0)
                printf(" ");
            else if (itr->coeff > 0)
                printf(" +");
            else if (itr->coeff < 0)
                printf(" -");
            else
                continue;
            
            if (itr->deg == 0)
                printf("%d", abs(itr->coeff));
            else if (itr->deg == 1)
                printf("%dx", abs(itr->coeff));
            else
                printf("%dx^%d", abs(itr->coeff), itr->deg);
        }
        itr = itr->next;
    }
    if (no_coeff) printf("0");
    printf("\n");
}

List * add_polynomial(List **list1, List **list2) {
    List *sum = NULL;
    List *itr1, *itr2;

    itr1 = back(list1);
    itr2 = back(list2);

    while (itr1 != NULL && itr2 != NULL) {
        push_front(&sum, itr1->coeff + itr2->coeff, itr1->deg);
        itr1 = itr1->prev;
        itr2 = itr2->prev;
    }
    while (itr1 != NULL) {
        push_front(&sum, itr1->coeff, itr1->deg);
        itr1 = itr1->prev;
    }
    while (itr2 != NULL) {
        push_front(&sum, itr2->coeff, itr2->deg);
        itr2 = itr2->prev;
    }

    return sum;
}

List * sub_polynomial(List **list1, List **list2) {
    List *diff = NULL;
    List *itr1, *itr2;

    itr1 = back(list1);
    itr2 = back(list2);

    while (itr1 != NULL && itr2 != NULL) {
        push_front(&diff, itr1->coeff - itr2->coeff, itr1->deg);
        itr1 = itr1->prev;
        itr2 = itr2->prev;
    }
    while (itr1 != NULL) {
        push_front(&diff, itr1->coeff, itr1->deg);
        itr1 = itr1->prev;
    }
    while (itr2 != NULL) {
        push_front(&diff, -itr2->coeff, itr2->deg);
        itr2 = itr2->prev;
    }

    return diff;
}

List * mul_polynomial(List **list1, List **list2) {
    List *prod = NULL;
    List *itr1, *itr2, *itr;
    int max_deg, i;

    max_deg = front(list1)->deg + front(list2)->deg;
    itr1 = front(list1);
    itr2 = front(list2);
    
    for (i = max_deg; i >= 0; --i) {
        push_back(&prod, 0, i);
    }

    while (itr1 != NULL) {
        while (itr2 != NULL) {
            itr = back(&prod);
            i = itr1->deg + itr2->deg;
            while (i > 0) {
                itr = itr->prev;
                i--;
            }
            itr->coeff += itr1->coeff * itr2->coeff;
            itr2 = itr2->next;
        }
        itr1 = itr1->next;
    }

    return prod;
}

int main() {
    List *list1, *list2, *sum, *diff, *prod;
    list1 = list2 = NULL;

    printf("Enter polynomial expression 1:\n");
    input_polynomial(&list1);
    printf("Enter polynomial expression 2:\n");
    input_polynomial(&list2);

    printf("Polynomial expression 1:");
    print_polynomial(&list1);
    printf("Polynomial expression 2:");
    print_polynomial(&list2);

    sum = add_polynomial(&list1, &list2);
    printf("Polynomial expression after addition:");
    print_polynomial(&sum);

    diff = sub_polynomial(&list1, &list2);
    printf("Polynomial expression after subtraction:");
    print_polynomial(&diff);

    prod = mul_polynomial(&list1, &list2);
    printf("Polynomial expression after multiplication:");
    print_polynomial(&prod);
    
    return 0;
}