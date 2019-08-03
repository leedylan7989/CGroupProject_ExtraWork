

#ifndef FILEIO_H
#define FILEIO_H
#include "hashtable.h"
#include "getInput.h"
#include "hashbasic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FLUSH stdin=freopen(NULL,"r",stdin)


//Read from and Write to a record txt file
//Add any necessary functions and change return type
//If successful, return the Heap allocated array pointer to main
//If failed, return null
void readFile(Node**);

#endif /* FILEIO_H */

