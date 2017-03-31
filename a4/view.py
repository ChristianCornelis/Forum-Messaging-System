#!/usr/bin/python3

######################################################
#Christian Cornelis        ccorneli@mail.uoguelph.ca
#CIS*2750                  ID# 0939357
#March 19th, 2017          Assignment 3
######################################################

import sys
import os
import subprocess

stream = sys.argv[1]
username = sys.argv[2]
postOffset = int(sys.argv[3])

#if getting all streams a user can access
if (stream == "*OUTPUT*"):
	subprocess.call(['./db', 'output', username])
#else if viewing all streams
elif (stream == 'all' and postOffset != 98765432109):
	if (postOffset <= -1):
		postOffset = 0;
		print("*AT ALL BEGNINNING*")
	print("OFFSET IS " + str(postOffset))
	subprocess.call(['./db', 'viewAll', 'all', username, str(postOffset)])
#else if viewing all and marking all as read
elif(stream == 'all' and postOffset == 98765432109):
	print("*AT ALL END*")
	postOffset = 0
	subprocess.call(['./db', 'view', username, stream, str(postOffset)])
#else if viewing a normal stream and marking all as read
elif (postOffset == 3141592654):
	if (postOffset >= 0):
		postOffset = 0
		print("*AT END*")

	subprocess.call(['./db' , 'allMarkAll', username, stream])

	
	#else, just print the post relative to the offset
else:
	if (postOffset >= 0):
		postOffset = 0
		print("FINDING THAT YUNG END")
		print("*AT END*")

	process = subprocess.call(['./db', 'view', username, stream, str(postOffset)])

