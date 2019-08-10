#include "search.h"



//Searching Manga from the hash table
//If select == 0, then return null.
//If select == 1, return a selected Manga.
//A caller will only set select to 1
//when a caller needs to retreive
//a selected record.

/*
 * Vladyslav Hrusha
 * This function searches for a record
 * 
 * 
 * Heon Lee and Nikita Kartavyi also modified this function
 */
Node* searchManga(Node** table, Node*** list, int retrieve) {
    //Search
    //Search Menu
    printLine();
    printf("1 - Search by ID\n2 - Search by Title\n");
    printf("3 - Search by Author\n4 - Search by Genre\n");
    printf("5 - Search by Publisher\n6 - Search Used/New\n");
    printf("7 - Search by Price Range\n8 - Search by ID Range\n");
    printf("0 - Exit\n");
    int choice;
    printLine();
    scanf("%d", &choice);
    FLUSH;
    //Validation
    choice = validateOption(choice, 0, 8);

    Node* node = NULL;
    if (choice == 1) { //ID search
        printLine();
        printf("Type the ID you want to search.\n");
        printLine();
        int id;
        scanf("%d", &id);
        while (id < 0) {
            printLine();
            printf("Please select a valid id.\n");
            printLine();
            scanf("%d", &id);
        }
        node = searchByID(table, id);
        //Print the searched node
        if (node != NULL) {
            printNode(node);
        } else {
            printLine();
            printf("SEARCH FAILED. ID NOT FOUND.\n");
            printLine();
        }
    } else if (choice >= 2 && choice < 9) {//Options available for
        //double search
        printLine();
        if (choice == 2)
            printf("Type the title you want to search.\n");
        else if (choice == 3)
            printf("Type the author you want to search.\n");
        else if (choice == 4)
            printf("Type the genre you want to search.\n");
        else if (choice == 5)
            printf("Type the publisher you want to search.\n");
        else if (choice == 6)
            printf("Type 'used' for used books and 'new' for new books\n");
        else if (choice == 7) {//Price range search
            double start, end;
            printLine();
            printf("Please Type a price range\n");
            printLine();
            printf("Starting Price: $");
            scanf("%lf", &start);
            FLUSH;
            printf("End Price: $");
            scanf("%lf", &end);
            FLUSH;

            node = searchByPriceRange(table, start, end);
        } else if (choice == 8) {//ID range search
            int start, end;
            printLine();
            printf("Please Type an ID range\n");
            printLine();
            printf("Starting ID: ");
            scanf("%d", &start);
            FLUSH;
            printf("End ID: ");
            scanf("%d", &end);
            FLUSH;

            node = searchByIDRange(table, start, end);
        }
        printLine();

        if (choice >= 2 && choice < 7) {
            char* searchString = getString();
            //Validation for used/new
            if (choice == 6) {
                while (!strcmp(searchString, "used") &&
                        !strcmp(searchString, "Used") &&
                        !strcmp(searchString, "new") &&
                        !strcmp(searchString, "New")) {
                    printLine();
                    printf("Please type either 'used' or 'new'.\n");
                    printLine();
                    FLUSH;
                    searchString = getString();
                }
                FLUSH;
            }
            node = searchDouble(node, list, searchString, choice);
        }


    } else if (choice == 0) {//Exit
        Node* exit = (Node*) malloc(sizeof (Node));
        exit->search = 0;
        return exit;
    }
    
    
    //A user must select one node from a result linked list
    Node* head = node;
    if (node != NULL && choice != 1 && retrieve) {
        printLine();
        printf("SELECT ONE BOOK AND TYPE THE ID.\n");
        printLine();
        int id;
        FLUSH;
        do {
            scanf("%d", &id);
            FLUSH;
            node = searchByID(table, id);
            if (node == NULL) {
                printLine();
                printf("ID NOT FOUND. PLEASE CHOOSE ANOTHER ID.\n");
                printLine();
            }
        } while (node == NULL);
    }

    clearList(head);

    return node;
}


/*
 * Vladyslav Hrusha
 * Searches a dictionary.
 * 
 * The dictionary given will be changed according to the
 * search field
 * 
 * Partial search is implemented by using strstr()
 */
