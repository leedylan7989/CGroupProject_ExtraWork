#include "hashtable.h"

//All functions done by Heon Lee

//Calculating key using division method

int divisionHash(int id) {
    return id % SIZE;
}


/*
 * Initializes a hash table
 */
void initializeTable(Node** table, int size) {
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
}


