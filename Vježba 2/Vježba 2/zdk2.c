#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 128
#define MAX_LINE 1024
#define ERR_NUM -1

typedef struct _person* Position;
typedef struct _person {

	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;

} Person;

int addToTop(Position head, char* name, char* surname, int birthYear);
void deleteMember(Position head, char* surnameToFind);
Position printBySurname(Position head, char* surnameToFind);

int main() {
	Person Head = { .next = NULL, .name = {0}, .surname = {0},	.birthYear = 0 };
	Position P = &Head;

	int finder = 10;

	char name[MAX_SIZE] = { " " };
	char surname[MAX_SIZE];
	int yearOfBirth = NULL;

	while (finder != 0) {
		printf("\t\nSto zelite uciniti?\n\n");
		printf("\tUnijeti osobu na pocetak liste (1)\n");
		printf("\tUnijeti osobu na kraj liste (2)\n");
		printf("\tPretraziti osobu po prezimenu (3)\n");
		printf("\tIzbrisati osobu iz liste (4)\n\n");
		printf("\tKraj (0) \n\n");
		printf("Unesite vas odabir:  ");
		scanf_s(" %d", &finder);

		switch (finder) {
		case 1:
			printf("Unesite ime:\n");
			scanf("%s", name);
			printf("Unesite prezime:\n");
			scanf("%s", surname);
			printf("Unesite godinu rođenja:");
			scanf("%d", &yearOfBirth);
			addToTop(P, name, surname, yearOfBirth);
			printList(P);
			continue;

		case 2:
			printf("Unesite ime:\n");
			scanf("%s", name);
			printf("Unesite prezime:\n");
			scanf("%s", surname);
			printf("Unesite godinu rođenja:");
			scanf("%d", &yearOfBirth);
			addToBottom(P, name, surname, &yearOfBirth);
			printList(P);

			continue;

		case 3:
			printf("Unesite prezime");
			scanf("%s", surname);
			printBySurname(P, surname);
			printList(P);
			continue;

		case 4:
			printf("Unesite prezime");
			scanf("%s", surname);
			deleteMember(P, surname);
			printList(P);
			continue;


		}
	}
}



int addToTop(Position head, char* name, char* surname, int birthYear) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		printf("Can't allocate memory!");

		return EXIT_SUCCESS;
	}


	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;

}

int printList(Position head) {
	while (head!= NULL) {
		printf("%s %s %d\n", head->name, head->surname, head->birthYear);
		head = head->next;
	}
	return  EXIT_SUCCESS;
}

int addToBottom(Position head, char* name, char* surname, char* birthYear) {
	while (head != NULL) {
		head = head->next;
	}
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		printf("Can't allocate memory!");

		return EXIT_SUCCESS;
	}


	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;

}

Position printBySurname(Position head, char* surnameToFind) {
	Position temp = head->next;
	do {
		if (strcmp(temp->surname, surnameToFind) == 0)
		{
			return temp;
		}
		temp = temp->next;

	} while (temp != NULL);
	return NULL;
}

void deleteMember(Position head, char* surnameToFind) {
	Position temp = head->next;
	Position tempBefore = head;
	do {
		if (strcmp(temp->surname, surnameToFind) == 0)
		{
			tempBefore->next = temp->next;
			free(temp);
		}
		temp = temp->next;
		tempBefore = tempBefore->next;

	} while (temp != NULL);
	printList(head);



}


