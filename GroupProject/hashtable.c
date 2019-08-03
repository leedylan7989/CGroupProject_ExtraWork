#include "hashtable.h"

//Calculating key using division method

int divisionHash(int id) {
    return id % SIZE;
}


void initializeTable(Node** table) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = NULL;
    }
}


