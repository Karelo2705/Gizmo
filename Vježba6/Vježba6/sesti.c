// errors.h
#ifndef ERRORS_H
#define ERRORS_H

#define FILE_WITH_BILLS_NOT_OPENED (1)
#define CREATE_BILL_FAILED (-1)
#define STRING_DESTINATION_NULL (-2)
#define STRING_NOT_VALID (-3)

#endif // !ERRORS_H

// date.h
#ifndef DATE_H
#define DATE_H
#include "errors.h"
#include <stdbool.h>

#define YEAR_STRING_LENGTH (4)           // 1999
#define DAY_STRING_LENGTH (2)            // 08
#define MONTH_STRING_LENGTH (2)          // 12
#define DASH_LENGTH (1)                  // -
#define NULL_TERMINATING_CHAR_LENGTH (1) // \0
#define MAX_DATE_AS_STRING (YEAR_STRING_LENGTH + DASH_LENGTH + MONTH_STRING_LENGTH + DASH_LENGTH + DAY_STRING_LENGTH + NULL_TERMINATING_CHAR_LENGTH)

struct _date;
typedef struct _date* DateP;
typedef struct _date {
    int year;
    int month;
    int day;
} Date;

DateP CreateDateFromString(char* str);
int DateToString(char* destination, DateP date);
int PrintDate(DateP date);
int Datecmp(DateP date1, DateP date2);
bool IsDateInsideOfRange(DateP date, DateP from, DateP to);

#endif

// article.h
#ifndef ARTICLE_H_
#define ARTICLE_H_
#include "errors.h"

#define MAX_ARTICLE_NAME (128)

struct _article;
typedef struct _article* ArticleP;
typedef struct _article {
    char name[MAX_ARTICLE_NAME];
    int count;
    float price;
    ArticleP next;
} Article;

int InitializeArticle(ArticleP article);
ArticleP CreateArticleFromString(char* str);
int ArticleToString(char* destination, ArticleP article);
int PrintArticle(ArticleP article);
ArticleP FindArticleByName(ArticleP head, char* name);
int DeleteArticleAfter(ArticleP position);
int DeleteAllArticles(ArticleP head);
int InsertArticleAfter(ArticleP position, ArticleP article);
int InsertArticleSorted(ArticleP head, ArticleP article);

#endif

// filter.h
#ifndef FILTER_H
#define FILTER_H
#include "date.h"
#include "article.h"

struct _filter;
typedef struct _filter* FilterP;
typedef struct _filter {
    DateP from;
    DateP to;
    char name[MAX_ARTICLE_NAME];
} Filter;

int InitializeFilter(FilterP filter);
FilterP CreateFilter(char* dateFromStr, char* dateToStr, char* articleName);
int DeleteFilter(FilterP filter);

#endif

// bill.h
#ifndef BILL_H
#define BILL_H
#include "date.h"
#include "article.h"
#include "errors.h"

#define MAX_BILL_NAME (128)

struct _bill;
typedef struct _bill* BillP;
typedef struct _bill {
    char name[MAX_BILL_NAME];
    DateP date;
    ArticleP articleHead;
    BillP next;
} Bill;

int InitializeBill(BillP bill);
BillP CreateBill(char* billFileName);
int InsertBillAfter(BillP position, BillP bill);
int InsertBillSorted(BillP head, BillP bill);
int ReadBillsFromFile(BillP head, char* fileName);
int PrintBill(BillP bill);
int PrintAllBills(BillP head);
int DeleteBill(BillP bill);
int DeleteBillAfter(BillP position);
int DeleteAllBills(BillP head);

#endif

// date.c
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

DateP CreateDateFromString(char* str) {
    DateP date = NULL;
    int status = 0;

    date = (DateP)malloc(sizeof(Date));
    if (!date) {
        return NULL;
    }

    status = sscanf(str, "%d-%d-%d", &date->year, &date->month, &date->day);
    if (status != 3) {
        free(date);
        return NULL;
    }

    return date;
}

int DateToString(char* destination, DateP date) {
    if (!destination) {
        printf("Destination string is null!\r\n");
        return STRING_DESTINATION_NULL;
    }

    if (!date) {
        printf("Date is null!\r\n");
        return STRING_NOT_VALID;
    }

    sprintf(destination, "%d-%02d-%02d", date->year, date->month, date->day);
    return EXIT_SUCCESS;
}

int PrintDate(DateP date) {
    char dateAsString[MAX_DATE_AS_STRING] = { 0 };

    DateToString(dateAsString, date);
    printf(dateAsString);

    return EXIT_SUCCESS;
}

int Datecmp(DateP date1, DateP date2) {
    int result = date1->year - date2->year;

    if (result == 0) {
        result = date1->month - date2->month;
        if (result == 0) {
            result = date1->day - date2->day;
        }
    }

    return result;
}

