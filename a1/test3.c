#include<stdio.h>
#include<stdlib.h>


struct A {
int a;
   int (*Afn)(struct A*);
};
   int Afn(struct A* classVarStruct) {
      classVarStruct->a = 3;
   }
	void constructorA (struct A *tempStruct) {
		tempStruct->Afn = Afn;
	}



/* set the value of a class variable from a method within the class */

int main(int argc, char *argv[]) {
struct A myA;
constructorA(&myA);

   myA.Afn(&myA);
   if (myA.a == 3)
      return(0);
   else
      return(1);
}