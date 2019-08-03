

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define SIZE 80

#include <stdio.h>
#include <stdbool.h>
typedef struct {
    int id;
    char* title;
    char* author;
    char* genre;
    char* publisher;
    bool used;
    double price;
} Manga;

typedef struct node {
    Manga manga;
    struct node* next;
} Node;

//Hash table functions
void initializeTable(Node**);
int divisionHash(int);

#endif /* HASHTABLE_H */

