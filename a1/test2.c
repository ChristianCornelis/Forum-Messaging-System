#include<stdio.h>
#include<stdlib.h>


struct A {
   int (*Afn)(struct A*);
};
   int Afn(struct A* classVarStruct) {
      return(3);
   }
	void constructorA (struct A *tempStruct) {
		tempStruct->Afn = Afn;
	}



/* use the return value of method in a class */

int main(int argc, char *argv[]) {
struct A myA;
constructorA(&myA);
int retValue;

   retValue = myA.Afn(&myA);
   if (retValue == 3)
      return(0);
   else
      return(1);
}