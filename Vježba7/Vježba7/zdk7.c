#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 60

typedef struct Tree* Position;
typedef struct List* lPosition;

typedef struct Tree {
    char* name;
    Position brother;
    Position child;
}tree;


typedef struct List {
    Position directory;

    lPosition next;
    lPosition prev;
}list;

#pragma funkicje
int Menu(Position, lPosition);
int Line(lPosition, Position, Position);
lPosition FindLast(lPosition);
int MakeTree(Position);
Position OpenDirec(Position, lPosition);
int Push(lPosition, Position);
Position FindByName(char*, Position);
Position Backstep(Position, lPosition);
int ChildPrint(Position current);
int TreeDelete(Position);
#pragma end_funkcije


int main() {

    Position root;
    root = (Position)malloc(sizeof(tree));
    root->brother = NULL;
    root->child = NULL;

    lPosition head; 
    head = (lPosition)malloc(sizeof(list));
    head->next = NULL;
    head->prev = NULL;

    root->name = (char*)malloc(MAX_SIZE * sizeof(char));
    root->name = "C:";

    int s = 1;
    while (s) {
        s = Menu(root, head); 
    }

    return 0;
}


int Menu(Position root, lPosition head) {

    Position current = root;
    char chosen[MAX_SIZE] = { 0 };

    printf("md [...] - Dodaj novi direktorij\n"); 
    printf("cd [...] - Otvori direktorij\n"); 
    printf("cd.. - Vrati na prethodni direktorij\n"); 
    printf("dir - Ispis pod-direktorija trenutnog direktorija\n");
    printf("exit - KRAJ\n\n");

    while (1) {

        Line(head, root, current);
        scanf(" %s", chosen);

        if (strcmp(chosen, "md") == 0)
            MakeTree(current);

        else if (strcmp(chosen, "cd") == 0)
            current = OpenDirec(current, head);

        else if (strcmp(chosen, "cd..") == 0)
            current = Backstep(current, head);


        else if (strcmp(chosen, "dir") == 0)
            ChildPrint(current);

        else if (strcmp(chosen, "exit") == 0) {
            TreeDelete(root);
            return 0;
        }

        else
            printf("Error! Try again!\n");
    }

    return 0;
}

int Line(lPosition head, Position root, Position current) {

    lPosition clan; 

    clan = FindLast(head);

    if (head->next == NULL)
    {
        printf("%s>", root->name);
        return 0;
    }

    while (NULL != clan->prev)
    {
        printf("%s>", clan->directory->name);
        clan = clan->prev;
    }

    printf("%s>", current->name);
    return 0;
}

lPosition FindLast(lPosition head) {

    lPosition z;
    z = head->next;

    if (NULL == z)
        return NULL;

    while (z->next != NULL)
    {
        z = z->next;
    }

    return z;
}

int MakeTree(Position current) {

    Position directory;
    directory = (Position)malloc(sizeof(tree));
    directory->name = (char*)malloc(MAX_SIZE * sizeof(char));

    if (!directory)
        perror("Cannot alocate memory!!\n");

    if (NULL != current->child) {
        current = current->child;
        while (NULL != current->brother)
        {
            current = current->brother;
        }
        current->brother = directory;
    }

    else
        current->child = directory;

    scanf(" %s", directory->name);
    directory->brother = NULL;
    directory->child = NULL;

    return 0;
}

Position OpenDirec(Position current, lPosition head) {

    Position s;
    char* name;
    name = (char*)malloc(MAX_SIZE * sizeof(char));

    scanf(" %s", name);

    if (NULL == current->child) {
        printf("Nema tog direktorija!!\n");
        return current;
    }

    s = FindByName(name, current);
    if (!s) {
        perror("Direktorij nije pronađen!!\n");
        return current;
    }

    Push(head, current);

    return s;
}

int Push(lPosition head, Position direktorij) {

    lPosition p = (lPosition)malloc(sizeof(list));

    p->next = head->next;
    p->prev = head;

    if (NULL != head->next)
    {
        head->next->prev = p;
    }

    head->next = p;
    p->directory = direktorij;

    return 0;
}

Position FindByName(char* name, Position current) {

    if (NULL == current->child)
    {
        printf("Direktorij je prazan!!");
        return 0;
    }

    current = current->child;

    while (strcmp(name, current->name) != 0 && current->brother != NULL) {
        current = current->brother;
    }

    if (NULL == current->brother)
    {    
        if (strcmp(name, current->name) != 0)
            return NULL;

        else
            return current;
    }

    else
        return current;
}
Position Backstep(Position current, lPosition lcurrent) {
    Position solution = lcurrent->next->directory;
    lPosition deleted = lcurrent->next;

    deleted->next->prev = lcurrent;
    lcurrent->next = deleted->next;
    free(deleted);
    return solution;
}


int ChildPrint(Position current) {
    int counter_dir = 0;
    long int memory = 0;
    if (NULL == current->child) {
        printf("Datoteka je prazna aka nema dice\n");
    }
    else {
        printf("Directory of %s \n ", current->name);
        current = current->child;
        while (NULL != current) {
            counter_dir++;
            printf("\n %ld B ,  %s", sizeof(current), current->name);
            current = current->brother;
            memory += sizeof(current);
        }
        printf("\n%d File(s)", counter_dir);
        printf("\n%ld Bytes taken\n", memory);

    }
}
int TreeDelete(Position current) {
    if (current == NULL) {
        return 0;
    }
    TreeDelete(current->brother);
    TreeDelete(current->child);
    free(current);
    return 0;
}