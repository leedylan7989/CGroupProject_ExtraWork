

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
    //1 - User want to continue a search
    //0 - User want to cancel a search
    int search;
    struct node* next;
    //Used for title dictionary
    struct node* nextTitle;
    //Used for author dictionary
    struct node* nextAuthor;
    //Used for genre dictionary
    struct node* nextGenre;
    //Used for publisher dictionary
    struct node* nextPublisher;
    //Used for used book
    struct node* nextUsed;
    //Used for range search
    struct node* nextList;
    //Used for double search
    struct node* nextSecondList;
} Node;

//Hash table functions
void initializeTable(Node**, int);
int divisionHash(int);

#endif /* HASHTABLE_H */

