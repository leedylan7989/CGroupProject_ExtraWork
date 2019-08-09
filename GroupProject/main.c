
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
#include "process.h"

#define FLUSH stdin=freopen(NULL,"r",stdin)




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
    
    
    process(dictionaryList,table);



    TreeNode* root = NULL;

    generateTree(table, &root, -1, 39, 0);
    generateTree(table, &root, 1, 40, SIZE);

    writeFile(root);


    printLine();
    printf("Thanks for using our shop!\n");
    printLine();
    freeTable(&table);
    freeTree(root);
    freeDictionary(dictionaryList);

    return 0;

}
