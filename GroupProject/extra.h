

#ifndef GETINPUT_H
#define GETINPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "print.h"

#define FLUSH stdin=freopen(NULL,"r",stdin)

char* getString();
int validateOptionWithException(int, int, int, int);
int validateOption(int, int, int);
int characterToIndex(char);
int boolToIndex(bool);
int optionToSize(int);
Node* buildList(Node*, Node*, int);
void clearList(Node*);
void switchList(Node*);

//Screens
int mainScreen();
int optionScreen();

//Function for other functions
void checkYN(char);

#endif /* GETINPUT_H */

