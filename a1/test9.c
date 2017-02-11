#include<stdio.h>
#include<stdlib.h>


struct A {
int a, b;
   int (*Afni_F)(struct A*, int , float*);
   int (*Afni__l)(struct A*, int , , long );
};
   int Afni_F(struct A* classVarStruct, int i, float *pj) {
      classVarStruct->a = i + (int) *pj;
   }
   int Afni__l(struct A* classVarStruct, int i,float j,long long k) {
      classVarStruct->b = i + (int) j + (int) k;
   }
	void constructorA (struct A *tempStruct) {
		tempStruct->Afni_F = Afni_F;
		tempStruct->Afni__l = Afni__l;
	}




/* overloaded methods with multiple types */

int main(int argc, char *argv[]) {
struct A myA;
constructorA(&myA);
int vali;
float valj;
long long valk;
float *pj;

   vali = 1;
   valj = 2.5;
   valk = 10;
   pj = &valj;

   myA.Afni_F(&myA, vali,pj);
   myA.Afni_F(&myA, vali,valj,valk);

   if ((myA.a == 3) && (myA.b == 13))
      return(0);
   else
      return(1);
}