Node* searchDictionary(Node** dictionary, char* searchString, int num) {
    int size;
    size = optionToSize(num);

    Node* head = NULL;
    for (int i = 0; i < size; i++) {
        Node* current = dictionary[i];
        while (current != NULL) {
            if (num == 0) {//Title
                if (strstr(current->manga.title, searchString) != NULL) {
                    head = buildList(head, current, 0);
                }
                current = current->nextTitle;
            } else if (num == 1) {//Author
                if (strstr(current->manga.author, searchString) != NULL) {
                    head = buildList(head, current, 0);
                }
                current = current->nextAuthor;
            } else if (num == 2) { //Genre
                if (strstr(current->manga.genre, searchString) != NULL) {
                    head = buildList(head, current, 0);
                }
                current = current->nextGenre;
            } else if (num == 3) {//Publisher
                if (strstr(current->manga.publisher, searchString) != NULL) {
                    head = buildList(head, current, 0);
                }
                current = current->nextPublisher;
            } else if (num == 4) {//Used
                head = buildList(head, current, 0);
                current = current->nextUsed;
            }
        }
    }

    return head;
}

/*
 * Vladyslav Hrusha
 * Search by ID from a hash table
 */
Node* searchByID(Node** table, int id) {
    int key = divisionHash(id);
    Node* current = table[key];
    while (current != NULL) {
        if (current->manga.id == id) {
            return current;
        } else {
            current = current->next;
        }
    }
    return current;
}

/*
 * Heon Lee
 * Search by ID range from a hash table
 */
Node* searchByIDRange(Node** table, int start, int end) {
    Node* head = NULL;
    for (int i = start; i < end + 1; i++) {
        int key = divisionHash(i);
        Node* current = table[key];
        while (current != NULL) {
            if (current->manga.id == i) {
                head = buildList(head, current, 0);
            }
            current = current->next;
        }
    }
    return head;
}

/*
 * Heon Lee
 * Range search for the price field using a given price range
 */
Node* searchByPriceRange(Node** table, double start, double end) {
    Node* head = NULL;
    for (int i = 0; i < SIZE; i++) {
        Node* current = table[i];
        while (current != NULL) {
            if (current->manga.price >= start
                    && current->manga.price <= end) {
                head = buildList(head, current, 0);
            }
            current = current->next;
        }
    }
    return head;
}

/*
 * Nikita Kartavyi
 * Search with two fields
 */
Node* searchDouble(Node* node, Node*** list, char* searchString, int choice) {
    int choice2, choice3;
    printLine();
    printf("Second Search? [1-yes, 0-no]:\n");
    printLine();
    scanf("%d", &choice3);
    FLUSH;
    validateOption(choice3, 0, 1);
    FLUSH;
    char* searchString2;
    //Search Menu for second field. A user is not allowed
    //to select the field which was selected as a first search field
    if (choice3 == 1) {
        printLine();
        if (choice != 2)
            printf("2 - Search by Title\n");
        if (choice != 3)
            printf("3 - Search by Author\n");
        if (choice != 4)
            printf("4 - Search by Genre\n");
        if (choice != 5)
            printf("5 - Search by Publisher\n");
        if (choice != 6)
            printf("6 - Search Used/New\n");
        printLine();
        scanf("%d", &choice2);
        printLine();

        FLUSH;
        if (choice == choice2) {
            choice2 = validateOptionWithException(choice2, 2, 6, choice);
        }
        FLUSH;

        printLine();
        if (choice2 == 2)
            printf("Type the title you want to search.\n");
        else if (choice2 == 3)
            printf("Type the author you want to search.\n");
        else if (choice2 == 4)
            printf("Type the genre you want to search.\n");
        else if (choice2 == 5)
            printf("Type the publisher you want to search.\n");
        else if (choice2 == 6)
            printf("Type 'used' for used books and 'new' for new books\n");
        FLUSH;
        printLine();
        searchString2 = getString();
    }


    Node* result = NULL;
    if (choice3 == 1) {//If a user wants to do a double search
        node = searchDictionary(list[choice - 2], searchString, choice - 2);
        result = searchDictionaryTwice(node, searchString,
                searchString2, choice - 2, choice2 - 2);
    } else {//If not
        node = searchDictionary(list[choice - 2],
                searchString, choice - 2);
    }

    
    //Printing a result list
    if ((!choice3 && node != NULL) || (choice3 && result != NULL)) {
        TreeNode* tree = NULL;
        if (!choice3)
            insertList(node, &tree);
        else
            insertList(result, &tree);

        //Sorting Menu
        printLine();
        printf("SELECT HOW YOU WANT YOUR RESULTS TO BE DISPLAYED.\n");
        printf("1 - Unordered\n");
        printf("2 - Ascending\n");
        printf("3 - Descending\n");
        printLine();
        FLUSH;
        int a;
        scanf("%d", &a);
        a = validateOption(a, 1, 3);
        FLUSH;
        if (a == 1) {
            if (!choice3)
                printList(node);
            else {
                printSecondList(result);
                clearList(node);
                switchList(result);
                node = result;
            }
        } else if (a == 2)
            printInorder(tree);
        else if (a == 3)
            printInorderReverse(tree);
        freeTree(tree);
    } else {//If the returned result list is NULL
        printLine();
        printf("SEARCH FAILED. BOOK NOT FOUND.\n");
        printLine();
    }
    return node;

}

