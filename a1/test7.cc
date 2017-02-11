#include<stdio.h>
#include<stdlib.h>


class A {
int a;
   int fn() {
      a = 3;
   }
};

class B {
int b;
   int fn() {
      b = 4;
   }
};


/* two classes which contain the same method name */

int main(int argc, char *argv[]) {
class A myA;
class B myB;

   myA.fn();
   myB.fn();
   if ((myA.a == 3) && (myB.b == 4))
      return(0);
   else
      return(1);
}

