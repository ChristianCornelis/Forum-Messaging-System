/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2016       Assignment 2
***************************************************/

#ifndef __CCORNELI_STREAM_H__
#define __CCORNELI_STREAM_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct userPost {
    char * username;
    char * streamname;
    char * date;
    char * text;
}; typedef struct userPost userPost;

void updateStream (struct userPost * st);
void addUser(char * username, char * list, int isRemovable);
void removeUser(char * username, char * list);
/*function to check if an author is already present in a stream's file*/
int checkAuthorExists(char* author, char* fileName);
#endif
