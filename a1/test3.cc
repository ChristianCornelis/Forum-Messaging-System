#include<stdio.h>
#include<stdlib.h>


class A {
int a;
   int fn() {
      a = 3;
   }
};


/* set the value of a class variable from a method within the class */

int main(int argc, char *argv[]) {
class A myA;

   myA.fn();
   if (myA.a == 3)
      return(0);
   else
      return(1);
}

