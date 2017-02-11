#include<stdio.h>
#include<stdlib.h>

struct mystruct {
   float f;
};

struct
E {
   float
      abc = 1.2;
   struct mystruct * (*Emethod)(struct E*);
};
   struct mystruct * Emethod(struct E* classVarStruct) {
   struct mystruct *ptr;
      ptr = malloc(sizeof(struct mystruct));
      ptr->f = classVarStruct->abc;
      return(ptr);
   }
	void constructorE (struct E *tempStruct) {
		tempStruct->Emethod = Emethod;
	}




/* complex class structure with initialized variable */

int main(int argc, char *argv[]) {
struct E myE;
constructorE(&myE);
struct mystruct *p;
   
   p = myE.Emethod(&myE);
   if (p->f == 1.2f)
      return(0);
   else
      return(1);
}