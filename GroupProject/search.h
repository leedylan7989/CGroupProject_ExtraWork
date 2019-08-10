
#ifndef SEARCH_H
#define SEARCH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"
#include "hashbasic.h"
#include "print.h"
#include "extra.h"
#include "dictionary.h"


#define FLUSH stdin=freopen(NULL,"r",stdin)

//Search
Node* searchManga(Node**, Node***, int);
Node* searchByID(Node**, int);
Node* searchDictionary(Node**, char*, int);
Node* searchByPriceRange(Node**,double, double);
Node* searchByIDRange(Node**, int, int);
Node* searchDouble(Node*, Node***, char*, int);
Node* searchDictionaryTwice(Node*, char*,char*, int, int);

#endif /* SEARCH_H */

