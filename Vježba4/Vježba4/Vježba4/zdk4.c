#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128

typedef struct Polinome* Position;

typedef struct Polinome {

    int coef;
    int exp;
    Position  next;

} Poli;

int Read_file(Position P1, Position P2);
Position MakePol(int koef, int eks);
int ReadLine(Position head, char* buffer);
int ClearZero(Position head);
int InsertSorted(Position head, Position NewElement);
int InsertAfter(Position head, Position NewElement);
int Print(Position P);
int CleanUp(Position P);
int multiply(Position P1, Position P2);
int sum(Position P1, Position P2);



int main() {


    Poli head1 = { .coef = 0 , .exp = 0, .next = NULL };
    Poli head2 = { .coef = 0, .exp = 0, .next = NULL };

    Position P1 = &head1;
    Position P2 = &head2;

    int answer = 1;

    if (Read_file(P1, P2) != 0) {
        perror("Ne radi lista");
        return -1;
    }

    while (answer != 0) {


        printf("\nOdaberite broj ovisno o zeljenoj vrsti racunanja: \n");
        printf("Ispis binoma (1)\n");
        printf("UMNOZAK (2)\n");
        printf("zbroj je: (3)\n");
        printf(" Kraj (0)\n");
        printf("Unesite vas odabir:  ");
        scanf(" %d", &answer);



        switch (answer)
        {

        case 0:
            printf("Program je prekinut !!");
            break;

        case 1:
            printf("\nPolinomi iz datoteke su :\n");
            printf("\n 1. RED: \n");
            Print(P1);
            printf("\n 2. RED: \n");
            Print(P2);

            break;

        case 2:
            multiply(P1, P2);

            break;
        case 3:
            sum(P1, P2);

            break;

        default:
            printf("\nUnijeli ste broj koji nije poduden!\n");
            break;
        }
    }


    return 0;
}


int CleanUp(Position P) {

    Position temp = NULL;

    while (NULL != P->next) {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }

    return 0;
}

Position MakePol(int koef, int eks) {

    Position New = NULL;

    New = (Position)malloc(sizeof(Poli));

    New->coef = koef;
    New->exp = eks;
    New->next = NULL;

    return New;
}


int Read_file(Position P1, Position P2) {

    FILE* fp = NULL;
    char buffer[MAX_SIZE] = { 0 };

    fp = fopen("polinome.txt", "r");

    if (fp == NULL) {
        printf("Datoteku nije moguce otvoriti!!");
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(P1, buffer);
    ClearZero(P1);

    fgets(buffer, MAX_SIZE, fp);
    ReadLine(P2, buffer);
    ClearZero(P2);


    fclose(fp);

    return 0;
}

int ReadLine(Position head, char* buffer) {

    int coef, exp;
    int counter = 0;
    int read = 0;

    while (strlen(buffer) > 0) {
        read = sscanf(buffer, " %d  %d  %n ", &coef, &exp, &counter);

        if (read == 2 && coef != 0)
            InsertSorted(head, MakePol(coef, exp));

        buffer += counter;

    }

    return 0;
}

int InsertSorted(Position head, Position NewElement) {

    int n = 0; 

    while (head->next != NULL && head->next->exp < NewElement->exp) {
        head = head->next;
    }

    if (head->next != NULL && head->next->exp == NewElement->exp) {
        head->next->coef += NewElement->coef;
        n = head->coef;

        if (n == 0)
            ClearZero(head);
    }

    else {
        MakePol(NewElement->coef, NewElement->exp);
        InsertAfter(head, NewElement);
    }

    return 0;
}


int ClearZero(Position head) {
    Position temp = head;

    Position Temp1 = NULL;

    while (temp->next != NULL) {

        if (temp->next->coef == 0)
        {
            Temp1 = temp->next;
            temp->next = Temp1->next;
            free(Temp1);
        }

        else {
            temp = temp->next; 
        }

    }
    return 0;
}

int InsertAfter(Position head, Position NewElement) {

    NewElement->next = head->next;
    head->next = NewElement;

    return 0;
}

int Print(Position P) {
    Position temp = P->next;
 
    while (temp) {
        printf(" %dx^%d  \n", temp->coef, temp->exp);
        temp = temp->next;  
    }

    return 0;
}
int sum(Position p1, Position p2) {
    p1 = p1->next;
    p2 = p2->next;
    Position temp = NULL;
    int sum_coef = 0;

    printf("zbroj je: \t\n");
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            sum_coef = p1->coef + p2->coef;
            printf("\t%dx^%d\n", sum_coef, p1->exp);
            p1 = p1->next;
            p2 = p2->next;


        }
        else if (p1->exp > p2->exp) {
            printf("\t%dx^%d\n", p2->coef, p2->exp);
            p2 = p2->next;

        }
        else {
            printf("\t%dx^%d\n", p1->coef, p1->exp);
            p1 = p1->next;
        }
    }
    if (p1 == NULL)temp = p2;
    else if (p2 == NULL) { temp = p1; }
    while (temp != NULL) {
        printf(" ovaj:\t%dx^%d", temp->coef, temp->exp);
        temp = temp->next;
    }
    return 0;

}

int multiply(Position p1, Position p2) {
    int mult_coef = 1, sum_exp = 0;
    p1 = p1->next;
    p2 = p2->next;
    if (p1 == NULL) { printf("null je"); }
    while (p1 != NULL) {
        mult_coef = mult_coef * p1->coef;
        sum_exp = sum_exp + p1->exp;
        printf("trenutno stanje : %dx^%d\n", mult_coef, sum_exp);
        p1 = p1->next;

    }
    while (p2 != NULL) {
        mult_coef = mult_coef * p2->coef;
        sum_exp = sum_exp + p2->exp;
        printf("trenutno stanje : %dx^%d\n", mult_coef, sum_exp);
        p2 = p2->next;
    }
    printf("Rjesenje je : %dx^%d", mult_coef, sum_exp);
    return 0;
}