#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024
#define MAX_POINTS 100

typedef struct {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}student;

void studPrint(student* stud, int numStud);
void loadDat(FILE* fp, student* stud);

int main() {
	FILE* file = NULL;
	int studNum = NULL;
	studNum = numOfStudents(file);
	student* stud = (student*)malloc(studNum*sizeof(student));
	loadDat(file, stud, studNum);
	studPrint(stud, studNum);
}

int numOfStudents(FILE* fp) {
	int counter = 1;
	char a;
	fp = fopen("Students.txt", "r");
	for (a = getc(fp); a != EOF; a = getc(fp)) {
		if (a == '\n') {
			counter = counter + 1;
		}
	}
	fclose(fp);
	return counter;
}
 
void loadDat(FILE* fp, student* stud, int numStud) {
	int i;
	fp = fopen("Students.txt", "r");
	for (i = 0; i < numStud; i++) {
		fscanf(fp, "%s %s %d \n", (stud + i)->name, (stud + i)->surname, &((stud + i)->points));
	}
	fclose(fp);

}

void studPrint(student* stud, int numStud) {
	for(int i=0;i<numStud;i++)
	printf("Ime: %s\n Prezime: %s\n Apsolutni bodovi: %d\n Relativni bodovi: %d\n\n",(stud+i)->name,(stud+i)->surname, (stud+i)->points, ((stud + i)->points)/MAX_POINTS*100);
}