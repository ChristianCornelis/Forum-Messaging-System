/***************************************************
Christian Cornelis        ccorneli@mail.uoguelph.ca
CIS*2750                  ID# 0939357
February 19th, 2017       Assignment 2
***************************************************/

COMPILATION
***********

To prepare the entire program, simply type:

make


To clean all executables, the stream library, and all .o files from the directory, type:

make clean


EXECUTION:
**********
This entire program should be run on the CIS*2750 web server.\

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
-From the main menu, input a stream name in the text box that matches a name outputted underneath the input box. The streams listed below are all of the streams a user can view.
	-Once a stream is inputted, hit the 'Submit' button to view the stream.


NOTES AND ISSUES:
*****************
-Upon initial login, the messages folder will not be present. It will be automatically created when the user adds themselves to a stream.
	-If the user tries to post to a stream or view a stream that they do not belong to, or if there are no streams in existence yet, appropriate messages will be displayed as this happens.

-Usernames can contain spaces for all programs, but streams CAN NOT

WPML Converter (converter)
-Any text that does not match what a tag is expected to contain WILL NOT be copied, it will be discarded
-My converter prints HTML to stdout, which is echoed by my PHP programs to the screen.
-No PHP is outputted by the converter, as I discussed having my converter only output HTML and he said this was fine. I can prove this if need be.

Addauthor program:
-Stream names cannot contains spaces or just be a newline
    -Furthermore, the user cannot enter spaces after the commas when entering multiple stream names, or leave the streams input blank:
        -For example, if the user entered 'cars, trucks' when prompted for streams, an error would occur due to a space being present
        -If the user entered nothing in the streams input, an appropriate error message would be outputted.
        -Correct input would be as follows: 'cars,trucks,vans'

Post program:
-If the user tries to post to a stream that DOES NOT EXIST, then an error message will be outputted telling the user to use the addauthor program before adding to the stream
-If the user tries to post to a stream that they do not have access to, then they will not be able to input any text and an error message will occur.
-Posts can be no longer than 10000 characters in length.

Viewing Program:
-Messages are displayed starting from the most recent unread messaage
-The 'Order Toggle' option does not work.
-If the user selects 'all', then the program will work. However, if they reach the last post, the program will iterate to the FIRST post in order of dates if 'Next' is hit
	-All WILL NOT update the read count for posts
-If a user is removed while they are viewing the program, an appropriate message will be outputted
-If a user has seen all posts in a stream, then the stream will begin viewing from the newest post
-If a user is viewing all streams at once (they've inputted 'all' as the stream), and they select 'Mark all as read', each post in all subscribed streams will be marked as read and the  newest post will be displayed
 
Messages folder:
-The messages folder will be created by my program if necessary.
-Please note, an additional file will be present called 'streamList'. This file is used by the viewing program in order for it to know which streams have been created in order to check which streams a user is subscribed to.

Configuration File:
-The sizes in the image tag cannot be larger than 5 digits in length.
-If multiple input-related tags are on the same line they will be put into the same HTML form
-When using the .e tag, DO NOT include './' in the name of the executable if it is located in the local directory.
	-This is because my program will search for the executable in the local directory, and if it finds it, will concatenate './' onto the front of it and run it.
	-This is not an issue if the executable is located in the user or system bin folders, as it will run fine since the './' is not concatenated onto the executable name

-.i tag
	-It is possible to have multiple inputs inside the same .i tag
	-This will output all of the appropriate input fields inside one form with one submit button
		-To do this, list the name, value, text, and action for each input IN THAT ORDER inside the .i tag.
		-PLEASE NOTE that ONLY the first instance of action will be used as the action for the form, any other instances of 'action="<>"' will be ignored
		-Example: .i(name="streamInput",value="Overwatch",text="Stream", action="post.php",name="testInput",value="This is a test",text="Stream")
	-It is possible to make an input field a text area by including textArea="True" after the 'text = "<>"' part of an i tag
		-Example: .i(name="streamInput",value="Overwatch",text="Stream", textArea="True", action="post.php",name="testInput",value="This is a test",text="Stream",action="sees.php")
		 would output a text area followed by a normal text input, followed by a submit button

-.q tag
	-This tag was made to keep track of variables between web pages
	-It creates a hidden input field with a static piece of text inside it that is replaced upon printing it out to the screen
	-It takes in a name and text input
	-Example: .q(name="username",value="ENTER USERNAME HERE") would create a hidden input field called username with ENTER USERNAME HERE as the text
		-My PHP programs will find these lines and replace the static strings with their appropriate values, which are passed between the web pages.

-.r tag
	-To have multiple radio buttons inside a list of radio buttons, simply list multiple values inside the tag. This will produce  a multiple radio buttons inside the same form
	-Example: .r(action="addAuthor.php",name="isRemovable",value="Add",value="Remove") would produce 2 radio buttons, 'Add', and 'Remove'
	-The first value listed will be selected by default.

