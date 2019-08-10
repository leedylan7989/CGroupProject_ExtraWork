
#include "extra.h"

//All of the functions here are done by Heon Lee

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
 * Heon Lee
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

/*
 * Heon Lee
 * This function changes a character to a dictionary index
 */
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

/*
 * This function changes a boolean value to a dictionary index
 */
int boolToIndex(bool c) {
    //false == 0, true == 1
    int i = c;
    return i;
}


/*
 * A function to return a size according to the given choice
 * num is an option that selects a dictionary
 */
int optionToSize(int num){
    if (num == 4) {
        return 2;
    } else {
        return 27;
    }
}

/*
 * Builds a list. 
 * If doubleSearch == 1, then build a list from a result list
 */
Node* buildList(Node* head, Node* node, int doubleSearch) {
    if (head == NULL) {
        return node;
    }
    Node* current = head;
    if (!doubleSearch) {
        while (current->nextList != NULL) {
            current = current->nextList;
        }
        current->nextList = node;
    } else {
        while (current->nextSecondList != NULL) {
            current = current->nextSecondList;
        }
        current->nextSecondList = node;
    }
    return head;
}

/*
 * Clears a result list
 */
void clearList(Node* head) {
    if (head != NULL) {
        clearList(head->nextList);
        head->nextList = NULL;
    }
    
}

/*
 * Switches a secondary list to a main result list
 */
void switchList(Node* head) {
    if (head != NULL) {
        switchList(head->nextSecondList);
        head->nextList = head->nextSecondList;
        head->nextSecondList = NULL;
    }
    
}

/*
 * Validates options
 */
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

/*
 * Validates options with an exception.
 * This exception is a value that should not be selected but in
 * the given range.
 */
int validateOptionWithException(int choice, int startRange, int endRange,
        int exception){
    while (choice < startRange || choice > endRange ||
            choice == exception) {
        printLine();
        printf("Please select the valid options. [%d-%d] except %d\n", startRange,
                endRange, exception);
        printLine();
        FLUSH;
        printf("Type an option: ");
        scanf("%d", &choice);
    }
    FLUSH;
    return choice;
}



/*
 * 
 * Displays an option screen and takes a user input
 */
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


/*
 * Displays a main screen and takes a user input
 */
int mainScreen() {
    int a;
    printf("=============================================================\n");
    printf("=============== Welcome to Manga Shop! ======================\n");
    printf("======================= 0 - Exit  ===========================\n");
    printf("================== ADMINISTRATOR OPTIONS ====================\n");
    printf("=========== 1 - Add === 2 - Edit === 3 - Delete =============\n");
    printf("======================== USER OPTIONS =======================\n");
    printf("========= 4 - Search === 5 - Show All === 6 - Purchase ======\n");
    printf("=============================================================\n");
    printf("Type an option: ");
    FLUSH;
    scanf("%d", &a);
    a = validateOption(a, 0, 6);

    return a;
}