
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"
#include "fileIO.h"
#include "extra.h"
#include "freefunctions.h"
#include "print.h"
#include "bookfunctions.h"
#include "search.h"
#include "tree.h"

#define FLUSH stdin=freopen(NULL,"r",stdin)


//Screens
int mainScreen();

//Additional functionality
void filterByGenre(Node**);


int main() {
    //Store node pointers instead of storing the whole nodes
    Node** table = (Node**) malloc(SIZE * sizeof (Node*));
    

    //If table is NULL
    if (table == NULL) {
        exit(1);
    }

    initializeTable(table);

    readFile(table);

    int choice;
    while ((choice = mainScreen())) {
        if (choice == 1 || choice == 2 || choice == 3) {
            FLUSH;
            printLine();
            printf("Checking Authority \n");
            printLine();
            printf("Type Username: ");
            char* username = getString();
            printf("Type password: ");
            char* password = getString();
            if (strcmp(username, "Extrawork") == 0 &&
                    strcmp(password, "extrawork") == 0) {
                printLine();
                printf("\nConfirmed\n");
                printLine();
                switch (choice) {
                    case 1:
                        //Add
                        addManga(table);
                        break;
                    case 2:
                        //Edit
                        editManga(table);
                        break;
                    case 3:
                        //Delete
                        deleteManga(table);
                        break;
                }
            } else{
                printLine();
                printf("\nEXCESS DENIED\n");
                printLine();
            }
        } else if (choice == 4) {
            //Search
            searchManga(table, 0);
        } else if (choice == 5) {
            printf("\n==========================================\n");
            printAll(table);
            printf("==========================================\n\n");
        }
    }

    
    
    TreeNode* root = NULL;
    
    generateTree(table, &root, -1, 39, 0);
    generateTree(table, &root, 1, 40, SIZE);
    
    //writeFile(root);


    printLine();
    printf("Thanks for using our shop!\n");
    printLine();
    freeTable(&table);
    freeTree(root);



    return 0;

}

int mainScreen() {
    int a;
    printf("=============================================================\n");
    printf("=============== Welcome to Manga Shop! = ====================\n");
    printf("======================= 0 - Exit  ===========================\n");
    printf("================== ADMINISTRATOR OPTIONS ====================\n");
    printf("============== 1 - Add === 2 - Edit === 3 - Delete ==========\n");
    printf("======================== USER OPTIONS =======================\n");
    printf("============== 4 - Search ==== 5 - Show All =================\n");
    printf("=============================================================\n");
    printf("Type an option: ");
    FLUSH;
    scanf("%d", &a);
    while (a != 1 && a != 2 && a != 3 && a != 4 && a != 0 && a != 5) {
        printf("\n");
        printLine();
        printf("Invalid Options. Please select a correct option.\n");
        printLine();
        printf("Type an option: ");
        scanf("%d", &a);
    }

    return a;
}

