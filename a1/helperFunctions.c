#include "helperFunctions.h"

char ** initArray(int rows, int columns)
{
    char ** array;
    int i, j;
    array = malloc(sizeof(char *) * rows);

    if (!array)
    {
        printf("Malloc failed. Exitting\n");
        exit(1);
    }
    for (i = 0; i < rows; i++)
    {
        array[i] = malloc(sizeof(char) * columns);
        if (!array[i])
        {
            printf("Malloc failed. Exitting\n");
            exit(1);
        }

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
    char** functions = NULL;
    int functionRows = 150;
    int functionCols = 10;
    int functionRowCnt = 0;
    char tempSize[10];
    char** oldFunctionNames = initArray(100, 250);
    char** newFunctionNames = initArray(100, 250);
    int functionNamesRowCnt = 0;
    int functionNamesRows = 100;
    int oldFunctionNamesCols = 0;
    int newFunctionNamesCols = 0;
    int funcStart = 0;
    int funcEnd = 0;
    char* newName = NULL;

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
        if (strcmp(strings[i], "class") == 0 && strcmp(strings[i+2], "{") == 0)
        {
            fprintf(toWrite, "%sstruct", spacing[i]);
            inClass = 1;
            strcpy(className, strings[i+1]);
            functions = initArray(functionRows, functionCols);
            functionRowCnt = 0;
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
            {
                inClass = 0;
                fprintf(toWrite, "%s%s", spacing[i], strings[i]);
                int k = 0;
                for (k = 0; k < functionRowCnt; k++)
                {
                    int index1 = atoi(functions[k]);
                    int index2 = atoi(functions[k+1]);
                    int j = 0;
                    int l = 0;
                    int found = -1;
                    for (j = index1; j <= index2; j++)
                    {
                        for (l = 0; l < functionNamesRowCnt; l++)
                        {
                            if (strcmp(strings[j], oldFunctionNames[l]) == 0)
                            {
                                printf("func name new: %s\n", newFunctionNames[l]);
                                found = 1;
                                fprintf(toWrite, "%s%s", spacing[j], newFunctionNames[l]);
                                j++;
                                break;
                            }
                        }
                        /*
                        if (strcmp(strings[j+1], "(") == 0 && strcmp(strings[j+2], ")") != 0 )
                        {
                            printf("before");
                            printf("in dat if %s\n", newFunctionNames[functionNamesRowCnt-1]);
                            fprintf(toWrite, "%s%s", spacing[j], newFunctionNames[functionNamesRowCnt-1]);
                            printf("after");    
                        }
                        else if (strcmp(strings[j+1], "(") == 0 && strcmp(strings[j+2], ")") == 0 && isFunc == 1)
                        {
                            printf("Im in here!");
                            fprintf(toWrite, "%s%s", spacing[j], newFunctionNames[functionNamesRowCnt-1]);
                            printf("in dat else\n");
                        }
                        else*/

                            fprintf(toWrite, "%s%s", spacing[j],strings[j]);
                            printf("After print\n");
                    }
                    k++;
                }

                destroyArray(functions, functionRows);
                functionRowCnt = 0;
                functions = NULL;
            }
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
            {
                isFunc = 1;
                strcpy(oldFunctionNames[functionNamesRowCnt], strings[i]);
            }
                braceCount++;

            /*if in a class, and a function is being defined*/
            if (inClass == 1 && isFunc == 1)
            {
                funcStart = 0;
                funcEnd = 0;
                fprintf(toWrite, "%s(*%s%s", spacing[i], className, strings[i]);

                /*if function has parameters*/
                if (strcmp(strings[i+1], "(") == 0 && strcmp(strings[i+2], ")") != 0)
                {
                    funcStart = i;
                    
                    while (strstr(spacing[funcStart], "\n") == NULL)
                        funcStart--;

                    funcEnd = funcStart;
                    while ((strcmp(strings[funcEnd], "}") != 0))
                    {
                        funcEnd++;
                    }

                    sprintf(tempSize, "%d", funcStart);
                    strcpy(functions[functionRowCnt], tempSize);
                    functionRowCnt++;
                    sprintf(tempSize, "%d", funcEnd);
                    strcpy(functions[functionRowCnt], tempSize);
                    functionRowCnt++;


                    int count = i+2;
                    newName = renameFuncs(strings, spacing, count, toWrite, funcStart, className);
                    strcpy(newFunctionNames[functionNamesRowCnt], newName);
                    functionNamesRowCnt++;
                    if (functionNamesRowCnt == functionNamesRows)
                    {
                        oldFunctionNames = resizeArray(oldFunctionNames, functionNamesRowCnt, oldFunctionNamesCols);
                        newFunctionNames = resizeArray(newFunctionNames,functionNamesRowCnt, newFunctionNamesCols);
                        functionNamesRowCnt *= 2;
                    }
                    free(newName);
                    fprintf(toWrite, "();");
                    i = funcEnd;
                }

                /*else if (strcmp(strings[i+1], "(") == 0 && strcmp(strings[i+2], ")") == 0)
                {
                    funcStart = i;
                    
                    while (strstr(spacing[funcStart], "\n") == NULL)
                        funcStart--;

                    funcEnd = funcStart;
                    while ((strcmp(strings[funcEnd], "}") != 0))
                    {
                        funcEnd++;
                    }

                    sprintf(tempSize, "%d", funcStart);
                    strcpy(functions[functionRowCnt], tempSize);
                    functionRowCnt++;
                    sprintf(tempSize, "%d", funcEnd);
                    strcpy(functions[functionRowCnt], tempSize);
                    functionRowCnt++;

                    int count = i+2;
                    newName = renameFuncs(strings, spacing, count, toWrite, funcStart, className);
                    strcpy(newFunctionNames[functionNamesRowCnt], newName);
                    functionNamesRowCnt++;
                    if (functionNamesRowCnt == functionNamesRows)
                    {
                        oldFunctionNames = resizeArray(oldFunctionNames, functionNamesRowCnt, oldFunctionNamesCols);
                        newFunctionNames = resizeArray(newFunctionNames,functionNamesRowCnt, newFunctionNamesCols);
                        functionNamesRowCnt *= 2;
                    }
                    free(newName);
                    fprintf(toWrite, "();");
                    i = funcEnd;
                }*/

                
            }
            else
                fprintf(toWrite, "%s%s", spacing[i], strings[i]);
            
            
        }
        /*else just print out spacing and string normally*/
        else
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);

    }

    destroyArray(oldFunctionNames, functionNamesRows);
    destroyArray(newFunctionNames, functionNamesRows);
    fclose(toWrite);
    return 0;
}