bool IsDateInsideOfRange(DateP date, DateP from, DateP to) {
    return Datecmp(date, from) >= 0 && Datecmp(date, to) <= 0;
}

// article.c
#include "article.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTICLE_AS_STRING (1024)

int InitializeArticle(ArticleP article) {
    article->count = 0;
    article->price = 0.0f;
    memset(article->name, 0, MAX_ARTICLE_NAME);

    return EXIT_SUCCESS;
}

ArticleP CreateArticleFromString(char* str) {
    ArticleP article = NULL;
    int status = 0;

    article = (ArticleP)malloc(sizeof(Article));
    if (!article) {
        return NULL;
    }

    InitializeArticle(article);

    status = sscanf(str, "%s %d %f", &article->name, &article->count, &article->price);
    if (status != 3) {
        free(article);
        return NULL;
    }

    return article;
}

int ArticleToString(char* destination, ArticleP article) {
    if (!destination) {
        printf("Destination string is null!\r\n");
        return STRING_DESTINATION_NULL;
    }

    if (!article) {
        sprintf(destination, "##INVALID ARTICLE");
        return STRING_NOT_VALID;
    }

    sprintf(destination, "%s %d %.02f", article->name, article->count, article->price);
    return EXIT_SUCCESS;
}

int PrintArticle(ArticleP article) {
    char articleAsString[MAX_ARTICLE_AS_STRING] = { 0 };

    ArticleToString(articleAsString, article);
    printf(articleAsString);

    return EXIT_SUCCESS;
}

ArticleP FindArticleByName(ArticleP head, char* name) {
    ArticleP article = NULL;

    for (article = head; article != NULL; article = article->next) {
        if (strcmp(article->name, name) == 0) {
            return article;
        }
    }

    return NULL;
}

