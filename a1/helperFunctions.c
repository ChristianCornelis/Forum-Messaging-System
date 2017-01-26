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
            array[i][j] = (char)0;
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

char ** resizeArray (char ** oldArray, int rows, int columns)
{
    char ** newArray;
    newArray = initArray(rows * 2, columns);

    int i, j;

    for (i = 0; i < rows; i++)
    {
        /*
        if (strcmp(oldArray[i], "") != 0)
            strcpy(oldArray[i], newArray[i]);*/
        for (j = 0; j < columns; j++)
        {
            newArray[i][j] = oldArray[i][j];
        }
    }

    /*destroying old array*/
    destroyArray(oldArray, rows);

    return newArray;
}

/*function to check if the array needs to be resized*/
int checkSize (int rowCnt, int rows)
{
    if (rowCnt == (rows-1))
        return 1;
    return 0;
}

/*function to check if a word is a type keyword*/
int isKeyword (char * word)
{
    if (strcmp(word, "int") == 0)
        return 1;
    else if (strcmp(word, "double") == 0)
        return 1;
    else if (strcmp(word, "char") == 0)
        return 1;
    else if (strcmp(word, "signed") == 0)
        return 1;
    else if (strcmp(word, "unsigned") == 0)
        return 1;
    else if (strcmp(word, "short") == 0)
        return 1;
    else if (strcmp(word, "long") == 0)
        return 1;
    else if (strcmp(word, "float") == 0)
        return 1;
    else if (strcmp(word, "struct") == 0)
        return 2;
    else if (strcmp(word, "*") == 0)
        return 3;
    else if (strstr(word, "*") != NULL && (strstr(word, "double") == NULL && strstr(word, "int") == NULL && strstr(word, "char") == NULL
            && strstr(word, "signed") == NULL && strstr(word, "unsigned") == NULL && strstr(word, "short") == NULL && strstr(word, "long") == NULL &&
            strstr(word, "float") == NULL && strstr(word, "struct") == NULL))
        return 4;
    else if (strstr(word, "*") != NULL)
        return 5;

    return 0;
}

