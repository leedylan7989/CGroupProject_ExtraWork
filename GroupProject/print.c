#include "print.h"



void printAll(Node** table) {
    Node* current;
    for (int i = 0; i < SIZE; i++) {
        current = table[i];
        while (current != NULL) {
            printNode(current);
            current = current->next;
            printf("-------------------------------------------\n");
        }
    }
}

void printNode(Node* node) {
    printLine();
    printf("\nID: %d\nTitle: %s\nAuthor: %s\nGenre: %s\nPublisher: %s\n"
            "Price: %.2lf\n", node->manga.id, node->manga.title,
            node->manga.author, node->manga.genre, node->manga.publisher,
            node->manga.price);
    if (node->manga.used) {
        printf("Used\n");
    } else {
        printf("New\n");
    }
    printLine();
}

void printLine(){
    printf("=============================================================\n");
}