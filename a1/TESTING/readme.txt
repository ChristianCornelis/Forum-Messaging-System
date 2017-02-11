
Marking Assignment 1

There are two parts to marking the assignment. The first is testing the
program. The second is marking how the assignment was submitted.

There is a testing program that you can run and it will tell you how many
test cases passed and failed.  It relies on the assignments being submitted
correctly so it won’t work if the executable is in a subdirectory or if
it is not named a1. It also assumes that the assignment is in a directory
containing your login name.

The process for marking the assignment is:

1. cd into the directory containing the assignment and type make. This should
create an executable named a1. If it doesn’t then do the following:
   -if the assignment is in a subdirectory named a1 then rename it to
    something else, such as mv a1 assign1 (you need to do this so we can
    move the a1 executable into this directory since the marking program uses
    the directory name which contains the login id to name the
    marking file)
   -cd into that directory and type make, this will hopefully create a
    program named a1
   -mv a1 up a directory (mv a1 ..), if it isn’t named a1 the rename it
    to a1 and move it up a directory
   -cd up a level (cd ..)

2. You should now have a program named a1 in the directory named after
the login id.

3. Copy the testing files into that directory. You should end up with a lot
of files named test*.cc, a make.test, and a make.py in the directory.

4. Run ./mark.py. This will run the a1 program on all of the test*.cc files
and create .c files. It will then try to compile and run the files.
It will test the output of program and store the results in a file named
username-marking.txt. The username will be that actual login for that person.

5. The program will also print some other marking deductions at the end of
the file.

A sample marking file looks like this:

CIS*2750 Assignment 1
Marking Scheme
Marked out of 10.

Test Cases

**** Fail test 1                      ****  -1
**** Success test 2
**** Success test 3
**** Success test 4
**** Fail test 5                      ****  -1
**** Fail test 6                      ****  -1
**** Success test 7
**** Fail test 8                      ****  -1
**** Fail test 9                      ****  -1
**** Fail test 10                      ****  -1


General Assignment Requirements
-1  Specification not followed.
-1  Poor formatting or variable names in source code.


Submission and Documentation
-1   Assignment not submitted correctly -in a subdirectory or named incorrectly.
-1   File not submitted as a tar file - submitted as a zip file.
-1   Documentation not included, name or ID missing from documentation file.
-2   Program segmentation faults at any time.
-10  Code doesn't compile.

Total

In the above example six of the tests failed and it lists -1 for those tests.

If there is a problem running the marking program then you may need to test
each program by hand. This means you will need to convert the .cc file to
a .c file, compile the .c file, and then you can try to run the mark.py again.
This would look something like this:
	./a1 test1.cc
	gcc test1.c -o test1
and you will need to do this for each of the 10 test*.cc files.
You can test the output of each program individually by running the
program and examining it's return value. Programs that run successfully
should return 0. Ones that don't work should return a value greater than 0.
For example, this is what it looks like to run test1, then print the
return value to the screen using echo. The zero in the example is
the value returned by echo.  
	./test1
	echo $?
	0
If it looked like this:
	./test1
	echo $?
	136
then the test1 program didn't work correctly.


7. The two sections after the test cases list other deductions that will be
applied if they are appropriate.  These are mostly things that people
sometimes forget about. These deductions are not negotiable. 

Since there are 225 people in the class it wastes a lot of time if the
assignments are not submitted correctly. If these things don’t apply the
they will be deleted from the file. If they do apply then they will be left
in and the deductions will count towards the final grade for the assignment.


