#ifndef __CCORNELI_HELPER_FUNCTIONS_H__
#define __CCORNELI_HELPER_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>

/*function to initialize a dynamically-allocated array based on size parameters */
char ** initArray(int rows, int columns);

/*function to destroy a dynamically-allocated array*/
int destroyArray(char ** toDestroy, int rows);


#endif