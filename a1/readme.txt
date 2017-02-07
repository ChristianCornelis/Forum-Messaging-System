/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
January 29th, 2016        Assignment 1
***************************************************/

ISSUES:
*******

-Global class variables will have a constructor to initialize the function pointers found in thye class functions. This will be present directly after the declaration of the global class variable, no matter where it is, which will yield a compilation error if the class hasn't already been defined.

-Method overloading will not work. This is because I did not have time to implement a system that checks the old function name along with it's parameters in order to determine which new function name to switch it with. If methods have unique names, these should work alright though.

-If a class has a function inside of it which includes a semicolon after it, the function name will contain two semicolons in the class definition in the generated C file.

-If a function returns a pointer and the asterisk is attached to the function name, it will be treated as a part of the function name, and will cause problems.

-If a class function returns an array and the square brackets are attached to the name, then the parser will not output a correctly-formatted name when creating constructors, functions, and function pointers.

-If a class function is called from a function inside the same class (such as in class C in sample 3), an improper call will be outputted, as my parser thinks it is looking at a function to rename since the class variable name will not be present.


To clarify:
-I realize that my function renaming may look funny, but, when concatenating characters to represent the parameter types onto the function names, I decided to delimit the parameter initials with an underscore in order to ensure that methods are given unique names. For example, if two methods named add were created, with one taking a long long and the other taking in two long's as parameters, both methods would be created with the name: addll. Using my method, these two methods would be named addl_l and addll respectively, giving them unique names and eliminating the risk of problems upon use.


Here is some Beavis and Butthead ASCII art to encourage you to have mercy on me : )

       .------..
     -          -
   /              \
 /                   \
/    .--._    .---.   |
|  /      -__-     \   |
| |                 |  |
 ||     ._   _.      ||
 ||      o   o       ||
 ||      _  |_      ||
 C|     (o\_/o)     |O     Uhhh, this program
  \      _____      /      is like, busted or
    \ ( /#####\ ) /        something.
     \  `====='  /
      \  -___-  /
       |       |
       /-_____-\
     /           \
   /               \
  /__|  AC / DC  |__\
  | ||           |\ \
