
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


/*
 * Parameter: c - a character to check
 * If a character is not 'y' or 'n', then the function
 * asks again until the user types 'y' or 'n'.
 */
void checkYN(char c){
    while (c != 'y' && c != 'n') {
        printLine();
        printf("\nINVALID OPTION. y OR n \n");
        printLine();
        FLUSH;
        char c = getchar();
    }
}

int characterToIndex(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 112)) {
        //a - z A - Z
        for (int i = 0; i < 26; i++) {
            if (c == 65 + i || c == 97 + i) {
                return i;
            }
        }
    }

    //Other special characters and numbers
    return 26;
}

int boolToIndex(bool c) {
    //false == 0, true == 1
    int i = c;
    return i;
}

Node* buildList(Node* head, Node* node){
    if(head == NULL){
        return node;
    }
    Node* current = head;
    while(current->nextList != NULL){
        current = current->nextList;
    }
    current->nextList = node;
    return head;
    
}


void clearList(Node* head){
    if(head != NULL){
        clearList(head->nextList);
        head->nextList = NULL;
    }
}

int validateOption(int choice, int startRange, int endRange){
    while (choice < startRange || choice > endRange) {
        printLine();
        printf("Please select the valid options. [%d-%d]\n", startRange,
                endRange);
        printLine();
        FLUSH;
        printf("Type an option: ");
        scanf("%d", &choice);
    }
    FLUSH;
    return choice;
}

int optionScreen(int a) {
    int i;
    printLine();
    if (a == 1)
        printf("Do you want to add another book?\n");
    if (a == 2)
        printf("Do you want to edit another book?\n");
    if (a == 3)
        printf("Do you want to delete another book?\n");
    printf("0 - No\n");
    printf("1 - Yes\n");
    printLine();
    scanf("%d", &i);
    i = validateOption(i, 0, 1);
    FLUSH;
    return i;
}