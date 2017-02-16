/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
January 29th, 2016        Assignment 1
***************************************************/

#include "helperFunctions.h"

/*function to inialize a 2D array of strings*/
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

/*function to initialize a string*/
char* initString (int size)
{
    char* string = malloc(sizeof(char) * size);

    int i = 0;
    for (i = 0; i < size; i++)
        string[i] = '\0';

    return string;
}

/*function to reset all characters in a string to '\0'*/
char * clearString (char* toClear, int size)
{
    int i;

    for (i = 0; i < size; i++)
        toClear[i] = '\0';

    return toClear;
}
/*function to free all memory allocated for a 2D string array*/
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

/*function to resize a 2D array of strings and return a larger one with all contents copied in*/
char ** resizeArray (char ** oldArray, int rows, int columns)
{
    char ** newArray;
    newArray = initArray(rows * 2, columns);

    int i, j;

    for (i = 0; i < rows; i++)
    {
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
    else if (strcmp(word, "char**") == 0)
        return 6;

    return 0;
}

/*function to format output to conform to C syntax and print it to the C file*/
int printToFile (char* fileName, char** spacing, char** strings, int rowCnt)
{
    int nameLen = strlen(fileName);
    int i;
    int inClass = 0;
    int isFunc = 0;
    int braceCount = 0;
    int openBraceCount = 0;
    int closeBraceCount = 0;
    char className[1000] = "";
    char** functions = NULL;
    int functionRows = 150;
    int functionCols = 10;
    int functionRowCnt = 0;
    char tempSize[10];
    char** oldFunctionNames = initArray(100, 250);
    char** newFunctionNames = initArray(100, 250);
    int functionNamesRowCnt = 0;
    int functionNamesRows = 100;
    int oldFunctionNamesCols = 250;
    int newFunctionNamesCols = 250;
    int funcStart = 0;
    int funcEnd = 0;
    char* newName = NULL;
    int nameIndex = 0;
    int classVarIndex = 0;
    char** classVars = initArray(100, 250);
    int classVarsCnt = 0;
    char** classVarsClasses = initArray(100, 250);
    char** localClassVars = initArray(500, 250);
    int localClassVarsCnt = 0;

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
            strcpy(localClassVars[localClassVarsCnt], "class ");
            strcat(localClassVars[localClassVarsCnt], className);
            localClassVarsCnt++;
            /*saving class name*/
            strcpy(oldFunctionNames[functionNamesRowCnt], "class ");
            strcat(oldFunctionNames[functionNamesRowCnt], className);
            strcpy(newFunctionNames[functionNamesRowCnt], "class ");
            strcat(newFunctionNames[functionNamesRowCnt], className);
            functionNamesRowCnt++;
            functions = initArray(functionRows, functionCols);
            functionRowCnt = 0;
        }
        /*else if at beginning of class where { is attached to class name*/
        else if (strcmp(strings[i], "class") == 0 && strstr(strings[i+1], "{") != NULL)
        {
            fprintf(toWrite, "%sstruct", spacing[i]);
            inClass = 1;
            strcpy(localClassVars[localClassVarsCnt], "class ");
            strcat(localClassVars[localClassVarsCnt], className);
            localClassVarsCnt++;
            strcpy(className, strings[i+1]);
            /*saving class name*/
            strcpy(oldFunctionNames[functionNamesRowCnt], "class ");
            strcat(oldFunctionNames[functionNamesRowCnt], className);
            strcpy(newFunctionNames[functionNamesRowCnt], "class ");
            strcat(newFunctionNames[functionNamesRowCnt], className);
            functionNamesRowCnt++;

            int z = 0;
            for (z = 0; z < strlen(className); z++)
            {
                if (className[z] == '{')
                    className[z] = (char)0;
            }
            functions = initArray(functionRows, functionCols);
            functionRowCnt = 0;
        }
        /*else if encountering a class variable*/
        else if (strcmp(strings[i], "class") == 0)
        {
            fprintf(toWrite, "%sstruct", spacing[i]);
            fprintf(toWrite, "%s%s", spacing[i+1], strings[i+1]);
            int h = 0;
            char** constructors = initArray(100, 250);
            int constructorCnt = 0;
            while (strcmp(strings[i+2+h], ";") != 0)
            {
                fprintf(toWrite, "%s%s", spacing[i+2+h],strings[i+2+h]);
                strcpy(classVars[classVarsCnt], strings[i+2 + h]);
                strcpy(classVarsClasses[classVarsCnt], strings[i+1]);
                classVarsCnt++;
                strcpy(constructors[constructorCnt], spacing[i]);
                strcat(constructors[constructorCnt], "constructor");
                strcat(constructors[constructorCnt], strings[i+1]);
                strcat(constructors[constructorCnt], "(&");
                strcat(constructors[constructorCnt], strings[i+2+h]);
                strcat(constructors[constructorCnt], ");");
                h++;
                constructorCnt++;

                if (strcmp(strings[i+2+h], ",") == 0)
                {
                    fprintf(toWrite, "%s%s", spacing[i+2+h],strings[i+2+h]);
                    h++;
                    if (strcmp(strings[i+2+h], "") == 0)
                    {
                        fprintf(toWrite, "%s%s", spacing[i+2+h],strings[i+2+h]);
                        h++;
                    }
                }
            }
            i = i+h+2;
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);
            for (h = 0; h < constructorCnt; h++)
                fprintf(toWrite, "%s", constructors[h]);
            destroyArray(constructors, 100); 
        }
        /*else if to count all opening brackets*/
        else if (strcmp(strings[i], "{") == 0)
        {
            openBraceCount++;
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);
        }
        /*else if to count all closing braces*/
        else if ((strcmp(strings[i], "}") == 0 /*|| (strcmp(strings[i], "}") == 0 && strcmp(strings[i+1], ";") == 0)*/))
        {
            closeBraceCount++;
            if (openBraceCount == closeBraceCount && inClass == 1)
            {
                inClass = 0;
                fprintf(toWrite, "%s%s", spacing[i], strings[i]);
                fprintf(toWrite, "%s%s", spacing[i+1], strings[i+1]);
                i++;
            
                int k = 0;
                char** funcClassVars = initArray(100, 250);
                int funcClassVarsCnt = 0;
                int funcClassVarIndex = 0;
                char** funcClassVarsClasses = initArray(100, 250);
                for (k = 0; k < functionRowCnt; k++)
                {
                    char** localFuncClassVars = createTempClassVarsList(localClassVars, localClassVarsCnt, className);
                    int localFuncClassVarsCnt = 0;
                    int localClassVarIndex = 0;
                    while(strcmp(localFuncClassVars[localFuncClassVarsCnt], "") != 0)
                    {
                        localFuncClassVarsCnt++;
                    }
                    int index1 = atoi(functions[k]);
                    int index2 = atoi(functions[k+1]);
                    int j = 0;
                    int l = 0;
                    for (j = index1; j <= index2; j++)
                    {
                        /*replacing function names for local class functions*/
                        for (l = 0; l < functionNamesRowCnt; l++)
                        {
                            if (strstr(oldFunctionNames[l], className) != NULL && strstr(oldFunctionNames[l], "class ") != NULL)
                            {
                                int g = l+1;
                                while (strstr(oldFunctionNames[g], "class ") == NULL && g < functionNamesRowCnt)
                                {
                                    if (strcmp(oldFunctionNames[g], strings[j]) == 0)
                                    {
                                        fprintf(toWrite, "%s%s" , spacing[j], newFunctionNames[g]);
                                        j++;
                                        break;
                                    }
                                    g++;
                                }
                            }

                        }

                        /*printing extra function parameters if necessary*/
                        if (strcmp(strings[j], "(") == 0)
                        {
                            int s = 0;
                            int found = 0;
                            for (s = 0; s < functionNamesRowCnt; s++)
                            {
                                if (strstr(strings[j-1], oldFunctionNames[s]) != NULL)
                                {
                                    found = 1;
                                    fprintf(toWrite, "%s%sstruct %s* classVarStruct", spacing[j], strings[j], className);
                                    if (strcmp(strings[j+1], ")") != 0)
                                        fprintf(toWrite, ", ");
                                    break;
                                }
                            }

                            if (found == 0)
                                fprintf(toWrite, "%s%s", spacing[j], strings[j]);
                            j++;
                        }

                        /*if encountering a class variable*/
                        if (strcmp(strings[j], "class") == 0)
                        {
                           fprintf(toWrite, "%sstruct%s%s", spacing[j], spacing[j+1], strings[j+1]);
                           int h = 0;
                           char** constructors = initArray(100, 250);
                           int constructorCnt = 0;

                           while (strcmp(strings[j+2+h], ";") != 0)
                           {
                                fprintf(toWrite, "%s%s", spacing[j+2+h],strings[j+2+h]);
                                /*copying class variable name and class into lists*/
                                strcpy(funcClassVars[funcClassVarsCnt], strings[j+2 + h]);
                                strcpy(funcClassVarsClasses[funcClassVarsCnt], strings[j+1]);
                                funcClassVarsCnt++;
                                /*creating constructor for the class variable and saving it in constructor list*/
                                strcpy(constructors[constructorCnt], spacing[j]);
                                strcat(constructors[constructorCnt], "constructor");
                                strcat(constructors[constructorCnt], strings[j+1]);
                                strcat(constructors[constructorCnt], "(&");
                                strcat(constructors[constructorCnt], strings[j+2+h]);
                                strcat(constructors[constructorCnt], ");");
                                h++;
                                constructorCnt++;
                                /*if multiple class varaible declarations on one line*/
                                if (strcmp(strings[j+2+h], ",") == 0)
                                {
                                    fprintf(toWrite, "%s%s", spacing[j+2+h],strings[j+2+h]);
                                    h++;
                                    if (strcmp(strings[j+2+h], "") == 0)
                                    {
                                        fprintf(toWrite, "%s%s", spacing[j+2+h],strings[j+2+h]);
                                        h++;
                                    }
                                }
                           } 
                            j = j+h+2;
                            fprintf(toWrite, "%s%s", spacing[j], strings[j]);
                            /*printing out constructors, then freeing constructor list*/
                            for (h = 0; h < constructorCnt; h++)
                                fprintf(toWrite, "%s", constructors[h]);
                            destroyArray(constructors, 100);
                            
                           
                        }

                        /*else if string is a local class variable*/
                        else if (isLocalClassVar(localFuncClassVars, localFuncClassVarsCnt, strings[j], className) != -1 && strcmp(strings[j], "") != 0)
                        {

                            localClassVarIndex = isLocalClassVar(localFuncClassVars, localFuncClassVarsCnt, strings[j], className);
                            fprintf(toWrite, "%s", spacing[j]);
                            /*if string before var is not a type*/
                            if (isKeyword(strings[j-1]) == 0)
                            {
                                
                                /*if string before is a comma*/
                                if (strcmp(strings[j-1], ",") == 0 || strcmp(strings[j-1], "") == 0)
                                {
                                    int d = j-2;
                                    while (isKeyword(strings[d]) != 1 || strcmp(strings[d], ";") == 0 || strstr(strings[d], "//") != NULL || strstr(strings[d], "\"") != NULL)
                                    {
                                        if (strcmp(strings[d], ",") == 0 || strcmp(strings[d], "") == 0)
                                            d--;
                                        else
                                            break;
                                    }

                                    /*if variable is local, delete from list*/
                                    if (isKeyword(strings[d]) == 1)
                                    {
                                        strcpy(localFuncClassVars[localClassVarIndex], "");
                                    }
                                    
                                }
                            }

                            else if (isKeyword(strings[j-1]) == 1)
                            {
                                strcpy(localFuncClassVars[localClassVarIndex], "");
                            }
                            if (strcmp(localFuncClassVars[localClassVarIndex], "") != 0)
                                fprintf(toWrite, "classVarStruct->");
                            fprintf(toWrite, "%s",strings[j]);

                            
                        }

                        /*if word is a class variable*/
                        else if ((funcClassVarIndex = isClassVar(funcClassVars, strings[j], funcClassVarsCnt)) != -1)
                        {
                            fprintf(toWrite, "%s%s", spacing[j],strings[j]);

                            int f = 0;
                            int g = 0;

                            /*if a class function is being used*/
                            if (strcmp(strings[j+1], ".") == 0)
                            {
                                for (f = 0; f < functionNamesRowCnt; f++)
                                {
                                    if (strstr(oldFunctionNames[f], funcClassVarsClasses[funcClassVarIndex]) != NULL && strstr(oldFunctionNames[f], "class ") != NULL)
                                    {
                                        g = f+1;
                                        while (strstr(oldFunctionNames[g], "class ") == NULL)
                                        {
                                            if (strcmp(oldFunctionNames[g], strings[j+2]) == 0)
                                            {
                                                fprintf(toWrite, ".%s%s&%s, " , newFunctionNames[g], strings[j+3], strings[j]);
                                                j += 3;
                                                break;
                                            }
                                            g++;
                                        }
                                    }

                                }
                            }
                        }

                        else
                            fprintf(toWrite, "%s%s", spacing[j],strings[j]);
                    }
                    k++;

                    destroyArray(localFuncClassVars, 250);
                }

                /*printing out constructors*/
                
                fprintf(toWrite, "\n\tvoid constructor%s (struct %s *tempStruct) {\n", className, className);
                for (k = nameIndex; k < functionNamesRowCnt; k++)
                {
                    if (strstr(newFunctionNames[k], "class") == NULL)
                        fprintf(toWrite, "\t\ttempStruct->%s = %s;\n", newFunctionNames[k], newFunctionNames[k]);
                }
                fprintf(toWrite, "\t}\n");

                destroyArray(functions, functionRows);
                destroyArray(funcClassVarsClasses, 100);
                destroyArray(funcClassVars, 100);
                
                functionRowCnt = 0;
                functions = NULL;

                nameIndex = functionNamesRowCnt;
            }

            else if (openBraceCount == closeBraceCount)
                fprintf(toWrite, "%s%s", spacing[i], strings[i]);
        }
        /*else if finds a (, handle for if encoutnering a function*/
        else if (strcmp(strings[i+1], "(") == 0 && strcmp(strings[i], "main") != 0)
        {
            int count = i+1;
            /*finding index of end bracket*/
            while(strcmp(strings[count], ")") != 0)
                count++;
            int funcBraceCount = 0;
            int funcCloseBraceCount = 0;

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
                if (strcmp(strings[i+1], "(") == 0)
                {
                    funcStart = i;
                    
                    while (strstr(spacing[funcStart], "\n") == NULL)
                        funcStart--;

                    funcEnd = funcStart;

                    while ((funcBraceCount != funcCloseBraceCount)|| strcmp(strings[funcEnd], "}")!= 0)
                    {
                        funcEnd++;
                        if (strcmp(strings[funcEnd], "}") == 0)
                            funcCloseBraceCount++;
                        else if (strcmp(strings[funcEnd], "{") == 0)
                            funcBraceCount++;
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
                    i = funcEnd;
                }
            }
            else
                fprintf(toWrite, "%s%s", spacing[i], strings[i]);  
        }
        
        /*else if a class variable is found*/
        else if (inClass == 1 && isKeyword(strings[i]) == 1 && strcmp(strings[i+2], "(") != 0)
        {
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);
            strcpy(localClassVars[localClassVarsCnt], strings[i+1]);
            localClassVarsCnt++;

            if (strcmp(strings[i+2], ",") == 0)
            {
                int v = i +3;
                while (strcmp(strings[v], ";") != 0)
                {
                    if (strcmp(strings[v], "") == 0)
                        v++;
                    strcpy(localClassVars[localClassVarsCnt], strings[v]);
                    localClassVarsCnt++;
                    v++;

                    if (strcmp(strings[v], ",") == 0 || strcmp(strings[v], "") == 0)
                    {
                        v++;
                        if (strcmp(strings[v], "") == 0)
                            v++;
                    }

                }
            }
        }
        /*else just print out spacing and string normally*/
        else
            fprintf(toWrite, "%s%s", spacing[i], strings[i]);

        /*if word is a class variable*/
        if ((classVarIndex = isClassVar(classVars, strings[i], classVarsCnt)) != -1)
        {
            int f = 0;
            int g = 0;

            /*if a class function is being used*/
            if (strcmp(strings[i+1], ".") == 0)
            {
                for (f = 0; f < functionNamesRowCnt; f++)
                {
                    if (strstr(oldFunctionNames[f], classVarsClasses[classVarIndex]) != NULL && strstr(oldFunctionNames[f], "class ") != NULL)
                    {
                        g = f+1;
                        while (strstr(oldFunctionNames[g], "class ") == NULL && g < functionNamesRowCnt)
                        {
                            if (strcmp(oldFunctionNames[g], strings[i+2]) == 0)
                            {
                                fprintf(toWrite, ".%s%s&%s" , newFunctionNames[g], strings[i+3], strings[i]);
                                if (strcmp(strings[i+4], ")") != 0)
                                    fprintf(toWrite, ", ");
                                i += 3;
                                break;
                            }
                            g++;
                        }
                    }

                }
            }
        }
    }

    /*freeing memory*/
    destroyArray(oldFunctionNames, functionNamesRows);
    destroyArray(newFunctionNames, functionNamesRows);
    destroyArray(classVars, 100);
    destroyArray(classVarsClasses, 100);
    destroyArray(localClassVars, 500);
    fclose(toWrite);
    return 0;
}

