#include "helperFunctions.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Incorrect number of arguments. \nExitting");
        return 1;
    }
    FILE* ccFile = NULL;
    ccFile = fopen(argv[1], "r");

    if (ccFile == NULL)
    {
        printf("File not found. \nExitting");
        return 1;
    }

    int rows = 600;
    int columns = 600;
    int character = -1;
    int prevCharacter = -1;
    int prevPrevCharacter = -1;
    char** spacingArray = initArray(rows, columns);
    char** stringArray = initArray(rows, columns);

    /*intializing row and column counters for both arrays*/
    int rowCnt = 0;
    int spacingColCnt = 0;
    int stringColCnt = 0;

    character = getc(ccFile);
    while (character != EOF)
    {
        printf("in");
        if (character == '"')
        {
            stringArray[rowCnt][stringColCnt] = (char)character;
            rowCnt++;
            if (checkSize(rowCnt, rows) == 1)
            {
                stringArray = resizeArray(stringArray, rows, columns);
                spacingArray = resizeArray(spacingArray, rows, columns);
                rows *= 2;
            }
            stringColCnt = 0;
            spacingColCnt = 0;
            character = getc(ccFile);

            while (character != '"')
            {
                /*if (character == ' ' || character == '\t' || character == '\n' || character == '\r')
                {
                    stringArray[rowCnt][stringColCnt] = (char) character;
                    stringColCnt++;
                    if (stringColCnt == columns)
                    {
                        rowCnt++;
                        spacingColCnt = 0;
                        spacingColCnt = 0;
                        if (checkSize(rowCnt, rows) == 1)
                        {
                            stringArray = resizeArray(stringArray, rows, columns);
                            spacingArray = resizeArray(spacingArray, rows, columns);
                            rows *= 2;
                        }
                    }
                    character = getc(ccFile);
                    while (character == ' ' || character == '\t' || character == '\n' || character == '\r')
                    {
                        spacingArray[rowCnt][spacingColCnt] = (char) character;
                        spacingColCnt++;
                        if (spacingColCnt == columns)
                        {
                            rowCnt++;
                            spacingColCnt = 0;
                            spacingColCnt = 0;
                            if (checkSize(rowCnt, rows) == 1)
                            {
                                stringArray = resizeArray(stringArray, rows, columns);
                                spacingArray = resizeArray(spacingArray, rows, columns);
                                rows *= 2;
                            }
                        }
                        character = getc(ccFile);
                    }

                    stringArray[rowCnt][stringColCnt] = (char) character;
                    stringColCnt++;
                }

                else */if (character == '\\')
                {
                    stringArray[rowCnt][stringColCnt] = (char) character;
                    stringColCnt++;
                    if (stringColCnt == columns)
                    {
                        rowCnt++;
                        stringColCnt = 0;
                        spacingColCnt = 0;
                        if (checkSize(rowCnt, rows) == 1)
                        {
                            stringArray = resizeArray(stringArray, rows, columns);
                            spacingArray = resizeArray(spacingArray, rows, columns);
                            rows *= 2;
                        }
                    }
                    character = getc(ccFile);
                    stringArray[rowCnt][stringColCnt] = (char) character;
                    stringColCnt++;

                    if (stringColCnt == columns)
                    {
                        rowCnt++;
                        stringColCnt = 0;
                        spacingColCnt = 0;
                        if (checkSize(rowCnt, rows) == 1)
                        {
                            stringArray = resizeArray(stringArray, rows, columns);
                            spacingArray = resizeArray(spacingArray, rows, columns);
                            rows *= 2;
                        }
                    }
                }
                else
                {
                    stringArray[rowCnt][stringColCnt] = (char) character;
                    stringColCnt++;
                    if (stringColCnt == columns)
                    {
                        rowCnt++;
                        stringColCnt = 0;
                        spacingColCnt = 0;
                        if (checkSize(rowCnt, rows) == 1)
                        {
                            stringArray = resizeArray(stringArray, rows, columns);
                            spacingArray = resizeArray(spacingArray, rows, columns);
                            rows *= 2;
                        }
                    }
                }
                character = getc(ccFile);

            }
            stringArray[rowCnt][stringColCnt] = (char)character;
            rowCnt++;
            if (checkSize(rowCnt, rows) == 1)
            {
                stringArray = resizeArray(stringArray, rows, columns);
                spacingArray = resizeArray(spacingArray, rows, columns);
                rows *= 2;
            }
            stringColCnt = 0;
            spacingColCnt = 0;
        }

        else if (character == '/')
        {
            stringArray[rowCnt][stringColCnt] = (char) character;
            stringColCnt++;

            if ((character = getc(ccFile)) == '/')
            {
                while (character != '\n' && character != EOF)
                {
                    stringArray[rowCnt][stringColCnt] = (char) character;
                    stringColCnt++;

                    if (stringColCnt == columns)
                    {
                        rowCnt++;
                        stringColCnt = 0;
                        spacingColCnt = 0;
                        if (checkSize(rowCnt, rows) == 1)
                        {
                            stringArray = resizeArray(stringArray, rows, columns);
                            spacingArray = resizeArray(spacingArray, rows, columns);
                            rows *= 2;
                        }
                    }

                    character = getc(ccFile);
                }
                printf("CHARACTER: %d", character);
                if (character == '\n' || character == '\r')
                {

                    rowCnt++;
                    if (checkSize(rowCnt, rows) == 1)
                    {
                        stringArray = resizeArray(stringArray, rows, columns);
                        spacingArray = resizeArray(spacingArray, rows, columns);
                        rows *= 2;
                    }
                    stringColCnt = 0;
                    spacingColCnt = 0;
                    spacingArray[rowCnt][spacingColCnt] = (char) character;
                }
            }

            else if (character == '*')
            {
                stringArray[rowCnt][stringColCnt] = (char) character;
                stringColCnt++;
                character = getc(ccFile);
                prevCharacter = '0';
                while (prevCharacter != '*' || character != '/')
                {
                    stringArray[rowCnt][stringColCnt] = (char) character;
                    stringColCnt++;
                    prevPrevCharacter = prevCharacter;
                    prevCharacter = character;
                    character = getc(ccFile);

                    if (prevPrevCharacter == '/' && prevCharacter == '*' && character == '/')
                        prevCharacter = '0';

                }
                stringArray[rowCnt][stringColCnt] = (char) character;
                rowCnt++;
                if (checkSize(rowCnt, rows) == 1)
                {
                    stringArray = resizeArray(stringArray, rows, columns);
                    spacingArray = resizeArray(spacingArray, rows, columns);
                    rows *= 2;
                }
                stringColCnt = 0;
                spacingColCnt = 0;
            }
        }

        /*else if (character == ' ' || character == '\n' || character == '\t')
        {
            rowCnt++;
            if (checkSize(rowCnt, rows) == 1)
            {
                stringArray = resizeArray(stringArray, rows, columns);
                spacingArray = resizeArray(spacingArray, rows, columns);
                rows *= 2;
                printf("expanded: %d\n", rows);
            }
            stringColCnt = 0;
            spacingColCnt = 0;
            spacingArray[rowCnt][spacingColCnt] = (char) character;
        }*/

        else if (character == ' ' || character == '\t' || character == '\n')
        {
            rowCnt++;
            if (checkSize(rowCnt, rows) == 1)
            {
                stringArray = resizeArray(stringArray, rows, columns);
                spacingArray = resizeArray(spacingArray, rows, columns);
                rows *= 2;
            }
            stringColCnt = 0;
            spacingColCnt = 0;
            spacingArray[rowCnt][spacingColCnt] = (char) character;
            spacingColCnt++;
            character = getc(ccFile);
            while (character == ' ' || character == '\t' || character == '\n')
            {
                spacingArray[rowCnt][spacingColCnt] = (char) character;
                spacingColCnt++;
                if (spacingColCnt == columns)
                {
                    rowCnt++;
                    spacingColCnt = 0;
                    spacingColCnt = 0;
                    if (checkSize(rowCnt, rows) == 1)
                    {
                        stringArray = resizeArray(stringArray, rows, columns);
                        spacingArray = resizeArray(spacingArray, rows, columns);
                        rows *= 2;
                    }
                }
                character = getc(ccFile);
            }
            continue;
        }
        else if (character == '(' || character == ')')
        {
            if (stringColCnt != 0)
            {
                rowCnt++;
                if (checkSize(rowCnt, rows) == 1)
                {
                    stringArray = resizeArray(stringArray, rows, columns);
                    spacingArray = resizeArray(spacingArray, rows, columns);
                    rows *= 2;
                }
                stringColCnt = 0;
                spacingColCnt = 0;
            }
            stringArray[rowCnt][stringColCnt] = (char) character;
            stringColCnt++;

            rowCnt++;
            if (checkSize(rowCnt, rows) == 1)
            {
                stringArray = resizeArray(stringArray, rows, columns);
                spacingArray = resizeArray(spacingArray, rows, columns);
                rows *= 2;
            }
            stringColCnt = 0;
            spacingColCnt = 0;
        }
        else
        {
            stringArray[rowCnt][stringColCnt] = (char) character;
            stringColCnt++;
            if (stringColCnt == columns -1)
            {
                rowCnt++;
                stringColCnt = 0;
                stringColCnt = 0;
                if (checkSize(rowCnt, rows) == 1)
                {
                    stringArray = resizeArray(stringArray, rows, columns);
                    spacingArray = resizeArray(spacingArray, rows, columns);
                    rows *= 2;
                }
            }
        }
        character = getc(ccFile);
    }

    int i;

    for (i = 0; i < rowCnt; i++)
    {
        printf("%s\n", stringArray[i]);
        /*printf("%s%s" , spacingArray[i], stringArray[i]);*/
        /*if (strcmp(stringArray[i], "\"") == 0)
            printf("\n");
        else if (strcmp(stringArray[i], "class") == 0)
            printf("struct");*/
    }

    printToFile(argv[1], spacingArray, stringArray, rowCnt);
    destroyArray(stringArray, rows);
    destroyArray(spacingArray, rows);
    fclose(ccFile);

    return 0;
}
