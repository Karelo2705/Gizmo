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

int addToTop(Position head);
int printList(Position head);
int addToBottom(Position head);
void deleteMember(Position head);
Position printBySurname(Position head);


int main() {
	Person Head = { .next = NULL, .name = {0}, .surname = {0},	.birthYear = 0 };
	Position P = &Head;
	P->next = NULL;

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
			addToTop(P);
			printList(P);
			continue;

		case 2:
			addToBottom(P);
			printList(P);

			continue;

		case 3:
			Position person = printBySurname(P);
			printf("%s %s %d",person->name, person->surname, person->birthYear );
			continue;

		case 4:
			printf("Unesite prezime: ");
			scanf("%s", surname);
			deleteMember(P, surname);
			printList(P);
			continue;


		}
	}
}



int addToTop(Position head) {
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	if (!newPerson) {
		printf("Can't allocate memory!");

		return EXIT_SUCCESS;
	}
	printf("Unesite ime:\n");
	scanf("%s", name);
	printf("Unesite prezime:\n");
	scanf("%s", surname);
	printf("Unesite godinu rođenja:");
	scanf("%d", &birthYear);

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

int addToBottom(Position head) {
	while (head->next != NULL) {
		head = head->next;
	}
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;

	if (!newPerson) {
		printf("Can't allocate memory!");

		return EXIT_FAILURE;
	}
	printf("Unesite ime:\n");
	scanf("%s", name);
	printf("Unesite prezime:\n");
	scanf("%s", surname);
	printf("Unesite godinu rođenja:");
	scanf("%d", &birthYear);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;

}

Position printBySurname(Position head) {
	char surname[MAX_SIZE];
	Position temp = head->next;

	printf("Unesite prezime: ");
	scanf("%s", surname);

	do {
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp = temp->next;

	} while (temp != NULL);
	return NULL;
}

	int deleteMember(Position head, char* surnameToFind) {
	Position temp = head->next;
	Position tempBefore = head;
	do {
		if (strcmp(temp->surname, surnameToFind) == 0)
		{
			tempBefore->next = temp->next;
			free(temp);
			return EXIT_SUCCESS;
		}
		temp = temp->next;
		tempBefore = tempBefore->next;

	} while (temp != NULL);

	return EXIT_SUCCESS;

}


