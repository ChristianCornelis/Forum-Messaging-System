#include<stdio.h>
#include<stdlib.h>


class A {
int a, b;
   int fn(int i) {
      a = i;
   }
   int fn(int i,int j) {
      b = i + j;
   }
};



/* overloaded methods, comment with the word class in it */

int main(int argc, char *argv[]) {
class A myA, myB;
int vali, valj;

   vali = 1;
   valj = 2;

   myA.fn(vali);
   myA.fn(vali,valj);

   if ((myA.a == 1) && (myA.b == 3))
      return(0);
   else
      return(1);
}

