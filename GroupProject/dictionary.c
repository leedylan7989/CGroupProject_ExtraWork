#include "dictionary.h"


/*
 * Vladyslav Hrusha
 * Parameters: table - hash table, dictionary - dictionary list
 * num - selected dictionary number
 * This function populates a dictionary from a hash table
 */
void createDictionary(Node** table, Node*** dictionary, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != NULL) {
            addDictionary(table[i], dictionary[num], num);
        }
    }
}

/*
 * 0 - title
 * 1 - author
 * 2 - genre
 * 3 - publisher
 * 4 - used
 */
/*
 * Vladyslav Hrusha
 * This function adds a node to a dictionary
 */
void addDictionary(Node* node, Node** dictionary, int num) {
    //Iterate through each index of hash table
    //and turn table nodes to become dictionary nodes as well
    while (node != NULL) {
        int index;
        if (num == 0) {
            char* title = node->manga.title;
            //All title that starts with 'a' goes into index 0 of 
            //the dictionary
            index = characterToIndex(title[0]);
        } else if (num == 1) {
            char* author = node->manga.author;
            index = characterToIndex(author[0]);
        } else if (num == 2) {
            char* genre = node->manga.genre;
            index = characterToIndex(genre[0]);
        } else if (num == 3) {
            char* publisher = node->manga.publisher;
            index = characterToIndex(publisher[0]);
        } else if (num == 4) {
            bool used = node->manga.used;
            index = boolToIndex(used);
        }
        //Searching for parent node 
        Node* parent = searchParentDictionaryNode(dictionary[index], num);
        if (parent == NULL) {
            dictionary[index] = node;
        } else {
            switch (num) {
                case 0:
                    parent->nextTitle = node;
                    break;
                case 1:
                    parent->nextAuthor = node;
                    break;
                case 2:
                    parent->nextGenre = node;
                    break;
                case 3:
                    parent->nextPublisher = node;
                    break;
                case 4:
                    parent->nextUsed = node;
                    break;
            }
        }
        node = node->next;
    }
}

/*
 * Searches a node that can be a parent node from a linked list
 * Vladyslav Hrusha
 */
Node* searchParentDictionaryNode(Node* node, int num) {
    if (node == NULL) {
        return node;
    }
    if (num == 0)
        while (node->nextTitle != NULL)
            node = node->nextTitle;
    else if (num == 1)
        while (node->nextAuthor != NULL)
            node = node->nextAuthor;
    else if (num == 2)
        while (node->nextGenre != NULL)
            node = node->nextGenre;
    else if (num == 3)
        while (node->nextPublisher != NULL)
            node = node->nextPublisher;
    else if (num == 4)
        while (node->nextUsed != NULL)
            node = node->nextUsed;
    return node;
}


//Heon Lee
//Parameter: table - hash table, id - id to delete
//This function deletes a node with selected id from the hash table
void deleteDictionary(Node** dictionary, Node* node, int num) {
    int index;
    if (num == 0)
        index = characterToIndex((node->manga.title)[0]);
    else if (num == 1)
        index = characterToIndex((node->manga.author)[0]);
    else if (num == 2)
        index = characterToIndex((node->manga.genre)[0]);
    else if (num == 3)
        index = characterToIndex((node->manga.publisher)[0]);
    else if (num == 4)
        index = boolToIndex(node->manga.used);
    bool found = false;
    Node* current = dictionary[index];
    Node* prev = NULL;
    while (!found && current != NULL) {
        if (current->manga.id == node->manga.id) {
            found = true;
        } else {
            if (num == 0 && current->nextTitle != NULL) {
                prev = current;
            }else if (num == 1 && current->nextAuthor != NULL) {
                prev = current;
            }else if (num == 2 && current->nextGenre != NULL) {
                prev = current;
            }else if (num == 3 && current->nextPublisher != NULL) {
                prev = current;
            }else if (num == 4 && current->nextUsed != NULL) {
                prev = current;
            }
            if(num == 0)
            current = current->nextTitle;
            if(num == 1)
            current = current->nextAuthor;
            if(num == 2)
            current = current->nextGenre;
            if(num == 3)
            current = current->nextPublisher;
            if(num == 4)
            current = current->nextUsed;
        }
    }

    if (dictionary[index]->manga.id == current->manga.id) {
        //found node is at first of the linked list
        if (num == 0)
            dictionary[index] = current->nextTitle;
        else if (num == 1)
            dictionary[index] = current->nextAuthor;
        else if (num == 2)
            dictionary[index] = current->nextGenre;
        else if (num == 3)
            dictionary[index] = current->nextPublisher;
        else if (num == 4)
            dictionary[index] = current->nextUsed;
    } else if (num == 0 && current->nextTitle == NULL) {//found node is at the end
        prev->nextTitle = NULL;
    } else if (num == 1 &&current->nextAuthor == NULL) {//found node is at the end
        prev->nextAuthor = NULL;
    } else if (num == 2 && current->nextGenre == NULL) {//found node is at the end
        prev->nextTitle = NULL;
    } else if (num == 3 && current->nextPublisher == NULL) {//found node is at the end
        prev->nextPublisher = NULL;
    }else if (num == 4 && current->nextUsed == NULL) {//found node is at the end
        prev->nextUsed = NULL;
    }else {
        //Mid-way
        if (num == 0) {
            prev->nextTitle = current->nextTitle;
            current->nextTitle = NULL;
        } else if (num == 1) {
            prev->nextAuthor = current->nextAuthor;
            current->nextAuthor = NULL;
        } else if (num == 2) {
            prev->nextGenre = current->nextGenre;
            current->nextGenre = NULL;
        } else if (num == 3) {
            prev->nextPublisher = current->nextPublisher;
            current->nextPublisher = NULL;
        } else if (num == 4) {
            prev->nextUsed = current->nextUsed;
            current->nextUsed = NULL;
        }
    }
}