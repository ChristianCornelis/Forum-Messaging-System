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
	userStreams.append("all")
	for i in userStreams:
		print (i + " ", end="")
	print("")
#else if viewing all streams
elif (stream == 'all' and postOffset != 98765432109):
    #print("IN HERE")
    streams = getStreams(username)
    posts = getAll(username, streams)
    if (postOffset <= -1):
        postOffset = 0;
        print("*AT ALL BEGNINNING*")
    if (postOffset > len(posts)-1):
        postOffset = len(posts)-1
        print("*AT ALL END*")
    for i in posts[postOffset]:
        print(i,end="")
#else if viewing all and marking all as read
elif(stream == 'all' and postOffset == 98765432109):
	streams = getStreams(username)
	posts = getAll(username, streams)
	for i in streams:
		markAllAsRead(i, username)
	postOffset = 0
	print("*AT ALL END*")
	for i in posts[postOffset]:
		print(i,end="")
#else if viewing a normal stream and marking all as read
elif (postOffset == 3141592654):
	markAllAsRead(stream, username)
	if (postOffset > 0):
		postOffset = 0
		print("*AT END*")

	userStreams = getStreams(username)
	found = False
	for i in userStreams:
		if (stream == i):
			found = True
	#if the user doesn't have access to the stream, or the stream does not exist
	if (not found):
		print("Error: The user does not have access to the " + stream + " stream, or the stream does not exist.")
		sys.exit()
	printPost(username, stream, postOffset)
	#else, just print the post relative to the offset
else:
	if (postOffset > 0):
		postOffset = 0
		print("*AT END*")
	print ("USERNAME IS " + username)
	process = subprocess.check_output(['./db' , 'view', username, stream, str(postOffset)])
	print(process)
