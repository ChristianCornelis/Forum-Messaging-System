#!/usr/bin/python

import os

if __name__ == "__main__":
	# get the username from the path
   path,filename = os.path.split(os.getcwd())
   print(filename)
   f = open(filename + "-marking.txt", "w")
   f.write("CIS*2750 Assignment 1\n" )
   f.write("Marking Scheme\n" )
   f.write("Marked out of 10.\n\n" )
   f.write("Test Cases\n\n" )

    # use make to build each test file, test1 to test10 and check the
    # output is equal to zero which mean a success
   for i in range(1,11):
      testname = "test" + str(i)
      os.system("make -f make.test " + testname);
      exename = "./test" + str(i)
      ret = os.system(exename)
      if ret == 0:
         f.write("**** Success test " + str(i) + "\n" )
         #print "**** Success test " , i
      else:
         f.write("**** Fail test " + str(i) + "                      ****  -1\n") 
         #print "**** Fail test " , i , "                      ****  -1"


   f.write("\n\nGeneral Assignment Requirements\n")
   f.write("-1  Specification not followed.\n")
   f.write("-1  Poor formatting or variable names in source code.\n\n\n")

   f.write("Submission and Documentation\n")
   f.write("-1   Assignment not submitted correctly -in a subdirectory or named incorrectly.\n")
   f.write("-1   File not submitted as a tar file - submitted as a zip file.\n")
   f.write("-1   Documentation not included, name or ID missing from documentation file.\n")
   f.write("-2   Program segmentation faults at any time.\n")
   f.write("-10  Code doesn't compile.\n\nTotal\n\n")


   f.close()

