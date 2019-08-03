#include "freefunctions.h"
//Heon Lee
//Frees a single Node

void freeNode(Node** node) {
    if ((*node)->manga.author != NULL) {
        free((*node)->manga.author);
    }

    if ((*node)->manga.genre != NULL) {
        free((*node)->manga.genre);
    }

    if ((*node)->manga.title != NULL) {
        free((*node)->manga.title);
    }

    if ((*node)->manga.publisher != NULL) {
        free((*node)->manga.publisher);
    }

    //Make sure node->next is not pointing to anything
    if ((*node)->next != NULL) {
        (*node)->next = NULL;
    }

    free(*node);
}


//Heon Lee
//Frees a list.
//A bucket

void freeList(Node** head) {
    //Move to the tail node of the list
    while (*head != NULL) {
        Node* temp = *head;
        *head = (*head)->next;
        freeNode(&temp);
    }
}

//Heon Lee
//Frees the whole table

void freeTable(Node*** table) {
    for (int i = 0; i < SIZE; i++) {
        freeList(&((*table)[i]));
    }
    free(*table);
}
