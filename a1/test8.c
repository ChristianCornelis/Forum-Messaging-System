#include<stdio.h>
#include<stdlib.h>


struct A {
int a, b;
   int (*Afni)(struct A*, int );
   int (*Afni_)(struct A*, int , );
};
   int Afni(struct A* classVarStruct, int i) {
      classVarStruct->a = i;
   }
   int Afni_(struct A* classVarStruct, int i,int j) {
      classVarStruct->b = i + j;
   }
	void constructorA (struct A *tempStruct) {
		tempStruct->Afni = Afni;
		tempStruct->Afni_ = Afni_;
	}




/* overloaded methods, comment with the word class in it */

int main(int argc, char *argv[]) {
struct A myA, myB;
constructorA(&myA);
constructorA(&myB);
int vali, valj;

   vali = 1;
   valj = 2;

   myA.Afni(&myA, vali);
   myA.Afni(&myA, vali,valj);

   if ((myA.a == 1) && (myA.b == 3))
      return(0);
   else
      return(1);
}