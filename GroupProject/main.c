
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 80

typedef struct{
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
}Node;

//Read from and Write to a record txt file
//Add any necessary functions and change return type
//If successful, return the Heap allocated array pointer to main
//If failed, return null
void readFile();
void writeFile();

//View functions
void showAll();
void viewDetails(int);

//Basic functions
void add();
void edit();
void delete();

//Search
void search();

//Additional functionality
void filterByGenre();
void sort();

int main() {
    
    
    return 0;
}

void add(){
    
}


