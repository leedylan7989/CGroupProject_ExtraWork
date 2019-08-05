
#include "extra.h"
//Heon Lee
//This function waits for user input
//and allocates the input to Heap
//Returns the memory address of the input
//to the caller

char* getString() {
    char tmp[100] = {0};

    fgets(tmp, sizeof (tmp), stdin);
    tmp[strcspn(tmp, "\n")] = 0;

    char* str = NULL;
    if (strlen(tmp) > 0) {
        str = (char*) malloc((strlen(tmp) + 1) * sizeof (char));
        if (str == NULL) {
            exit(1);
        }
        strcpy(str, tmp);
    }
    FLUSH;
    return str;
}



void checkYN(char c){
    while (c != 'y' && c != 'n') {
        printLine();
        printf("\nINVALID OPTION. y OR n \n");
        printLine();
        FLUSH;
        char c = getchar();
    }
}