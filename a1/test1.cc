#include<stdio.h>
#include<stdlib.h>


class A {
   int a;
};



/* reference a class variable */

int main(int argc, char *argv[]) {
class A myA;
   myA.a = 3;
   if (myA.a == 3)
      return(0);
   else
      return(1);
}

