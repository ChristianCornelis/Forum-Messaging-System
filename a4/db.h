#ifndef __CCORNELI_DATABASE_MANAGER_H__
#define __CCORNELI_DATABASE_MANAGER_H__

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

/*defines*/
#define MAX_QUERY 512
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "ccorneli"
#define PASSWORD "0939357"
#define DATABASE "dursley.socs.uoguelph.ca"

/*function to handle errors within the database*/
void handleError (char* msg, MYSQL *mysql);

#endif