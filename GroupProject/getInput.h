

#ifndef GETINPUT_H
#define GETINPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLUSH stdin=freopen(NULL,"r",stdin)

char* getString();

//Function for other functions
void checkYN(char);

#endif /* GETINPUT_H */

