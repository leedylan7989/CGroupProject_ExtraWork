
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
void readFile(Node**);
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
void delete(Node**, int);
char* getString();
void addManga(Node**);
bool deleteManga(Node**);
void printAll(Node**);
void printNode(Node*);

//Screens
int mainScreen();

//Search
Node* searchManga(Node**, int);
Node* searchByID(Node**, int);
Node* searchByTitle(Node**, char*);

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
    
    int choice;
    while((choice = mainScreen())){
        if(choice == 1){
            //Add
            addManga(table);
        } else if(choice == 2){
            //Edit
            
        } else if(choice == 3){
            //Delete
            if(deleteManga(table)){
                printf("\nDelete successful.\n");
            }else{
                printf("\nDelete failed.\n");
            }
        } else if(choice == 4) {
            //Search
            searchManga(table);
        } else if(choice == 5){
            printf("\n==========================================\n");
            printAll(table);
            printf("==========================================\n\n");
        }
    }
    
    
    //writeFile(table);
    
    
    printf("Thanks for using our shop!\n");
    freeTable(&table);
    
    
    
    return 0;

}

void editManga(Node** table){
    //First, search a Manga to edit.
    printf("Search a Manga to edit");
    Node* node = searchManga(table,1);
}

//Searching Manga from the hash table
//If select == 0, then return null.
//If select == 1, return a selected Manga.
//A caller will only set select to 1
//when a caller needs to retreive
//a selected record.
Node* searchManga(Node** table, int select) {
    //Search
    printf("\n1 - Search by ID\n2 - Search by Title\n");
    int choice;
    scanf("%d", &choice);
    while (choice != 1 && choice != 2) {
        printf("Please select the valid options.\n");
        scanf("%d", choice);
    }

    FLUSH;

    if (choice == 1) {
        printf("Type the ID you want to search.\n");
        int id;
        scanf("%d", &id);
        while (id < 0) {
            printf("Please select a valid id.\n");
            scanf("%d", &id);
        }
        Node* node = searchByID(table, id);
        if (node != NULL) {
            printNode(node);
        } else {
            printf("\nSEARCH FAILED. ID NOT FOUND.\n");
        }
        
        if(select)
            return node;
    } else if (choice == 2) {
        printf("Type the title you want to search.\n");
        char* title = getString();

        Node* node = searchByTitle(table, title);
        if (node != NULL) {
            printNode(node);
        } else {
            printf("\nSEARCH FAILED. BOOK NOT FOUND.\n");
        }
        if(select)
        return node;
    }
    
    return NULL;
}

void printAll(Node** table){
    Node* current;
    for(int i = 0; i < SIZE; i++){
        current = table[i];
        while(current != NULL){
            printNode(current);
            current = current->next;
        printf("-------------------------------------------\n");
        }
    }
}


void printNode(Node* node){
    printf("\nID: %d\nTitle: %s\nAuthor: %s\nGenre: %s\nPublisher: %s\n"
            "Price: %lf\nCount: %d\n", node->manga.id, node->manga.title,
            node->manga.author,node->manga.genre, node->manga.publisher,
            node->manga.price, node->manga.count);
    if(node->manga.used){
        printf("Used\n");
    }else{
        printf("New\n");
    }
}
bool deleteManga(Node** table){
    printf("Which Manga do you want to delete?\n"
            "1 - Search by ID\n2 - Search by Title\n");
    int choice;
    scanf("%d", &choice);
    while(choice != 1 && choice != 2){
        printf("Please select the valid options.\n");
        scanf("%d", choice);
    }
    
    if(choice == 1) {
        printf("Type the ID you want to delete.\n");
        int id;
        scanf("%d", &id);
        while (id < 0) {
            printf("Please select a valid id.\n");
            scanf("%d", &id);
        }

        if (searchByID(table, id) != NULL) {
            delete(table, id);
            return true;
        } else {
            return false;
        }
    } else if(choice == 2){
        printf("Type the title you want to delete.\n");
        char* deleteTitle = getString();
        
        Node* node = searchByTitle(table, deleteTitle);
        if(node != NULL){
            delete(table, node->manga.id);
            return true;
        }else {
            return false;
        }
    }
    return false;
}

Node* searchByTitle(Node** table, char* title){
    Node* current = NULL;
    for(int i = 0; i < SIZE; i++){
        current = table[i];
        while(current != NULL){
            if(strcmp(current->manga.title, title) == 0){
                return current;
            }else{
                current = current->next;
            }
        }
    }
    return current;
}
Node* searchByID(Node** table, int id){
    int key = divisionHash(id);
    Node* current = table[key];
    while(current != NULL){
        if(current->manga.id = id){
            return current;
        } else {
            current = current->next;
        }
    }
    return current;
}
void addManga(Node** table){
    Manga new;
    int id;
    printf("\nType an ID (integer) for new Manga\n");
    scanf("%d", &id);
    while(searchByID(table, id) != NULL){
        printf("ID exists. Please type a new ID.\n");
        scanf("%d", &id);
    }
    new.id = id;
    FLUSH;
    printf("Type the title of new Manga\n");
    char* newTitle = getString();
    if(newTitle != NULL){
        new.title = newTitle;
    }
    printf("Type the author of new Manga\n");
    char* newAuthor = getString();
    if(newAuthor != NULL){
        new.author = newAuthor;
    }
    printf("Type the genre of new Manga\n");
    char* newGenre = getString();
    if(newAuthor != NULL){
        new.genre = newGenre;
    }
    printf("Type the publisher of new Manga\n");
    char* newPublisher = getString();
    if(newAuthor != NULL){
        new.publisher = newPublisher;
    }
    printf("Used? [y/n]\n");
    char yesorno;
    while((yesorno = getchar()) != 'y' && yesorno != 'n'){
        printf("Please enter either 'y' or 'n'.\n");
        yesorno = getchar();
    }
    if(yesorno == 'y'){
       new.used = true; 
    }else{
        new.used = false;
    }
    printf("Type the price.\n");
    double newPrice;
    scanf("%lf", &newPrice);
    while(newPrice < 0.0){
        printf("Please type a valid price value.\n");
        scanf("%lf", &newPrice);
    }
    new.price = newPrice;
    
    printf("Type the number of the book.\n");
    int newCount;
    scanf("%d", &newCount);
    while(newCount < 0 ){
        printf("Negative value is invalid. Please type a positive value.\n");
        scanf("%d", &newCount);
    }
    new.count = newCount;
    
    add(table, new);
    
    printf("\nNew book added!\n");
}

int mainScreen(){
    int a;
    printf("=============================================================\n");
    printf("Welcome to Manga Shop!\n");
    printf("=============================================================\n");
    printf("===== 0 - Exit === 1 - Add === 2 - Edit === 3 - Delete ====\n");
    printf("===== 4 - Search ==== 5 - Show All ==========================\n");
    printf("=============================================================\n");
    printf("Type an option: ");
    scanf("%d", &a);
    while (a != 1 && a != 2 && a != 3 && a != 4 && a != 0 && a != 5) {
        printf("Invalid Options. Please select a correct option.\n"
                "Type an option: ");
        scanf("%d", &a);
    }
    
    return a;
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
        free((*node)->manga.title);
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
