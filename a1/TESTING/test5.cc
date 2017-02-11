#include<stdio.h>
#include<stdlib.h>


class A {
int a;
   int fn(char *str) {
      if (strcmp(str, "abc") == 0)
         return(0);
      else
         return(1);
   }
};


/* set the value of a class variable using a method pointer parameter */
/* using a method in an expression */

int main(int argc, char *argv[]) {
class A myA;
char *str = "abc";

   if ( myA.fn(str)==0)
      return(0);
   else
      return(1);
}

