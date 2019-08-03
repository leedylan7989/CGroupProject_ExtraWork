#include "bookfunctions.h"

void editManga(Node** table) {
    //First, search a Manga to edit.
    printf("Search a Manga to edit\n");
    Node* node = searchManga(table, 1);
    int tryagain = 1;
    while(node == NULL && tryagain){
        printf("SEARCH FAILED. TRY SEARCH AGAIN? [y/n] \n");
        FLUSH;
        char c = getchar();
        if(c == 'y'){
           node = searchManga(table,1); 
        } else if(c == 'n'){
            tryagain = 0;
        } else{
            printf("INVALID OPTION. TRY AGAIN.\n");
        }
    }
    if (node != NULL) {
        char c;
        do {
            //Iterating edit() until user doesn't have anything to edit
            const char* arr[] = {"title", "author", "genre", "publisher",
                "used", "price"};
            for (int i = 0; i < 6; i++) {
                printf("%d - Edit %s\n", i + 1, arr[i]);
            }
            //Getting the user choice
            int choice;
            scanf("%d", &choice);
            FLUSH;
            
            edit(choice, node);
            printf("\nCONTINUE EDIT?[y/n] \n");
            FLUSH;
            c = getchar();
            checkYN(c);
        } while (c == 'y');
    }
}



bool deleteManga(Node** table) {
    printf("Which Manga do you want to delete?\n"
            "1 - Search by ID\n2 - Search by Title\n");
    int choice;
    scanf("%d", &choice);
    while (choice != 1 && choice != 2) {
        printf("Please select the valid options.\n");
        scanf("%d", choice);
    }

    if (choice == 1) {
        printf("Type the ID you want to delete.\n");
        int id;
        scanf("%d", &id);
        while (id < 0) {
            printf("Please select a valid id.\n");
            scanf("%d", &id);
        }

        if (searchByID(table, id) != NULL) {
            printf("DELETE: CONFIRMING...");
            char c = getchar();
            checkYN(c);
            if (c == 'y') {
                delete(table, id);
                return true;
            } else{
                return false;
            }
        } else {
            return false;
        }
    } else if (choice == 2) {
        printf("Type the title you want to delete.\n");
        char* deleteTitle = getString();

        Node* node = searchByTitle(table, deleteTitle);
        if (node != NULL) {
            delete(table, node->manga.id);
            return true;
        } else {
            return false;
        }
    }
    return false;
}


void addManga(Node** table) {
    Manga new;
    int id;
    printf("\nType an ID (integer) for new Manga\n");
    scanf("%d", &id);
    while (searchByID(table, id) != NULL) {
        printf("ID exists. Please type a new ID.\n");
        scanf("%d", &id);
    }
    new.id = id;
    FLUSH;
    printf("Type the title of new Manga\n");
    char* newTitle = getString();
    if (newTitle != NULL) {
        new.title = newTitle;
    }
    printf("Type the author of new Manga\n");
    char* newAuthor = getString();
    if (newAuthor != NULL) {
        new.author = newAuthor;
    }
    printf("Type the genre of new Manga\n");
    char* newGenre = getString();
    if (newAuthor != NULL) {
        new.genre = newGenre;
    }
    printf("Type the publisher of new Manga\n");
    char* newPublisher = getString();
    if (newAuthor != NULL) {
        new.publisher = newPublisher;
    }
    printf("Used? [y/n]\n");
    char yesorno;
    while ((yesorno = getchar()) != 'y' && yesorno != 'n') {
        printf("Please enter either 'y' or 'n'.\n");
        yesorno = getchar();
    }
    if (yesorno == 'y') {
        new.used = true;
    } else {
        new.used = false;
    }
    printf("Type the price.\n");
    double newPrice;
    scanf("%lf", &newPrice);
    while (newPrice < 0.0) {
        printf("Please type a valid price value.\n");
        scanf("%lf", &newPrice);
    }
    new.price = newPrice;

    printf("\nADD: CONFIRMING...[y/n]\n");
    char c = getchar();
    checkYN(c);
    if (c == 'y'){
        add(table, new);
        printf("\nNEW BOOK ADDED!\n");
    } else{
        printf("\nADD CANCELED\n");
    }
}