/*function to rename functions inside classes*/
char* renameFuncs(char** strings, char** spacing, int count, FILE* toWrite, int funcStart, char className[])
{
    /*mallocing for new name*/
    char* newName = malloc(sizeof(char) * 1000);
    strcpy(newName, "");
    char temp[2] = "";

    int countCpy = count -1;

    printf("name: |%s|\n", className);
    /*fprintf(toWrite, "%s%s%s", spacing[i], className, strings[i]);*/
    if (strstr(className, " ") != NULL)
    {
        int a = 0;
        for (a = 0; a <strlen(className); a++)
        {
            if (className[a] == ' ')
                className[a] = (char) 0;
        }
    }
    strcat(newName, className);
    while(strcmp(strings[funcStart+1], "(") != 0)
    {

        /*strcat(newName, spacing[funcStart+1]);*/
        strcat(newName, strings[funcStart+1]);
        funcStart++;
    }

    /*while the end bracket for parameter list is not found*/
    while (strcmp(strings[count],")") != 0)
    {
        /*if word is a type, check if other words following are types*/
        if (isKeyword(strings[count]) == 1)
        {
            /*if next keyword contains a **/
            if (isKeyword(strings[count+1]) == 3  || isKeyword(strings[count+1]) == 4)
            {
                fprintf(toWrite, "%c", strings[count][0]-32);
                temp[0] = strings[count][0]-32;
                strcat(newName, temp);

                if (isKeyword(strings[count+1]) == 3)
                    count += 3;
                else if (isKeyword(strings[count+1]) == 4)
                    count += 2;
            }
            else
            {
                fprintf(toWrite, "%c", strings[count][0]);
                temp[0] = strings[count][0];
                strcat(newName, temp);
                count++;
            }
        }
        /*else if current word is 'struct'*/
        else if (isKeyword(strings[count]) == 2)
        {
            fprintf(toWrite, "%c", strings[count][0]);
            temp[0] = strings[count][0];
            strcat(newName, temp);
            /*if * is in between struct name and variable, ex struct myStruct * a*/
            if (isKeyword(strings[count+2]) == 3)
            {
                fprintf(toWrite, "%c", strings[count+1][0] - 32);
                temp[0] = strings[count+1][0]-32;
                strcat(newName, temp);
                count++;
            }
            /*else if * is attached to struct name, ex struct myStruct* a*/
            else if (isKeyword(strings[count+2]) == 4)
            {
                fprintf(toWrite, "%c", strings[count+1][0] - 32);
                temp[0] = strings[count+1][0]-32;
                strcat(newName, temp);
            }
            /*else if * is attached to struct variable name, ex struct myStruct *a*/
            else if (isKeyword(strings[count+1]) == 4)
            {
                fprintf(toWrite, "%c", strings[count+1][0]-32);
                temp[0] = strings[count+1][0]-32;
                strcat(newName, temp);
            }
            else
            {
                fprintf(toWrite, "%c", strings[count+1][0]);
                temp[0] = strings[count+1][0];
                strcat(newName, temp);
            }

            count += 3;
        }
        /*else if the keyword doesn't contain a type, but contains a **/
        else if (isKeyword(strings[count]) == 5)
        {
            fprintf(toWrite, "%c", strings[count][0] - 32);
            temp[0] = strings[count][0]-32;
            strcat(newName, temp);
            count+= 2;
        }
        else
            count += 1;

        /*if blank, increase count*/
        if (strcmp(strings[count], "") == 0)
            count += 1;
        /*else if a comma, skip to the next keyword and print a | to separate parameters in method name in order to ensure unique method signatures*/
        else if (strcmp(strings[count], ",") == 0)
        {
            count += 2;
            fprintf(toWrite, "|");
            temp[0] = '|';
            strcat(newName, temp);
        }
    }

    fprintf(toWrite, "%c", ')');

    return newName;
}
