#include<stdio.h>
#include<stdlib.h>

struct A {
int a;
   int (*AfnC)(struct A*, char*);
};
   int AfnC(struct A* classVarStruct, char *str) {
      if (strcmp(str, "abc") == 0)
         return(0);
      else
         return(1);
   }
	void constructorA (struct A *tempStruct) {
		tempStruct->AfnC = AfnC;
	}



/* set the value of a class variable using a method pointer parameter */
/* using a method in an expression */

int main(int argc, char *argv[]) {
struct A myA;
constructorA(&myA);
char *str = "abc";

   if ( myA.AfnC(&myA, str)==0)
      return(0);
   else
      return(1);
}
