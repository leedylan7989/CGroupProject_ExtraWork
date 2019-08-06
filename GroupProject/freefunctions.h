

#ifndef FREEFUNCTIONS_H
#define FREEFUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include "freefunctions.h"
#include "hashtable.h"
#include "tree.h"
#include "dictionary.h"


//Free table
void freeTable(Node***);
void freeList(Node**);
void freeNode(Node**);
void freeTree(TreeNode*);
void freeDictionary(Node***);

#endif /* FREEFUNCTIONS_H */

