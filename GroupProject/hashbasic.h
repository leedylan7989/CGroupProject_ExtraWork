
#ifndef HASHBASIC_H
#define HASHBASIC_H
#include "hashtable.h"
#include "extra.h"
#include "freefunctions.h"
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>


#define FLUSH stdin=freopen(NULL,"r",stdin)

//Basic functions
void add(Node**, Node***, Manga);
void edit(int, Node*);
void delete(Node**, int);

#endif /* HASHBASIC_H */

