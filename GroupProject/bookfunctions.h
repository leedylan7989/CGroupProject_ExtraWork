
#ifndef BOOKFUNCTIONS_H
#define BOOKFUNCTIONS_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
#include "hashbasic.h"
#include <string.h>
#include "extra.h"
#include "freefunctions.h"
#include "print.h"
#include "search.h"

#define FLUSH stdin=freopen(NULL,"r",stdin)

void addManga(Node**);
void deleteManga(Node**);
void editManga(Node**);


#endif /* BOOKFUNCTIONS_H */

