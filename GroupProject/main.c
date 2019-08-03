
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"
#include "fileIO.h"
#include "hashbasic.h"
#include "getInput.h"
#include "freefunctions.h"
#include "print.h"
#include "bookfunctions.h"
#include "search.h"

#define FLUSH stdin=freopen(NULL,"r",stdin)


typedef struct treenode{
    Node* value;
    struct treenode *left, *right;
}TreeNode;

//IO
void writeFile();

//Screens
int mainScreen();

//Additional functionality
void filterByGenre(Node**);
void sort(Node**);

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
            printf("Checking Authority \nType Username: ");
            char* username = getString();
            printf("Type password: ");
            char* password = getString();
            if (strcmp(username, "Extrawork") == 0 &&
                    strcmp(password, "extrawork") == 0) {
                printf("\nConfirmed\n");
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
                        if (deleteManga(table)) {
                            printf("\nDELETE SUCCESSFUL\n");
                        } else {
                            printf("\nDELETE CANCELED\n");
                        }
                        break;
                }
            } else{
                printf("\nEXCESS DENIED\n");
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


    
    //writeFile(table);


    printf("Thanks for using our shop!\n");
    freeTable(&table);



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
    scanf("%d", &a);
    while (a != 1 && a != 2 && a != 3 && a != 4 && a != 0 && a != 5) {
        printf("Invalid Options. Please select a correct option.\n"
                "Type an option: ");
        scanf("%d", &a);
    }

    return a;
}

