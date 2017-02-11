#include<stdio.h>
#include<stdlib.h>


class A {
   int fn() {
      return(3);
   }
};


/* use the return value of method in a class */

int main(int argc, char *argv[]) {
class A myA;
int retValue;

   retValue = myA.fn();
   if (retValue == 3)
      return(0);
   else
      return(1);
}

