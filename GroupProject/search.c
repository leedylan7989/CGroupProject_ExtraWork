#include "search.h"



//Searching Manga from the hash table
//If select == 0, then return null.
//If select == 1, return a selected Manga.
//A caller will only set select to 1
//when a caller needs to retreive
//a selected record.

Node* searchManga(Node** table, int select) {
    //Search
    printLine();
    printf("\n1 - Search by ID\n2 - Search by Title\n");
    int choice;
    printLine();
    scanf("%d", &choice);
    FLUSH;
    while (choice != 1 && choice != 2) {
        printLine();
        printf("Please select the valid options.\n");
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
    } else if (choice == 2) {
        printLine();
        printf("Type the title you want to search.\n");
        printLine();
        char* title = getString();

        node = searchByTitle(table, title);
        if (node != NULL) {
            printNode(node);
        } else {
            printLine();
            printf("\nSEARCH FAILED. BOOK NOT FOUND.\n");
            printLine();
        }
    }
    
    if (select)
        return node;
    else
        return NULL;
}

Node* searchByTitle(Node** table, char* title) {
    Node* current = NULL;
    for (int i = 0; i < SIZE; i++) {
        current = table[i];
        while (current != NULL) {
            if (strcmp(current->manga.title, title) == 0) {
                return current;
            } else {
                current = current->next;
            }
        }
    }
    return current;
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