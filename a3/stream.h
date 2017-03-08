/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2017       Assignment 2
***************************************************/

#ifndef __CCORNELI_STREAM_H__
#define __CCORNELI_STREAM_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

struct userPost {
    char * username;
    char * streamname;
    char * date;
    char * text;
}; typedef struct userPost userPost;


/*function to add a new posting to a specific stream*/
void updateStream (struct userPost * st);

/*function to add a user to a list of streams*/
void addUser(char * username, char * list, int isRemovable);

/*function to remove a user from a stream*/
void removeUser(char * username, char * list);

/*function to check if an author is already present in a stream's file*/
int checkAuthorExists(char* author, char* fileName);

/*function to free all memory for a user post struct*/
void destroyStruct(userPost* toDestroy);

/*function to update the master stream list if a new stream is created*/
void updateMasterList(char* stream);
#endif
