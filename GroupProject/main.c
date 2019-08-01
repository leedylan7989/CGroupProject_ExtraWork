
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
bool edit(int, Node*);
void delete();
char* getString();

//Search
void search();

//Additional functionality
void filterByGenre();
void sort();

//Free table
void freeTable(Node***);
void freeList(Node**);
void freeNode(Node**);

int main() {
    //Store node pointers instead of storing the whole nodes
    Node** table = (Node**)malloc(SIZE*sizeof(Node*));
    
    //If table is NULL
    if(table == NULL){
        exit(1);
    }
    
    initializeTable(table);
    
    //readFile(table);
    
    //Test code
    
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
    
    freeTable(&table);
    
    
    
    return 0;
}

//Heon Lee
//A caller records a user's choice in an int variable
//Choice List
/*
 * 1 - title
 * 2 - author
 * 3 - genre
 * 4 - publisher
 * 5 - used
 * 6 - price
 * 7 - count
 */
bool edit(int choice, Node* node){
    if(choice == 1 || choice == 2 || choice == 3 ||
            choice == 4){
        if (choice == 1)
            printf("Type a new title for Manga\n");
        else if (choice == 2)
            printf("Type a new author for Manga\n");
        else if (choice == 3)
            printf("Type a new genre for Manga\n");
        else
            printf("Type a new publisher for Manga\n");
        char* new = getString();
        if(new != NULL){
            if(choice == 1)
                node->manga.title = new;
            else if (choice == 2)
                node->manga.author = new;
            else if (choice == 3)
                node->manga.genre = new;
            else
                node->manga.publisher = new;
            return true;
        } else {
            return false;
        }
    } else if(choice == 5){
        //Change used
        node->manga.used = !node->manga.used;
        printf("%s", node->manga.used ? "Changed from false to true" :
            "Changed from true to false");
        return true;
    } else if(choice == 6){
        //Price
        double new;
        printf("Type a new price for Manga.\n-999 - Exit\n");
        scanf("%lf", &new);
        if(new == -999){
            return false;
        }
        while(new < 0.0){
            printf("Negative value is not a valid price. Type again. -999 - Exit");
            scanf("%lf", &new);
            if(new == -999){
                return false;
            }
        }
        node->manga.price = new;
        return true;
    } else {
        //Count
        int choiceCount;
        int amount;
        printf("1 - Increase count\n2 - Decrease Count\n0 - Exit\n");
        scanf("%d", choiceCount);
        //Exit condition
        if(choiceCount){
            return false;
        }
        while(choiceCount != 1 || choiceCount != 2){
            printf("1 or 2 are the only valid options. 0 - Exit.");
            scanf("%d", choiceCount);
            if(choiceCount){
                return false;
            }
        }
        printf("How many?\n0 - Exit\n");
        scanf("%d", amount);
        //Exit condition
        if(amount){
            return false;
        }
        //Validation
        if(choiceCount == 2){
            while((node->manga.count - amount) < 0){
                printf("Invalid amount. Please type again.\n0 - Exit\n");
                scanf("%d", amount);
                if(amount)
                    return false;
            }
        }
        
        if(choiceCount == 1){
            node->manga.count = node->manga.count + amount;
            return true;
        } else {
            node->manga.count = node->manga.count - amount;
            return true;
        }
    }
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
        if(str == NULL){
            exit(1);
        }
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
        current->next = NULL;
    }
    if(found){
        freeNode(&current);
    }
}

//Heon Lee
void freeNode(Node** node){
    if((*node)->manga.author != NULL){
        free((*node)->manga.author);
    }
    
    if((*node)->manga.genre != NULL){
        free((*node)->manga.genre);
    }
    
    if((*node)->manga.title != NULL){
        free((*node)->manga.genre);
    }
    
    if((*node)->manga.publisher != NULL){
        free((*node)->manga.publisher);
    }
    
    //Make sure node->next is not pointing to anything
    if((*node)->next != NULL){
        (*node)->next = NULL;
    }
    
    free(*node);
}


//Heon Lee
void freeList(Node** head){
    //Move to the tail node of the list
    while(*head != NULL){
        Node* temp = *head;
        *head = (*head)->next;
        freeNode(&temp);
    }
}

//Heon Lee
void freeTable(Node*** table){
    for(int i = 0; i < SIZE; i++){
        freeList(&((*table)[i]));
    }
    free(*table);
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
