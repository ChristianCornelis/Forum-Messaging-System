/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
March 19th, 2017          Assignment 3
***************************************************/

COMPILATION
***********

To prepare the entire program, simply type:

make


To clean all executables, the stream library, and all .o files from the directory, type:

make clean


EXECUTION:
**********
This entire program should be run on the CIS*2750 web server.

Login:
Login with a username of your choice at the login screen and hit 'Submit' to move to the main menu.
If a username is a blank string or is just 1 space, it will be replaced with 'Guest User' by default upon entering the main menu.

Add author:
-To add an author to a stream, first login and then navigate to the 'Add/Remove Author' button on the main menu and press it
-To remove a user from a stream, select 'Remove' on the Add author page instead of leaving the default 'Add' option checked
-Then, input the streams to add or remove a user to/from after being prompted to
-If a user is being added to multiple streams then the streams MUST be separated by commas and contain no spaces between them
	-Proper input would look like this: cars,trucks,vans
-If a user is already in the stream they are attempting to be added to, an appropriate message will be displayed.
-If the user cannot be removed from a stream because it does not exist or they are not present in it, an appropriate message will be displayed.S

Post:
-To post to a stream, navigate to the 'Post' option from the menu.
-Then, input the stream that you wish to add to and enter the post's text in the textarea.
	-Upon finishing typing in the post, click the 'Submit' button to add the post to the stream.
	-If the stream does not exist, then an appropriate error message will be outputted.
	-If the user is not subscribed to the stream theu are trying to post to an appropriate error message which will be outputted.

View:
-From the main menu, select the 'View Posts' button
-Next, input a stream from the list of streams that the user is able to access, which is found below the text input
-Once a stream name has been entered, hit submit to go to a viewing page



NOTES AND ISSUES:
*****************
-If the user tries to post to a stream or view a stream that they do not belong to, or if there are no streams in existence yet, appropriate messages will be displayed as this happens.
-On any page, the 'Return' button will take the user to the main menu, and the 'Logout' button will take them to the login screen
-The maximum query length is 10000 characters. 
	-However, an odd limitation is in place for single quotes: If a query contains 2000 single quotes, in can only be 8000 characters in length.
-The table that contains the users, the streams they have access to, and the number of posts they have read may be referred to as either the authors or users table.
-Usernames can contain spaces for all programs, but streams CAN NOT
-Both usernames and streams CAN NOT contain single quotes (apostrophes)
-If a post contains an apostrophe it will be sanitized so that it does not cause a mySQL error
-To include a double quote (") in a post, you MUST put the '\', or escape, character before it when typing or it will cause an error.
-Double quotes CAN NOT BE in stream or user names.
-If a mySQL error is ever thrown when querying, a meaningful message will be printed out along with the actual mySQL error message.

Addauthor program:
-Stream names cannot contains spaces or just be a newline, or include a comma
    -Furthermore, the user cannot enter spaces after the commas when entering multiple stream names, or leave the streams input blank:
        -For example, if the user entered 'cars, trucks' when prompted for streams, an error would occur due to a space being present
        -If the user entered nothing in the streams input, an appropriate error message would be outputted.
        -Correct input would be as follows: 'cars,trucks,vans'
    -If the users table does not exist, and the user tries to remove themselves from a stream, an error message will be outputted that will contain an error from mySQL as well

Post program:
-If the user tries to post to a stream that DOES NOT EXIST, then an error message will be outputted telling the user to use the addauthor program before adding to the stream
-If the user tries to post to a stream that they do not have access to, then they will not be able to input any text and an error message will occur.
-Posts can be no longer than 10000 characters in length.
-A post cannot contain a double quote. Could not figure out a way that this would get passed into my database program, since I was wrapping the text argument in quotes so that it would be recognized as one signle argument

Viewing Program:
-Messages are displayed starting from the most recent unread messaage
-If the posts and or users tables do not exist
-The 'Order Toggle' option does not work and will do nothing.
-All WILL NOT update the read count for posts
	-If a user hits 'Check for new posts' while viewing all streams then the oldest post will be displayed. Since all doesn't keep track of how many posts a user has read I thought that this was an appropriate way to handle it
	-If a user hits 'Mark all as read' while viewing all streams then all posts will be marked for all streams that a user is subcribed to, and the oldest post will be displayed, since it would have been very difficult to keep track of the number of posts that the offset would have been set to for what post to view
-If a user is removed while they are viewing the program, an appropriate message will be outputted
-If a user has seen all posts in a stream, then the stream will begin viewing from the newest post
-The 'Return to main menu' button will take you to the main menu, and the 'Switch streams' button will return you to the view menu

Database Program Flags:

To use these flags, run (from the command line) ./db <FLAG>
MAKE SURE TO INCLUDE THE DASH IN FRONT OF THE FLAG NAME PLS
-users
	-This flag will display the contents of the authors table.
	-This includes the author, stream they are subscribed to, and the number of posts that they have read so far in the stream.
	-If the authors table does not exist, then an appropriate message will be printed.
	-The output will be ordered by name.

-posts
	-The author, stream, date, and post content will all be displayed.
	-If there are no posts, or the table does not exist, an appropriate message will be printed that says that there are no posts to display.
	-Posts are printed out in the order of the date

-streams
	-This flag will display all of the streams that are present in the database
	-The streams will be outputted in the order of their names
	-If no streams are present or the streams table is empty, an appropriate message will be printed.

-clear
	-This flag will clear all of the tables present in the database
	-If the tables are already empty, an appropriate message will be outputted
	-If the tables do not exist, the tables will be created, and a message will be outputted saying that they are clear

-reset
	-drops all tables in use if they exist
	-if the table does not exist, it cannot be dropped and an appropriate message will be outputted

-help
	-Outputs information about all previous flags and how to run them