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
To add an author to a stream, first login and then navigate to the 'Add/Remove Author' button and press it
To remove a user from a stream, select 'Remove' on the Add author page instead of leaving the default 'Add' option checked
Then, input the streams to add or remove a user to/from after being prompted to
If a user is being added to multiple streams then the streams MUST be separated by commas and contain no spaces between them
	Proper input would look like this: cars,trucks,vans

Post:
To post to a stream, navigate to the 'Post' option from the menu.
Then, imput the stream that you wish to add to and enter the post's text in the textarea.
	Upon finishing typing in the post, click the 'Submit' button to add the post to the stream.
	If the stream does not exist, then an appropriate error message will be outputted.
	If the user is not subscribed to the stream theu are trying to post to an appropriate error message which will be outputted.

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
-If the user tries to post to a stream that DOES NOT EXIST, then an error message will be outputted telling the user to use the addauthor program before adding to the stream\
-If the user tries to post to a stream that they do not have access to, then they will not be able to input any text and an error message will occur.
-Posts can be no longer than 10000 characters in length.

Viewing Program:
-The UP and DOWN arrows are used to scroll throug messages
-Messages are displayed starting from the most recent unread messaage
-The 'O' option does not work.
-Selecting 'all' will not do anything, as I didn't have time to complete it.
-If a user is removed while they are viewing the program, the user will be able to view all messages from the stream that they were removed from
 until the next time the program is run.
-If a user has seen all posts in a stream, then the stream will begin viewing from the newest post
 
Messages folder:
-The messages folder will be created by my program if necessary.
-Please note, an additional file will be present called 'streamList'. This file is used by the viewing program in order for it to know which streams have been created in order to check which streams a user is subscribed to.

Configuration File:
-The sizes in the image tag cannot be larger than 5 digits in length.
-If multiple input-related tags are on the same line
-
