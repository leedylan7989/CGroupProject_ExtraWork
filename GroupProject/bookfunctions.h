
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
#include "dictionary.h"

#define FLUSH stdin=freopen(NULL,"r",stdin)

void addManga(Node**, Node***);
void deleteManga(Node**, Node***);
void editManga(Node**, Node***);
void purchaseManga(Node**, Node***);


#endif /* BOOKFUNCTIONS_H */