/*function to rename functions inside classes*/
char* renameFuncs(char** strings, char** spacing, int count, FILE* toWrite, int funcStart, char* className)
{
    /*mallocing for new name*/
    char* newName = malloc(sizeof(char) * 1000);
    strcpy(newName, "");
    char temp[2] = "";
    char params[1000];
    sprintf(params, "(struct %s*", className);
    char* tempName = malloc(sizeof(char) * 1000);
    strcpy(tempName, "");
    int countCpy = count-2;

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
        funcStart++;
    }

    if (strcmp(strings[funcStart+2], ")") != 0)
        strcat(params, ", ");

    strcpy(tempName, strings[funcStart]);

    /*eliminating the * in the function name if present*/
    if (strstr(tempName, "*") != NULL)
        memmove(tempName, tempName+1, strlen(tempName));
    strcat(newName, tempName);
    free(tempName);

    /*while the end bracket for parameter list is not found*/
    while (strcmp(strings[count],")") != 0)
    {
        /*if word is a type, check if other words following are types*/
        if (isKeyword(strings[count]) == 1)
        {
            /*if next keyword contains a '*' */
            if (isKeyword(strings[count+1]) == 3  || isKeyword(strings[count+1]) == 4)
            {
                fprintf(toWrite, "%c", strings[count][0]-32);
                temp[0] = strings[count][0]-32;
                strcat(newName, temp);
                strcat(params, strings[count]);
                strcat(params, "*");

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
                strcat(params, strings[count]);
                strcat(params, " ");
                count++;
            }
        }
        /*else if current word is 'struct'*/
        else if (isKeyword(strings[count]) == 2)
        {
            fprintf(toWrite, "%c", strings[count][0]);
            temp[0] = strings[count][0];
            strcat(newName, temp);
            strcat(params, strings[count]);
            strcat(params, " ");
            /*if * is in between struct name and variable, ex struct myStruct * a*/
            if (isKeyword(strings[count+2]) == 3)
            {
                fprintf(toWrite, "%c", strings[count+1][0] - 32);
                temp[0] = strings[count+1][0]-32;
                strcat(newName, temp);
                strcat(params, strings[count+1]);
                strcat(params, "*");
                count++;
            }
            /*else if * is attached to struct name, ex struct myStruct a* */
            else if (isKeyword(strings[count+2]) == 4)
            {
                fprintf(toWrite, "%c", strings[count+1][0] - 32);
                temp[0] = strings[count+1][0]-32;
                strcat(params, strings[count+1]);
                strcat(params, "*");
                strcat(newName, temp);
            }
            /*else if * is attached to struct variable name, ex struct myStruct* a*/
            else if (isKeyword(strings[count+1]) == 4)
            {
                fprintf(toWrite, "%c", strings[count+1][0]-32);
                temp[0] = strings[count+1][0]-32;
                strcat(params, strings[count+1]);
                strcat(params, "*");
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
        /*else if the keyword doesn't contain a type, but contains a * */
        else if (isKeyword(strings[count]) == 5)
        {
            fprintf(toWrite, "%c", strings[count][0] - 32);
            temp[0] = strings[count][0]-32;
            strcat(newName, temp);
            strcat(params, strings[count]);
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
            fprintf(toWrite, "_");
            temp[0] = '_';
            strcat(newName, temp);
            strcat(params, ", ");
        }
    }

    fprintf(toWrite, ")%s%s", params, ");");
    strcpy(strings[countCpy], newName);
    return newName;
}

/*function to check if a string is a class variable*/
int isClassVar (char** classVars, char* string, int classVarsCnt)
{
    int i = 0;
        
    for (i = 0; i < classVarsCnt; i++)
    {
        if (strcmp(classVars[i], string) == 0)
        {
            return i;
        }
    }

    return -1;
}

int isLocalClassVar (char** localClassVars, int localClassVarsCnt, char* string, char* className)
{
    int i = 0;

    for (i = 0; i < localClassVarsCnt; i++)
    {
        if (strcmp(localClassVars[i], string) == 0)
        {
            return i;
        }
    }

    return -1;
}

char** createTempClassVarsList(char** localClassVars, int localClassVarsCnt, char* className)
{
    int i = 0;
    char** tempList = initArray(250, 250);
    int tempListCnt = 0;
    for (i = 0; i < localClassVarsCnt; i++)
    {
        if (strstr(localClassVars[i], "class ") != NULL && strstr(localClassVars[i], className) != NULL)
        {

            int j = i+1;
            while (strstr(localClassVars[j], "class ") == NULL && j < localClassVarsCnt)
            {
                strcpy(tempList[tempListCnt], localClassVars[j]);
                tempListCnt++;
                j++;
            }

            return tempList;
        }
    }

    return NULL;
}