int DeleteArticleAfter(ArticleP position) {
    ArticleP toDelete = position->next;

    if (!toDelete) {
        return EXIT_SUCCESS;
    }

    position->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int DeleteAll

Articles(ArticleP head) {
    while (head->next) {
        DeleteArticleAfter(head);
    }

    return EXIT_SUCCESS;
}

int InsertArticleAfter(ArticleP position, ArticleP article) {
    article->next = position->next;
    position->next = article;

    return EXIT_SUCCESS;
}

int InsertArticleSorted(ArticleP head, ArticleP article) {
    ArticleP position = head;

    while (position->next != NULL && strcmp(position->next->name, article->name) < 0) {
        position = position->next;
    }

    InsertArticleAfter(position, article);

    return EXIT_SUCCESS;
}

// filter.c
#include "filter.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

int InitializeFilter(FilterP filter) {
    filter->from = NULL;
    filter->to = NULL;
    memset(filter->name, MAX_ARTICLE_NAME, 0);

    return EXIT_SUCCESS;
}

FilterP CreateFilter(char* dateFromStr, char* dateToStr, char* articleName) {
    FilterP filter = NULL;

    filter = (FilterP)malloc(sizeof(Filter));
    if (!filter) {
        return NULL;
    }

    InitializeFilter(filter);

    filter->from = CreateDateFromString(dateFromStr);
    if (!filter->from) {
        DeleteFilter(filter);
        return NULL;
    }

    filter->to = CreateDateFromString(dateToStr);
    if (!filter->to) {
        DeleteFilter(filter);
        return NULL;
    }

    strncpy(filter->name, articleName, MAX_ARTICLE_NAME - 1);

    return filter;
}

int DeleteFilter(FilterP filter) {
    if (filter->from) {
        free(filter->from);
    }

    if (filter->to) {
        free(filter->to);
    }

    free(filter);

    return EXIT_SUCCESS;
}

// bill.c
#include "bill.h"
#include "date.h"
#include "article.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE (1024)

int InitializeBill(BillP bill) {
    bill->date = NULL;
    bill->next = NULL;
    memset(bill->name, 0, MAX_BILL_NAME);
    InitializeArticle(&bill->articleHead);

    return EXIT_SUCCESS;
}

BillP CreateBill(char* billFileName) {
    FILE* fp = NULL;
    BillP bill = NULL;
    int status = EXIT_SUCCESS;
    char fileLine[MAX_LINE] = { 0 };

    bill = (BillP)malloc(sizeof(Bill));
    if (!bill) {
        return NULL;
    }

    InitializeBill(bill);

    strcpy(bill->name, billFileName);

    fp = fopen(billFileName, "r");
    if (!fp) {
        perror("File with bills not opened!");
        DeleteBill(bill);
        return NULL;
    }

    fgets(fileLine, MAX_LINE, fp);
    bill->date = CreateDateFromString(fileLine);
    if (!bill->date) {
        fclose(fp);
        DeleteBill(bill);
        return NULL;
    }

    while (fgets(fileLine, MAX_LINE, fp)) {
        if (fileLine[0] == '\n') {
            continue;
        }

        ArticleP article = CreateArticleFromString(fileLine);
        if (!article) {
            fclose(fp);
            DeleteBill(bill);
            return NULL;
        }

        InsertArticleSorted(&bill->articleHead, article);
    }

    fclose(fp);

    return bill;
}

int InsertBillAfter(BillP position, BillP bill) {
    bill->next = position->next;
    position->next = bill;

    return EXIT_SUCCESS;
}

int InsertBillSorted(BillP head, BillP bill) {
    BillP position = head;

    while (position->next != NULL && Datecmp(position->next->date, bill->date) < 0) {
        position = position->next;
    }

    InsertBillAfter(position, bill);

    return EXIT_SUCCESS;
}

int ReadBillsFromFile(BillP head, char* fileName) {
    FILE* fp = NULL;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(fileName, "r");
    if (!fp) {
        perror("File with bills not opened!");
        return FILE_WITH_BILLS_NOT_OPENED;
    }

    while (!feof(fp)) {
        if (!fgets(fileLine, MAX_LINE, fp)) {
            break;
        }

        BillP bill = CreateBill(fileLine);
        if (!bill) {
            fclose(fp);
            DeleteAllBills(head);
            return CREATE_BILL_FAILED;
        }

        InsertBillSorted(head, bill);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int PrintBill(BillP bill) {
    ArticleP article = NULL;

    printf("\t============================\r\n");
    printf("\t\t** Date => ");
    PrintDate(bill->date);
    printf("\r\n");
    printf("\t\t** Articles (name, count, price) \r\n");

    for (article = bill->articleHead.next; article != NULL; article = article->next) {
        printf("\t\t\t * ");
        PrintArticle(article);
        printf("\r\n");
    }

    return EXIT_SUCCESS;
}

int PrintAllBills(BillP head) {
    BillP bill = NULL;

    for (bill = head->next; bill != NULL; bill = bill->next) {
        PrintBill(bill);
    }

    return EXIT_SUCCESS;
}

int DeleteBill(BillP bill) {
    if (!bill) {
        return EXIT_SUCCESS;
    }

    if (bill->date) {
        free(bill->date);
    }

    DeleteAllArticles(&bill->articleHead);
    free(bill);

    return EXIT_SUCCESS;
}

int DeleteBillAfter(BillP position) {
    BillP toDelete = position->next;

    if (!toDelete) {
        return EXIT_SUCCESS;
    }

    position->next = toDelete->next;
    DeleteBill(toDelete);

    return EXIT_SUCCESS;
}

int DeleteAllBills(BillP head) {
    while (head->next) {
        DeleteBillAfter(head);
    }

    return EXIT_SUCCESS;
}

// main.c
#include "bill.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    BillP head;
    char fileName[MAX_FILE_NAME] = { 0 };
    int status = EXIT_SUCCESS;

    InitializeBill(&head);

    do {
        printf("Please insert filename ->\t");
        scanf(" %s", fileName);

        status = ReadBillsFromFile(&head, fileName);

        if (status != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }

        printf("\r\n"
            "\t ** Successfully read %s:\r\n\r\n",
            fileName);
        PrintAllBills(&head);
        UserSearchArticleInRange(&head);
        DeleteAllBills(&head);
    } while (status > EXIT_SUCCESS);

    return EXIT_SUCCESS;
}

int UserSearchArticleInRange(BillP head) {
    FilterP filter = NULL;
    char article[MAX_ARTICLE_NAME];
    char dateFromString[MAX_DATE_AS_STRING];
    char dateToString[MAX_DATE_AS_STRING];

    do {
        printf("Please insert article name and date range (YYYY-MM-DD YYYY-MM-DD) or type 'exit' to end:\t");
        scanf(" %s", article);

        // Check if the user wants to exit
        if (strcmp(article, "exit") == 0) {
            break;
        }

        printf("Please insert start date (YYYY-MM-DD):\t");
        scanf(" %s", dateFromString);

        printf("Please insert end date (YYYY-MM-DD):\t");
        scanf(" %s", dateToString);

        filter = CreateFilter(dateFromString, dateToString, article);

        if (!filter) {
            printf("Invalid input. Please try again.\n");
            continue;
        }

        printf("\n** Bills within the specified range for the article %s:\n", filter->name);
        PrintFilteredBills(head, filter);
        DeleteFilter(filter);

    } while (1);

    return EXIT_SUCCESS;
}

int PrintFilteredBills(BillP head, FilterP filter) {
    BillP bill = NULL;

    for (bill = head->next; bill != NULL; bill = bill->next) {
        if (IsDateInsideOfRange(bill->date, filter->from, filter->to)) {
            ArticleP article = FindArticleByName(&bill->articleHead, filter->name);
            if (article) {
                PrintBill(bill);
            }
        }
    }

    return EXIT_SUCCESS;
}
