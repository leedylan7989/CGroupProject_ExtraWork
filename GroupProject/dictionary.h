
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"
#include "extra.h"
#include "hashbasic.h"
#include "bookfunctions.h"

void createDictionary(Node**, Node***, int);
void addDictionary(Node*, Node**, int);
Node* searchParentDictionaryNode(Node*, int);
void deleteDictionary(Node**, Node*, int);
#endif /* DICTIONARY_H */