int printToFile (char* fileName, char** spacing, char** strings, int rowCnt)
{
    int nameLen = strlen(fileName);
    int i;
    int inClass = 0;
    int isFunc = 0;
    int braceCount = 0;
    int openBraceCount = 0;
    int closeBraceCount = 0;
    char className[1000];
    fileName[nameLen-1] = '\0';

    FILE* toWrite = NULL;
    toWrite = fopen(fileName, "w");

    if (toWrite == NULL)
    {
        printf("File not found. \nExitting");
        return 1;
    }
    for (i = 0; i < rowCnt; i++)
    {
        isFunc = 0;
        /*if encountering string "class"*/
        if (strcmp(strings[i], "class") == 0)
        {
            fprintf(toWrite, "%sstruct", spacing[i]);
            inClass = 1;
            strcpy(className, strings[i+1]);
        }
        /*else if to count all opening brackets*/
        else if (strcmp(strings[i], "{") == 0)
        {
            openBraceCount++;
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);
        }
        /*else if to count all closing braces*/
        else if (strcmp(strings[i], "}") == 0 || strcmp(strings[i], "};") == 0)
        {
            closeBraceCount++;
            if (openBraceCount == closeBraceCount)
                inClass = 0;
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);
        }
        /*else if finds a (, handle for if encoutnering a function*/
        else if (strcmp(strings[i+1], "(") == 0 && strcmp(strings[i], "main") != 0)
        {
            int count = i+1;
            /*finding index of end bracket*/
            while(strcmp(strings[count], ")") != 0)
                count++;

            /*if the a function-starting brace is close by*/
            if (strcmp(strings[count+1], "{") == 0 || strcmp(strings[count+2], "{") == 0)
                isFunc = 1;
                braceCount++;

            /*if in a class, and a function is being defined*/
            if (inClass == 1 && isFunc == 1)
            {
                fprintf(toWrite, "%s%s%s", spacing[i], className, strings[i]);

                if (strcmp(strings[i+1], "(") == 0 && strcmp(strings[i+2], ")") != 0 && isFunc == 1)
                {
                    int count = i+2;
                    while (strcmp(strings[count],")") != 0)
                    {
                        /*if word is a type, check if other words following are types*/
                        if (isKeyword(strings[count]) == 1)
                        {
                            if (isKeyword(strings[count+1]) == 3  || isKeyword(strings[count+1]) == 4)
                            {
                                printf("dis one result %d\n", isKeyword(strings[count+1]));
                                fprintf(toWrite, "%c", strings[count][0]-32);

                                if (isKeyword(strings[count+1]) == 3)
                                    count += 3;
                                else if (isKeyword(strings[count+1]) == 4)
                                    count += 2;
                            }
                            else
                            {
                                fprintf(toWrite, "%c", strings[count][0]);
                                printf("string %s result: %d", strings[count], isKeyword(strings[count+1]));
                                count++;
                            }
                            /*int j;

                            for (j = 1; j < 4; j++)
                            {
                                printf("in for word: %s\n", strings[count + j]);
                                /*if next word is a type, and the next word is not a ptr
                                if (isKeyword(strings[count+j]) == 1 && (isKeyword(strings[count+j+1]) != 3 && isKeyword(strings[count+j+1]) != 4))
                                {
                                    fprintf(toWrite, "%c", strings[count + j][0]);
                                    count+= 1;
                                }
                                /*else if one past word looked at is a *, or the keyword or the word after have a * in them
                                else if (isKeyword(strings[count+j+1]) == 3 || isKeyword(strings[count+j]) == 4 || isKeyword(strings[count+j+1]) == 4)
                                {
                                    printf("ptr\n");
                                    fprintf(toWrite, "%c", strings[count + j][0] - 32);
                                    if (isKeyword(strings[count+j+1]) == 3)
                                        count++;
                                    
                                    else if (isKeyword(strings[count+j]) == 4)
                                        count += 2;
                                    else if (isKeyword(strings[count+j+1]) == 4)
                                        count++;
                                    break;
                                    count++;
                                }
                                else
                                    break;

                                
                            }
                            
                            if (strcmp(strings[count + j], ")") != 0 || strcmp(strings[count +j], ",") != 0)
                                count += j+1;
                            printf("STRINGLoop: %s\n",strings[count]);*/
                        }
                        /*else if current word is 'struct'*/
                        else if (isKeyword(strings[count]) == 2)
                        {
                            fprintf(toWrite, "%c", strings[count][0]);
                            printf("struct result: %d\n", isKeyword(strings[count+2]));
                            /*if * is in between struct name and variable, ex struct myStruct * a*/
                            if (isKeyword(strings[count+2]) == 3)
                            {
                                fprintf(toWrite, "%c", strings[count+1][0] - 32);
                                count++;
                            }
                            /*else if * is attached to struct name, ex struct myStruct* a*/
                            else if (isKeyword(strings[count+2]) == 4)
                                fprintf(toWrite, "%c", strings[count+1][0] - 32);
                            /*else if * is attached to struct variable name, ex struct myStruct *a*/
                            else if (isKeyword(strings[count+1]) == 4)
                                fprintf(toWrite, "%c", strings[count+1][0]-32);
                            else
                                fprintf(toWrite, "%c", strings[count+1][0]);

                            count += 3;
                        }

                        else if (isKeyword(strings[count]) == 5)
                        {
                            printf("here\n, Aresult %d\n", isKeyword(strings[count]));
                            fprintf(toWrite, "%c", strings[count][0] - 32);
                            count+= 2;
                        }
                        else
                            count += 1;

                        /*if (strcmp) have to do for structs as well!!!!! like struct person thatPerson would be a thing*/
                        if (strcmp(strings[count], "") == 0)
                            count += 1;
                        else if (strcmp(strings[count], ",") == 0)
                        {
                            count += 2;
                            fprintf(toWrite, "|");
                        }

                        /*fprintf(toWrite, "|");*/
                        printf("STRING: %s\n",strings[count]);
                    }
                }
            }
            else
                fprintf(toWrite, "%s%s", spacing[i], strings[i]);
        }
        /*else just print out spacing and string normally*/
        else
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);


    }

    fclose(toWrite);
    /*free(className);*/
    return 0;
}
