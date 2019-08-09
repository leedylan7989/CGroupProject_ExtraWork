#include "process.h"


void process(Node*** dictionaryList, Node** table){
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
                int i = 1;
                switch (choice) {
                    case 1:
                        //Add
                        while (i) {
                            addManga(table, dictionaryList);
                            i = optionScreen(choice);
                            i = validateOption(i, 0, 1);
                        }
                        break;
                    case 2:
                        //Edit
                        while(i){
                            editManga(table, dictionaryList);
                            i = optionScreen(choice);
                            i = validateOption(i, 0, 1);
                        }
                        break;
                    case 3:
                        //Delete
                        while (i) {
                            deleteManga(table, dictionaryList);
                            i = optionScreen(choice);
                            i = validateOption(i, 0, 1);
                        }
                        break;
                }
            } else {
                printLine();
                printf("\nACCESS DENIED\n");
                printLine();
            }
        } else if (choice == 4) {
            //Search
            searchManga(table, dictionaryList, 0);
        } else if (choice == 5) {
            printLine();
            printAll(table);
            printLine();
        } else if (choice == 6) {
            purchaseManga(table, dictionaryList);
        }
    }
}