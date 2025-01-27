/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
March 31st, 2017          Assignment 4
***************************************************/

#ifndef __CCORNELI_DB_H__
#define __CCORNELI_DB_H__

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

/*defines*/
#define MAX_QUERY_LENGTH 12000
#define HOSTNAME  "dursley.socs.uoguelph.ca"
#define USERNAME  "ccorneli"
#define PASSWORD  "0939357"
#define DATABASE  "ccorneli"

/*function to handle errors within the database*/
void handleError (char* msg, MYSQL *mysql);

/*function to clear the query*/
char* clearQuery(char* query);
#endif