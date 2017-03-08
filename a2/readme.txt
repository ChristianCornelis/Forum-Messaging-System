/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2017       Assignment 2
***************************************************/

COMPILATION
***********

To build the library and to create the executables for addauthor and post, as well as convert post.cc to post.c, type:

make

To compile the view.py file using the makefile, type:

make view

To clean all executables and .o files from the directory, type:

make clean

EXECUTION:
**********

Addauthor:
To run the addauthor program, type ./addauthor <username>
To remove a user from a stream, run ./addauthor <username> -r
Then, input the streams to add or remove a user to/from after being prompted to

Post:
To post to a stream, run ./post <username>
Then, input the stream to post to, and enter the text
Use CTRL+D to exit the input for the text and complete the post

View:
-Run ./view.py <username> and select which stream to view from a list of streams outputted that  the user has access to.
-If a user does not have access to any streams, an error message will be outputted and the       program will exit.

NOTES AND ISSUES:
*****************

-Usernames can contain spaces for all programs, but streams CAN NOT

Addauthor program:
-Stream names cannot contains spaces or just be a newline
    -Furthermore, the user cannot enter spaces after the commas when entering multiple stream names:
        For example, if the user entered 'cars, trucks' when prompted for streams, an error would occur due to a space being present
            Correct input would be as follows: 'cars,trucks,vans'

Post program:
-If the user tries to post to a stream that DOES NOT EXIST, then the stream files will be created BUT no info will be added to them
    -The user is informed of this, and that in order to get permission to post to the stream, they must first use the addauthor program
-If the user tries to post to a stream that they do not have access to, then they will not be able to input any text and an error message will occur.
-Posts can be no longer than 10000 characters in length.

Viewing Program:
-The UP and DOWN arrows are used to scroll throug messages
-Messages are displayed starting from the most recent unread messaage
-If the terminal is in full screen (or half screen), then my program will NOT resize it to be 80 x 24
-The 'O' option does not work.
-Selecting 'all' will not do anything, as I didn't have time to complete it.
-If a user is removed while they are viewing the program, the user will be able to view all messages from the stream that they were removed from
 until the next time the program is run.
-If a user has seen all posts in a stream, then the stream will begin viewing from the oldest post
-Please note: The user can view PAST the pad by 23 lines, if the user pushes the UP arrow, they will return to the messages
 
Messages folder:
-The messages folder will be created by my program if necessary.
-Please note, an additional file will be present called 'streamList'. This file is used by the viewing program in order 
 for it to know which streams have been created in order to check which streams a user is subscribed to.
