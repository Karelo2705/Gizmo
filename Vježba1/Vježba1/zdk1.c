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

int main() {
	FILE* file = NULL;
	int studNum = NULL;
	studNum = numOfStudents(file);
	printf("%d", studNum);

	

}

int numOfStudents(FILE* fp) {
	int counter = 1;
	char a;
	fp = fopen("Students.txt", "r");
	for (a = getc(fp); a != EOF; a = getc(fp))
		if (a == '\n')
			counter = counter + 1;
	fclose(fp);
	return counter;
}

