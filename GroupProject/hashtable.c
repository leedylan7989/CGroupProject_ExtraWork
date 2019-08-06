#include "hashtable.h"

//Calculating key using division method

int divisionHash(int id) {
    return id % SIZE;
}


void initializeTable(Node** table, int size) {
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
}


