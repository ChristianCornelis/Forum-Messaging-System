#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a;

	/* /different ways to access variables */
class A {
int a;
   void print1 (struct myStruct * b, int *a[], long long double* i, float * s) {
		// print parameter - local to the function
      printf("output should be 1: %d\n", a);
   }
   void print2(int a) {
		// create a local variable
      int a = 2;
		// print local variable
      printf("output should be 2: %d\n", a);
   }
   void print3(float b) {
		// there is a class variable named a so
		// assign value to it and print the class variable
      a = 3;
      printf("output should be 3: %d\n", a);
   }
};

class B {
   void print4(int b) {
		// there is no class variable named a so print global variable
      printf("output should be 4: %d\n", a);
   }
};

	// simple function outside of a class
float product(float a, float b) {
   return( a*b );
}



int main(int argc, char *argv[]) {
class A myA;
class B myB;
int value;

   printf("Hello    \" there\n");
   strcpy(str, "A string containing the word class may be tricky");

   a = 4;
   value = 1;

   myA.print1(value);
   myA.print2();
   myA.print3();

   myB.print4();

}
