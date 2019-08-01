
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FLUSH stdin=freopen(NULL,"r",stdin)
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
char* getString();

//Search
void search();

//Additional functionality
void filterByGenre();
void sort();

//Free table
void freeTable(Node**);

int main() {
    //Store node pointers instead of storing the whole nodes
    Node** table = (Node**)malloc(SIZE*sizeof(Node*));
    
    //If table is NULL
    if(table == NULL){
        exit(1);
    }
    
    initializeTable(table);
    
    //readFile(table);
    
    /*  Test code
    printf("Author for manga 1\n");
    char* author1 = getString();
    
    printf("Author for manga 2\n");
    char* author2 = getString();
    
    Manga manga;
    manga.id = 1;
    manga.author = author1;
    manga.genre = NULL;
    manga.publisher = NULL;
    manga.price = 0.0;
    manga.title = NULL;
    manga.used = false;
    manga.count = 1;
    add(table, manga);
    
    Manga manga2;
    manga2.id = 81;
    manga2.author = author2;
    manga2.genre = NULL;
    manga2.publisher = NULL;
    manga2.price = 0.0;
    manga2.title = NULL;
    manga2.used = false;
    manga2.count = 1;
    add(table, manga2);
    
    printf("%s\n", table[1]->manga.author);
    printf("%s\n", table[1]->next->manga.author);
    
    delete(table, 1);
    delete(table, 81);
     * 
     * 
    */
    free(table);
    
    
    
    return 0;
}

//Heon Lee
//This function waits for user input
//and allocates the input to Heap
//Returns the memory address of the input
//to the caller
char* getString(){
    char tmp[100] = {0};
    
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = 0;
    
    char* str = NULL;
    if(strlen(tmp) > 0){
        str = (char*)malloc((strlen(tmp)+1)*sizeof(char));
        strcpy(str, tmp);
    }
    FLUSH;
    return str;
}

//Heon Lee
void delete(Node** table, int id){
    int key = divisionHash(id);
    bool found = false;
    Node* current = table[key];
    Node* prev = NULL;
    while(!found && current != NULL){
        if(current->manga.id == id){
            found = true;
        }else{
            if(current->next != NULL){
               prev = current; 
            }
            current = current->next;
        }
    }
    
    if(table[key]->manga.id == current->manga.id){
        //found node is at first of the linked list
        table[key] = current->next;
    } else if(current->next == NULL){
        //found node is at the end
        prev->next = NULL;
    } else{
        //Mid-way
        prev->next = current->next;
    }
    if(found){
        free(current);
    }
}

//Heon Lee
void add(Node** table, Manga manga){
    int key = divisionHash(manga.id);
    Node* temp = (Node*)malloc(sizeof(Node));
    //If temp is NULL
    if(temp == NULL){
        exit(1);
    }
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
