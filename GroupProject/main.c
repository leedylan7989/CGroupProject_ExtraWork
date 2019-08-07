
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
#include "dictionary.h"

#define FLUSH stdin=freopen(NULL,"r",stdin)


//Screens
int mainScreen();


int main() {
    //Store node pointers instead of storing the whole nodes
    Node** table = (Node**) malloc(SIZE * sizeof (Node*));


    //If table is NULL
    if (table == NULL) {
        exit(1);
    }

    initializeTable(table, SIZE);

    readFile(table);

    Node*** dictionaryList = (Node***) malloc(5 * sizeof (Node**));
    //String dictionary is made of 27 indexes
    //A string dictionary uses first character of a string
    //to sort
    //a - z & A - Z = 0 - 25
    //Other special characters: 26
    for (int i = 0; i < 4; i++) {
        dictionaryList[i] = (Node**) malloc(27 * sizeof (Node*));
        if (dictionaryList[i] == NULL) {
            exit(1);
        }
        initializeTable(dictionaryList[i], 27);
    }
    //Boolean dictionary is made of 2 indexes
    //Index 0 storing all false values
    //Index 1 storing all true values
    dictionaryList[4] = (Node**) malloc(2 * sizeof (Node*));
    if (dictionaryList[4] == NULL) {
        exit(1);
    }
    initializeTable(dictionaryList[4], 2);


    for (int i = 0; i < 5; i++) {
        createDictionary(table, dictionaryList, i);
    }

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
                printf("Confirmed\n");
                printLine();
                switch (choice) {
                    case 1:
                        //Add
                        addManga(table, dictionaryList);
                        break;
                    case 2:
                        //Edit
                        editManga(table, dictionaryList);
                        break;
                    case 3:
                        //Delete
                        deleteManga(table, dictionaryList);
                        break;
                }
            } else {
                printLine();
                printf("\nEXCESS DENIED\n");
                printLine();
            }
        } else if (choice == 4) {
            //Search
            searchManga(table, dictionaryList, 0);
        } else if (choice == 5) {
            printf("\n==========================================\n");
            printAll(table);
            printf("==========================================\n\n");
        } else if (choice == 6) {
            purchaseManga(table, dictionaryList);
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
    freeDictionary(dictionaryList);

    return 0;

}

int mainScreen() {
    int a;
    printf("=============================================================\n");
    printf("=============== Welcome to Manga Shop! = ====================\n");
    printf("======================= 0 - Exit  ===========================\n");
    printf("================== ADMINISTRATOR OPTIONS ====================\n");
    printf("=========== 1 - Add === 2 - Edit === 3 - Delete =============\n");
    printf("======================== USER OPTIONS =======================\n");
    printf("========= 4 - Search === 5 - Show All === 6 - Purchase ======\n");
    printf("=============================================================\n");
    printf("Type an option: ");
    FLUSH;
    scanf("%d", &a);
    while (a < 0 || a > 6) {
        printf("\n");
        printLine();
        printf("Invalid Options. Please select a correct option.\n");
        printLine();
        FLUSH;
        printf("Type an option: ");
        scanf("%d", &a);
    }

    return a;
}

