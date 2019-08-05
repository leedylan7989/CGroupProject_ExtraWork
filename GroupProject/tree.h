
#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

typedef struct treenode{
    Node* node;
    struct treenode *left, *right;
} TreeNode;

void generateTree(Node**, TreeNode**, int, int,
        int);
void searchTableNode(Node*, TreeNode**);
void insertTreeNode(TreeNode**, Node*);
TreeNode* searchTreeNode(TreeNode*, TreeNode*);

#endif /* TREE_H */