/*
 * Nikita Kartavyi
 * Double search
 * Takes the first result linked list as a parameter
 * I separated this part from searchDictionary which is single field search.
 * The two functions have different authors.
 * The functions might have duplicate parts.
 * 
 * 
 * Searches for the second search field from a result list
 */
Node* searchDictionaryTwice(Node* firstResultList, char* searchString,
        char* searchString2, int num, int num2) {

    Node* head = NULL;

    Node* current = firstResultList;
    while (current != NULL) {
        if (num == 0 && num2 == 1) {//Title Author
            if (strstr(current->manga.title, searchString) != NULL
                    && strstr(current->manga.author, searchString2) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num2 == 0 && num == 1) {//Author Title
            if (strstr(current->manga.title, searchString2) != NULL
                    && strstr(current->manga.author, searchString) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num == 0 && num2 == 2) {//Title Genre
            if (strstr(current->manga.title, searchString) != NULL &&
                    strstr(current->manga.genre, searchString2) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num2 == 0 && num == 2) {//Genre Title
            if (strstr(current->manga.title, searchString2) != NULL
                    && strstr(current->manga.genre, searchString) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num == 0 && num2 == 3) {//Title Publisher
            if (strstr(current->manga.title, searchString) != NULL &&
                    strstr(current->manga.publisher, searchString2) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num2 == 0 && num == 3) {//Publisher Title
            if (strstr(current->manga.title, searchString2) != NULL
                    && strstr(current->manga.publisher, searchString) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num == 1 && num2 == 0 || num == 0 && num2 == 1) {//Author Title 
            if (strstr(current->manga.author, searchString) != NULL &&
                    strstr(current->manga.title, searchString2) != NULL ||
                    strstr(current->manga.author, searchString2) != NULL &&
                    strstr(current->manga.title, searchString) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num == 1 && num2 == 2 || num == 2 && num2 == 1) {//Author Genre 
            if (strstr(current->manga.author, searchString) != NULL &&
                    strstr(current->manga.genre, searchString2) != NULL ||
                    strstr(current->manga.author, searchString2) != NULL &&
                    strstr(current->manga.genre, searchString) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num == 1 && num2 == 3 || num == 3 && num2 == 1) {//Author Publisher 
            if (strstr(current->manga.author, searchString) != NULL &&
                    strstr(current->manga.publisher, searchString2) != NULL ||
                    strstr(current->manga.author, searchString2) != NULL
                    && strstr(current->manga.publisher, searchString) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num == 1 && num2 == 2 || num == 2 && num2 == 1) {//Author Used 
            if (strstr(current->manga.author, searchString) != NULL
                    && strstr(current->manga.genre, searchString2) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num == 2 && num2 == 3 || num == 3 && num2 == 2) { //Genre Publisher
            if (strstr(current->manga.genre, searchString) != NULL
                    && strstr(current->manga.publisher, searchString2) != NULL ||
                    strstr(current->manga.genre, searchString2) != NULL
                    && strstr(current->manga.publisher, searchString) != NULL) {
                head = buildList(head, current, 1);
            }
            current = current->nextList;
        } else if (num2 == 2) { //Genre
            if (strstr(current->manga.genre, searchString) != NULL) {
                head = buildList(head, current,1);
            }
            current = current->nextList;
        } else if (num2 == 3) {//Publisher
            if (strstr(current->manga.publisher, searchString) != NULL) {
                head = buildList(head, current,1);
            }
            current = current->nextList;
        } else if (num2 == 4) {//Used
            if (current->manga.used)
                head = buildList(head, current,1);
            current = current->nextList;
        }
    }


    return head;
}