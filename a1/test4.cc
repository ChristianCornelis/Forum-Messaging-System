#include<stdio.h>
#include<stdlib.h>


class A {
int a;
   void fn(int value) {
      a = value;
   }
};


/* set the value of a class variable using a method parameter */

int main(int argc, char *argv[]) {
class A myA;
int i;

   i = 3;
   myA.fn(i);
   if (myA.a == 3)
      return(0);
   else
      return(1);
}

