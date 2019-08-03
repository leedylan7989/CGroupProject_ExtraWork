
#include "hashbasic.h"

//Heon Lee

void add(Node** table, Manga manga) {
    int key = divisionHash(manga.id);
    Node* temp = (Node*) malloc(sizeof (Node));
    //If temp is NULL
    if (temp == NULL) {
        exit(1);
    }
    temp->manga = manga;
    temp->next = NULL;
    if (table[key] == NULL) {
        table[key] = temp;
    } else {
        Node* current = table[key];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
}

//Heon Lee

void delete(Node** table, int id) {
    int key = divisionHash(id);
    bool found = false;
    Node* current = table[key];
    Node* prev = NULL;
    while (!found && current != NULL) {
        if (current->manga.id == id) {
            found = true;
        } else {
            if (current->next != NULL) {
                prev = current;
            }
            current = current->next;
        }
    }

    if (table[key]->manga.id == current->manga.id) {
        //found node is at first of the linked list
        table[key] = current->next;
    } else if (current->next == NULL) {
        //found node is at the end
        prev->next = NULL;
    } else {
        //Mid-way
        prev->next = current->next;
        current->next = NULL;
    }
    if (found) {
        freeNode(&current);
    }
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
void edit(int choice, Node* node) {
    if (choice == 1 || choice == 2 || choice == 3 ||
            choice == 4) {
        if (choice == 1){
                printf("\nOLD VALUE: %s\n", node->manga.title);
            printf("Type a new title for Manga\n");
        }
        else if (choice == 2){
                printf("\nOLD VALUE: %s\n", node->manga.author);
            printf("Type a new author for Manga\n");
        }
        else if (choice == 3){
                printf("\nOLD VALUE: %s\n", node->manga.genre);
            printf("Type a new genre for Manga\n");
        }
        else{
                printf("\nOLD VALUE: %s\n", node->manga.publisher);
            printf("Type a new publisher for Manga\n");
        }
        char* new = getString();
        printf("EDIT? [y/n]\n");
        char c = getchar();
        checkYN(c);
        if (new != NULL && c == 'y') {
            if (choice == 1) {
                node->manga.title = new;
            } else if (choice == 2) {
                node->manga.author = new;
            } else if (choice == 3) {
                node->manga.genre = new;
            } else {
                node->manga.publisher = new;
            }
            printf("\nEDIT SUCCESSFUL\n");
        } else {
            printf("\nEDIT CANCELED\n");
        }
    } else if (choice == 5) {
        //Change used
        printf("EDIT? [y/n]\n");
        char c = getchar();
        checkYN(c);
        if (c == 'y') {
            node->manga.used = !node->manga.used;
            printf("%s", node->manga.used ? "\nCHANGED FROM NEW TO USED\n" :
                    "\nCHANGED FROM USED TO NEW\n");
        }
    } else if (choice == 6) {
        //Price
        double new;
        printf("Type a new price for Manga.\n");
        while (new < 0.0) {
            printf("Negative value is not a valid price.\n");
            scanf("%lf", &new);
        }
        printf("EDIT? [y/n]\n");
        char c = getchar();
        checkYN(c);
        if (c == 'y') {
            node->manga.price = new;
        }
    }
}
