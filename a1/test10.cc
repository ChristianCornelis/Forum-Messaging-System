#include<stdio.h>
#include<stdlib.h>

struct mystruct {
   float f;
};

class
E {
   float
      abc = 1.2;
   struct mystruct * method() {
   struct mystruct *ptr;
      ptr = malloc(sizeof(struct mystruct));
      ptr->f = abc;
      return(ptr);
   }
};



/* complex class structure with initialized variable */

int main(int argc, char *argv[]) {
class E myE;
struct mystruct *p;
   
   p = myE.method();
   if (p->f == 1.2f)
      return(0);
   else
      return(1);
}

