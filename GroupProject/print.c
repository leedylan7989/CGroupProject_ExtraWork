#include "print.h"
#include "tree.h"


//All functions done by Heon Lee

/*
 * Prints all nodes in a hash table
 */
void printAll(Node** table) {
    Node* current;
    for (int i = 0; i < SIZE; i++) {
        current = table[i];
        while (current != NULL) {
            printNode(current);
            current = current->next;
        }
    }
}

/*
 * Prints a single node
 */
void printNode(Node* node) {
    printLine();
    printf("ID: %d\nTitle: %s\nAuthor: %s\nGenre: %s\nPublisher: %s\n"
            "Price: $%.2lf\n", node->manga.id, node->manga.title,
            node->manga.author, node->manga.genre, node->manga.publisher,
            node->manga.price);
    if (node->manga.used) {
        printf("Used\n");
    } else {
        printf("New\n");
    }
    printLine();
}

/*
 * Prints a linked list
 */
void printList(Node* head){
    while(head != NULL){
        printNode(head);
        head = head->nextList;
    }
}


/*
 * Prints a second linked list created from a result linked list
 */
void printSecondList(Node* head){
    while(head != NULL){
        printNode(head);
        head = head->nextSecondList;
    }
}

/*
 * Prints treenodes using Inorder Traversal
 */
void printInorder(TreeNode* root){
    if(root != NULL){
        printInorder(root->left);
        printNode(root->node);
        printInorder(root->right);
    }
}

/*
 * Prints treenodes using Inorder Traversal in reverse
 */
void printInorderReverse(TreeNode* root){
    if(root != NULL){
        printInorderReverse(root->right);
        printNode(root->node);
        printInorderReverse(root->left);
    }
}

/*
 * Self explanatory
 */
void printLine(){
    printf("=============================================================\n");
}