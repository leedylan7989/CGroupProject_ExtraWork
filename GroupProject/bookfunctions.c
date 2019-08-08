#include "bookfunctions.h"

/*
 * Parameter: table - hash table
 * This function contains necessary UIs for edit and
 * calls search function to search for a node.
 * If a node is found, the function calls edit() function to 
 * edit the searched node.
 * If not found, a message will be prompted and the function will exit.
 */
void editManga(Node** table, Node*** list) {
    //First, search a Manga to edit.
    printLine();
    printf("Search a Manga to edit\n");
    printLine();
    Node* node = searchManga(table, list, 1);
    if(!strcmp(node->manga.title,"search is canceled from searchManga")){
        printLine();
        printf("EDIT CANCELED\n");
        printLine();
        return;
    }
    int tryagain = 1;
    while(node == NULL && tryagain){
        printLine();
        printf("SEARCH FAILED. TRY SEARCH AGAIN? [y/n] \n");
        printLine();
        FLUSH;
        char c = getchar();
        if(c == 'y'){
           node = searchManga(table, list, 1); 
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
            printf("CONTINUE EDIT?[y/n] \n");
            printLine();
            FLUSH;
            c = getchar();
            checkYN(c);
        } while (c == 'y');
    }
}



/*
 * Parameter: table - hash table
 * This function contains necessary UIs for delete.
 * This function calls search function to search for a node with 
 * a user's search criteria.
 * Then, calls delete() function to delete the node.
 * If the search criteria does not exist in the table, prompts
 * a message. 
 */
void deleteManga(Node** table, Node*** list) {
    printLine();
    printf("Search the Manga you want to delete\n");
    printLine();
    
    Node* node = searchManga(table, list, 1);
    if (node == NULL) {
        //If the book is not found,
        //return the control to the caller.
        printLine();
        printf("BOOK NOT FOUND\n");
        printLine();
        return;
    }
    
    if(!strcmp(node->manga.title,"search is canceled from searchManga")){
        printLine();
        printf("DELETE CANCELED\n");
        printLine();
        return;
    }
    printNode(node);
    printLine();
    printf("DELETE: CONFIRMING...[y/n]\n");
    printLine();
    FLUSH;
    char c = getchar();
    checkYN(c);
    if (c == 'y') {
        //Delete from dictionary before deleting from the table
        for(int i = 0; i < 5; i++){
            deleteDictionary(list[i], node, i);
        }
        delete(table, node->manga.id);
        printLine();
        printf("DELETE SUCCESSFUL\n");
        printLine();
    } else {
        printLine();
        printf("DELETE CANCELED\n");
        printLine();
    }
}

/*
 * Parameter: table - hash table
 * This function contains necessary UIs for add.
 * This function asks for new book's information to a user.
 * Then, creates a new book object with the information and
 * calls add() function to add a node to the table.
 */
void addManga(Node** table, Node*** list) {
    Manga new;
    int id;
    printLine();
    printf("Type an ID (integer) for new Manga\n");
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
    printf("ADD: CONFIRMING...[y/n]\n");
    printLine();
    FLUSH;
    char c = getchar();
    checkYN(c);
    if (c == 'y'){
        add(table, list, new);
        printLine();
        printf("NEW BOOK ADDED!\n");
        printLine();
    } else{
        printLine();
        printf("ADD CANCELED\n");
        printLine();
    }
}

void purchaseManga(Node** table, Node*** dictionaryList) {
    printLine();
    printf("Search a book to purchase\n");
    printLine();
    Node* book = searchManga(table, dictionaryList, 1);
    if(!strcmp(book->manga.title,"search is canceled from searchManga")){
        printLine();
        printf("PURCHASE CANCELED\n");
        printLine();
        return;
    }
    if (book == NULL) {
        printLine();
        printf("PURCHASE FAILED\n");
        printLine();
    } else {
        printLine();
        printf("%d: PURCHASE CONFIRMING...[y/n]\n", book->manga.id);
        printLine();
        FLUSH;
        char c = getchar();
        checkYN(c);
        if (c == 'y') {
            //Delete from dictionary before deleting from the table
            for (int i = 0; i < 5; i++) {
                deleteDictionary(dictionaryList[i], book, i);
            }
            delete(table, book->manga.id);
            printLine();
            printf("PURCHASE COMPLETED\n");
            printLine();
        } else {
            printLine();
            printf("PURCHASE CANCELED\n");
            printLine();
        }
    }
}