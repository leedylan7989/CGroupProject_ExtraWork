#include "tree.h"


//direction: -1 - Going left, 1 - Going right
void generateTree(Node** table, TreeNode** tree, int direction, int start,
        int end){
    if(direction == 1 && end > start){
        if (table[start] != NULL) {
            insertTableList(table[start], tree);
        }
        generateTree(table, tree, direction, start+direction, end);
    } else if (direction == -1 && end <= start) {
        if (table[start] != NULL) {
            insertTableList(table[start], tree);
        }
        generateTree(table, tree, direction, start+direction, end);
    }
}

/*
 * Iterate through a list and make them into tree nodes
 */
void insertTableList(Node* current, TreeNode** tree){
    if (current != NULL) {
        insertTreeNode(tree, current);
        insertTableList(current->next, tree);
    }
}

/*
 * Iterate through a list and make them into tree nodes
 */
void insertList(Node* current, TreeNode** tree){
    if (current != NULL) {
        insertTreeNode(tree, current);
        insertList(current->nextList, tree);
    }
}

void insertTreeNode(TreeNode** tree, Node* node){
    if(*tree == NULL){
        *tree = (TreeNode*)malloc(sizeof(TreeNode));
        (*tree)->left = (*tree)->right = NULL;
        (*tree)->node = node;
    } else {
        TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
        temp->node = node;
        temp->left = temp->right = NULL;
        TreeNode* parent = searchTreeNode(*tree, temp);
        if(parent != NULL && parent->node->manga.id > temp->node->manga.id){
            parent->left = temp;
        }else if(parent != NULL && parent->node->manga.id < temp->node->manga.id){
            parent->right = temp;
        }
    }
}

TreeNode* searchTreeNode(TreeNode* root, TreeNode* temp){
        if(temp->node->manga.id > root->node->manga.id){
            if(root->right == NULL){
                return root;
            }else{
                return searchTreeNode(root->right, temp);
            }
        } else if(temp->node->manga.id < root->node->manga.id){
            if(root->left == NULL){
                return root;
            }else{
                return searchTreeNode(root->left, temp);
            }
        } else{
            return NULL;
        }
}