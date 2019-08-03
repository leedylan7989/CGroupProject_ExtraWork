
#ifndef SEARCH_H
#define SEARCH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"
#include "hashbasic.h"
#include "print.h"


#define FLUSH stdin=freopen(NULL,"r",stdin)

//Search
Node* searchManga(Node**, int);
Node* searchByID(Node**, int);
Node* searchByTitle(Node**, char*);

#endif /* SEARCH_H */

