#!/usr/bin/python3

######################################################
#Christian Cornelis        ccorneli@mail.uoguelph.ca
#CIS*2750                  ID# 0939357
#March 19th, 2017          Assignment 3
######################################################

import sys
import os
import curses

#function to update the number of posts read in a stream file
def updatePostsRead(path, name, postsRead):
    if (os.path.isfile(path)):
        with open(path) as f:
            streamUsers = f.readlines()
        nameToCompare = " "
        newList = []
        for i in streamUsers:
            tokens = i.split(" ")
            nameToCompare = ""
            for j in range(0, len(tokens)-1):
                nameToCompare += " "
                nameToCompare += tokens[j]
            nameToCompare = nameToCompare.strip()
            if (nameToCompare == name):
                read = str(postsRead)
                toAdd = name + " " + read + "\n"
                newList.append(toAdd)
            else:
                newList.append(i)
        f = open(path, "w")
        for i in newList:
            f.write(i)
        f.close()
    else:
        print("Error: File not found.\nExitting")
    return;

#function that runs curses in order to be called multiple times with different streams if the user chooses to switch streams
def getAll(username, streams):
    toReturn = []
    for i in streams:
        #print(i)
        stream = str(i)
        string = "messages/" + stream + "StreamData"
        with open(string) as f:
            bytesList = f.readlines()
        if (len(bytesList) == 0):
            continue
		#stripping spaces at beginning and end of string
        bytesList = [i.strip() for i in bytesList]
        #print(str(bytesList))
        streamStr = "messages/" +stream + "Stream"
        dataFptr = open(streamStr, "r")


        bytesListCnt = 0
        toAdd = ""
        lines = []
        a = 0
		#for i in range (0, )
		#printing post with correct formatting
        #print("UPPER BOUND")
        #print(str(bytesList[len(bytesList)-1]))
        for j in range(0, (int(bytesList[len(bytesList)-1])+1)):
            c = dataFptr.read(1)

            if (c == '\n'):
                toAdd+="<br>"
                lines.append(toAdd)
                toAdd = ""
            else:
                toAdd += c
            #print("J is " + str(j) + "BYTES[BYTESCNT] is " + str(bytesList[bytesListCnt]))
            if (j == int(bytesList[bytesListCnt])):
                bytesListCnt+= 1
                toReturn.append(lines)
                lines = []
                #print("BYTESLISTCNT IS " + str(bytesListCnt))
            a = j
        #print("CNT IS " + str(a))
        #print("TO RETURN")
        #print(toReturn)
        dataFptr.close()
    toReturn.sort(key=lambda x:x[2])
    #print (toReturn)
    #print(len(toReturn))
    return toReturn

#function that prints out a post based on offset and the point that a user has read up to
def printPost(username, stream, postOffset):
	string = "messages/" + stream + "StreamData"
	with open(string) as f:
		bytesList = f.readlines()
	if (len(bytesList) == 0):
		print("Error: No posts to display")
		sys.exit()
	#stripping spaces at beginning and end of string
	bytesList = [i.strip() for i in bytesList]
	streamStr = "messages/" +stream + "Stream"
	dataFptr = open(streamStr, "r")

	streamUsers = []
	userFile = "messages/" + stream + "StreamUsers"
	with open(userFile) as f:
		streamUsers = f.readlines()
	streamUsers = [i.strip() for i in streamUsers]
	nameToCompare = ""
	toStart = -1

	#getting the index that the messages should start to display at based on
	#what messages the user has read
	for a in streamUsers:
		tokens = ""
		tokens = a.split(" ")
		nameToCompare = ""
		for j in range(0, len(tokens)-1):
			nameToCompare += " "
			nameToCompare += tokens[j]
		nameToCompare = nameToCompare.strip()
		if (nameToCompare and nameToCompare == username):
			toStart = int(tokens[(len(tokens)-1)])
	initToStart = toStart
	toStart -= 1
	#printing for the PHP to see that the first post will be outputted
	if ((toStart+postOffset) <= 0):
		print("*AT BEGINNING*")
	if ((toStart + postOffset) >= 0):
		toStart = toStart+postOffset
	if (toStart == int(len(bytesList))):
		toStart = toStart-1
	elif (toStart < len(bytesList)-1 and postOffset is 0):
		toStart += 1
	#printing data from <stream>Stream file
	offset = 0
	if(toStart == 0):
		dataFptr.seek(0, 0)
	else:
		offset = 0
		#using seek to offset where the posts are in the file
		for k in range(0, toStart):
			offset = int(bytesList[k])
		dataFptr.seek(offset, 0)
	#postPtr = open("postData", "w")
	endInd = 0
	if (offset is not 0):
		endInd = int(bytesList[toStart])-offset
	else:
		endInd = int(bytesList[0])

	#printing post with correct formatting
	for j in range(0, endInd):
		c = dataFptr.read(1)
		if (c == '\n'):
			print("<br>")
		else:
			print(c, end="")
		#postPtr.write(c)
	#postPtr.close()
	if (initToStart is not len(bytesList)):
		updatePostsRead(userFile, username, toStart+1)
	dataFptr.close()
	return

#function to return all streams that a user is subscribed to
def getStreams(username):
	userStreams = []
	#if the messages folder and the file needed exists
	if (os.path.isdir("messages")):
		if (os.path.isfile('messages/streamList') == True):
			with open('messages/streamList') as f:
				streams = f.readlines()

			streams = [i.strip() for i in streams]

			for i in streams:
				stream = "messages/"
				stream += i
				stream += "StreamUsers"

				#check in all streamUsers files to find which streams the user has access to
				with open(stream) as fptr:
					users = fptr.readlines();

				for j in users:
					tokens = []
					tokens = j.split(" ")
					tokens = tokens[:-1]
					toCompare = ""
					for k in tokens:
						toCompare += k
						toCompare+= " "

					toCompare = toCompare.strip()
					if (toCompare and username == toCompare):
						userStreams.append(i)

			#if userStreams is empty
			if not userStreams:
				print("Error: This user has access to no streams currently. Use the addauthor program to add a user to a stream.")
				sys.exit()
	            #print("all")
		else:
			print("Error: No streams are present.")
			exit()

	else:
		print("Error: No streams are present.")
		sys.exit()
	return userStreams

def markAllAsRead(stream, username):
	string = "messages/" + stream + "StreamData"
	with open(string) as f:
		bytesList = f.readlines()
	if (len(bytesList) == 0):
		print("Error: No posts are present.")
		sys.exit()
	userFile = "messages/" + stream + "StreamUsers"
	updatePostsRead(userFile, username, len(bytesList))

stream = sys.argv[1]
username = sys.argv[2]
postOffset = int(sys.argv[3])

#if getting all streams a user can access
if (stream == "*OUTPUT*"):
	userStreams = getStreams(username)
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
