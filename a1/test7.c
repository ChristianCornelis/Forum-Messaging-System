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


struct B {
int b;
   int (*Bfn)(struct B*);
};
   int Bfn(struct B* classVarStruct) {
      classVarStruct->b = 4;
   }
	void constructorB (struct B *tempStruct) {
		tempStruct->Bfn = Bfn;
	}



/* two classes which contain the same method name */

int main(int argc, char *argv[]) {
struct A myA;
constructorA(&myA);
struct B myB;
constructorB(&myB);

   myA.Afn(&myA);
   myB.Bfn(&myB);
   if ((myA.a == 3) && (myB.b == 4))
      return(0);
   else
      return(1);
}