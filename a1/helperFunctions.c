#include "helperFunctions.h"

char ** initArray(int rows, int columns)
{
    char ** array;
    int i, j;
    array = malloc(sizeof(char *) * rows);
    for (i = 0; i < rows; i++)
    {
        array[i] = malloc(sizeof(char) * columns);
        for (j = 0; j < columns; j++)
        {
            /*initializing all elements in the array to the DEL character*/
            array[i][j] = (char) 127;
        }
    }

    return array;
}

int destroyArray(char ** toDestroy, int rows)
{
    int i;

    if (!toDestroy || rows <= 0)
        return -1;

    for (i = 0; i < rows; i++)
        free(toDestroy[i]);

    free(toDestroy);

    return 1;
}