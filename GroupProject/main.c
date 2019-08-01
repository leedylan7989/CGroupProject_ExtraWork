
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
    int count;
} Manga;

typedef struct node {
    Manga manga;
    struct node* next;
}Node;

//Read from and Write to a record txt file
//Add any necessary functions and change return type
//If successful, return the Heap allocated array pointer to main
//If failed, return null
void readFile(int**);
void writeFile();

//View functions
void showAll();
void viewDetails(int);

//Hash table functions
int divisionHash(int);
void initializeTable(Node**);

//Basic functions
void add(Node**, Manga);
void edit();
void delete();

//Search
void search();

//Additional functionality
void filterByGenre();
void sort();

int main() {
    //Store node pointers instead of storing the whole nodes
    Node** table = (Node**)malloc(SIZE*sizeof(Node*));
    
    initializeTable(table);
    
    //readFile(table);
    
    Manga manga;
    manga.id = 1;
    manga.author = NULL;
    manga.genre = NULL;
    manga.publisher = NULL;
    manga.price = 0.0;
    manga.title = NULL;
    manga.used = false;
    manga.count = 1;
    add(table, manga);
    
    Manga manga2;
    manga2.id = 81;
    manga2.author = NULL;
    manga2.genre = NULL;
    manga2.publisher = NULL;
    manga2.price = 0.0;
    manga2.title = NULL;
    manga2.used = false;
    manga2.count = 1;
    add(table, manga2);
    
    
    return 0;
}

void delete(Node** table, int id){
    
    
}

void add(Node** table, Manga manga){
    int key = divisionHash(manga.id);
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->manga = manga;
    temp->next = NULL;
    if(table[key] == NULL){
        table[key] = temp;
    }else{
        Node* current = table[key];
        while(current->next != NULL){
            current = current->next;
        }
        current->next = temp;
    }
}

void initializeTable(Node** table){
    for(int i = 0; i < SIZE; i++){
        table[i] = NULL;
    }
}

//Calculating key using division method
int divisionHash(int id){
    return id%SIZE;
}
