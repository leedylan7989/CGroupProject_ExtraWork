#include "bookfunctions.h"

void editManga(Node** table) {
    //First, search a Manga to edit.
    printLine();
    printf("Search a Manga to edit\n");
    printLine();
    Node* node = searchManga(table, 1);
    int tryagain = 1;
    while(node == NULL && tryagain){
        printLine();
        printf("SEARCH FAILED. TRY SEARCH AGAIN? [y/n] \n");
        printLine();
        FLUSH;
        char c = getchar();
        if(c == 'y'){
           node = searchManga(table,1); 
        } else if(c == 'n'){
            tryagain = 0;
        } else{
            printLine();
            printf("INVALID OPTION. TRY AGAIN.\n");
            printLine();
        }
    }
    if (node != NULL) {
        char c;
        do {
            //Iterating edit() until user doesn't have anything to edit
            const char* arr[] = {"title", "author", "genre", "publisher",
                "used", "price"};
            printLine();
            for (int i = 0; i < 6; i++) {
                printf("%d - Edit %s\n", i + 1, arr[i]);
            }
            printLine();
            //Getting the user choice
            int choice;
            FLUSH;
            scanf("%d", &choice);
            FLUSH;
            
            edit(choice, node);
            printLine();
            printf("\nCONTINUE EDIT?[y/n] \n");
            printLine();
            FLUSH;
            c = getchar();
            checkYN(c);
        } while (c == 'y');
    }
}



void deleteManga(Node** table) {
    printLine();
    printf("Which Manga do you want to delete?\n"
            "1 - Search by ID\n2 - Search by Title\n");
    printLine();
    int choice;
    scanf("%d", &choice);
    while (choice != 1 && choice != 2) {
        printLine();
        printf("Please select the valid options.\n");
        printLine();
        scanf("%d", choice);
    }

    if (choice == 1) {
        printLine();
        printf("Type the ID you want to delete.\n");
        printLine();
        int id;
        scanf("%d", &id);
        while (id < 0) {
            printLine();
            printf("Please select a valid id.\n");
            printLine();
            scanf("%d", &id);
        }
        
        Node* node = NULL;
        if ((node = searchByID(table, id)) != NULL) {
            printNode(node);
            printLine();
            printf("DELETE: CONFIRMING...[y/n]\n");
            printLine();
            FLUSH;
            char c = getchar();
            checkYN(c);
            if (c == 'y') {
                delete(table, id);
                printLine();
                printf("\nDELETE SUCCESSFUL\n");
                printLine();
            } else {
                printLine();
                printf("\nDELETE CANCELED\n");
                printLine();
            }
        } else {
            printLine();
            printf("BOOK NOT FOUND\n");
            printLine();
        }
    } else if (choice == 2) {
        printLine();
        printf("Type the title you want to delete.\n");
        printLine();
        FLUSH;
        char* deleteTitle = getString();

        Node* node = searchByTitle(table, deleteTitle);
        if (node != NULL) {
            printNode(node);
            printLine();
            printf("DELETE: CONFIRMING...[y/n]\n");
            printLine();
            FLUSH;
            char c = getchar();
            checkYN(c);
            if (c == 'y') {
                delete(table, node->manga.id);
                printLine();
                printf("\nDELETE SUCCESSFUL\n");
                printLine();
            } else {
                printLine();
                printf("\nDELETE CANCELED\n");
                printLine();
            }
        } else {
            printLine();
            printf("BOOK NOT FOUND\n");
            printLine();
        }
    }
}


void addManga(Node** table) {
    Manga new;
    int id;
    printLine();
    printf("\nType an ID (integer) for new Manga\n");
    printLine();
    scanf("%d", &id);
    while (searchByID(table, id) != NULL) {
        printLine();
        printf("ID exists. Please type a new ID.\n");
        printLine();
        scanf("%d", &id);
    }
    new.id = id;
    FLUSH;
    printLine();
    printf("Type the title of new Manga\n");
    printLine();
    char* newTitle = getString();
    if (newTitle != NULL) {
        new.title = newTitle;
    }
    printLine();
    printf("Type the author of new Manga\n");
    printLine();
    char* newAuthor = getString();
    if (newAuthor != NULL) {
        new.author = newAuthor;
    }
    printLine();
    printf("Type the genre of new Manga\n");
    printLine();
    char* newGenre = getString();
    if (newAuthor != NULL) {
        new.genre = newGenre;
    }
    printLine();
    printf("Type the publisher of new Manga\n");
    printLine();
    char* newPublisher = getString();
    if (newAuthor != NULL) {
        new.publisher = newPublisher;
    }
    printLine();
    printf("Used? [y/n]\n");
    printLine();
    char yesorno = getchar();
    checkYN(yesorno);
    if (yesorno == 'y') {
        new.used = true;
    } else {
        new.used = false;
    }
    printLine();
    printf("Type the price.\n");
    printLine();
    double newPrice;
    scanf("%lf", &newPrice);
    while (newPrice < 0.0) {
        printLine();
        printf("Please type a valid price value.\n");
        printLine();
        scanf("%lf", &newPrice);
    }
    new.price = newPrice;

    printLine();
    printf("\nADD: CONFIRMING...[y/n]\n");
    printLine();
    FLUSH;
    char c = getchar();
    checkYN(c);
    if (c == 'y'){
        add(table, new);
        printLine();
        printf("\nNEW BOOK ADDED!\n");
        printLine();
    } else{
        printLine();
        printf("\nADD CANCELED\n");
        printLine();
    }
}