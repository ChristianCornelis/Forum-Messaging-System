#include<stdio.h>
#include<stdlib.h>


class A {
int a, b;
   int fn(int i, float *pj) {
      a = i + (int) *pj;
   }
   int fn(int i,float j,long long k) {
      b = i + (int) j + (int) k;
   }
};



/* overloaded methods with multiple types */

int main(int argc, char *argv[]) {
class A myA;
int vali;
float valj;
long long valk;
float *pj;

   vali = 1;
   valj = 2.5;
   valk = 10;
   pj = &valj;

   myA.fn(vali,pj);
   myA.fn(vali,valj,valk);

   if ((myA.a == 3) && (myA.b == 13))
      return(0);
   else
      return(1);
}

