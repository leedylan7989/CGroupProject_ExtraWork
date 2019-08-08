#include "search.h"



//Searching Manga from the hash table
//If select == 0, then return null.
//If select == 1, return a selected Manga.
//A caller will only set select to 1
//when a caller needs to retreive
//a selected record.

Node* searchManga(Node** table, Node*** list, int retrieve) {
    //Search
    printLine();
    printf("1 - Search by ID\n2 - Search by Title\n");
    printf("3 - Search by Author\n4 - Search by Genre\n");
    printf("5 - Search by Publisher\n6 - Search Used/New\n");
    printf("0 - Exit\n");
    int choice;
    printLine();
    scanf("%d", &choice);
    FLUSH;
    while (choice < 0 && choice > 6) {
        printLine();
        printf("Please select the valid options. [1-6]\n");
        printLine();
        scanf("%d", &choice);
        FLUSH;
    }

    Node* node = NULL;
    if (choice == 1) {
        printLine();
        printf("Type the ID you want to search.\n");
        printLine();
        int id;
        scanf("%d", &id);
        while (id < 0) {
            printLine();
            printf("Please select a valid id.\n");
            printLine();
            scanf("%d", &id);
        }
        node = searchByID(table, id);
        if (node != NULL) {
            printNode(node);
        } else {
            printLine();
            printf("\nSEARCH FAILED. ID NOT FOUND.\n");
            printLine();
        }
    } else if (choice >= 2 && choice < 7) {
        printLine();
        if(choice == 2)
            printf("Type the title you want to search.\n");
        else if (choice == 3)
            printf("Type the author you want to search.\n");
        else if (choice == 4)
            printf("Type the genre you want to search.\n");
        else if (choice == 5)
            printf("Type the publisher you want to search.\n");
        else if (choice == 6)
            printf("Type 'used' for used books and 'new' for new books\n");
        printLine();
        char* searchString = getString();

        node = searchDictionary(list[choice-2], searchString, choice-2);
        if (node != NULL) {
            printList(node);
        } else {
            printLine();
            printf("\nSEARCH FAILED. BOOK NOT FOUND.\n");
            printLine();
        }
    } else if (choice == 0){
        Manga manga;
        manga.title = "search is canceled from searchManga";
        Node* exit;
        exit->manga = manga;
        return exit;
    }
    Node* head = node;
    if (node != NULL && choice != 1 && retrieve){
        printLine();
        printf("\nSELECT ONE BOOK AND TYPE THE ID.\n");
        printLine();
        int id;
        FLUSH;
        do {
            scanf("%d", &id);
            FLUSH;
            node = searchByID(table, id);
            if(node == NULL){
                printLine();
                printf("ID NOT FOUND. PLEASE CHOOSE ANOTHER ID.\n");
                printLine();
            }
        } while (node == NULL);
    }
    
    clearList(head);
    
    return node;
}

Node* searchDictionary(Node** dictionary, char* searchString, int num) {
    int index;
    if (num == 4) {
        if(strcmp("used", searchString) == 0 || 
                strcmp("Used", searchString) == 0){
            index = 1;
        } else if(strcmp("new", searchString) == 0 || 
                strcmp("New", searchString) == 0){
            index = 0;
        } else {
            printLine();
            printf("PLEASE TYPE EITHER 'used' OR 'new'. RETURNING TO THE MENU\n");
            printLine();
            return NULL;
        }
    } else {
        index = characterToIndex(searchString[0]);
    }
    
    Node* head = NULL;
    Node* current = dictionary[index];
    while (current != NULL) {
        if (num == 0) {//Title
            if (strcmp(current->manga.title, searchString) == 0) {
                head = buildList(head, current);
            }
            current = current->nextTitle;
        } else if (num == 1) {//Author
            if (strcmp(current->manga.author, searchString) == 0) {
                head = buildList(head, current);
            }
            current = current->nextAuthor;
        } else if (num == 2) { //Genre
            if (strstr(current->manga.genre, searchString) != NULL) {
                head = buildList(head, current);
            }
            current = current->nextGenre;
        } else if (num == 3) {//Publisher
            if (strcmp(current->manga.publisher, searchString) == 0) {
                head = buildList(head, current);
            }
            current = current->nextPublisher;
        } else if (num == 4) {//Used
            head = buildList(head, current);
            current = current->nextUsed;
        }
    }
    
    return head;
}

Node* searchByID(Node** table, int id) {
    int key = divisionHash(id);
    Node* current = table[key];
    while (current != NULL) {
        if (current->manga.id == id) {
            return current;
        } else {
            current = current->next;
        }
    }
    return current;
}