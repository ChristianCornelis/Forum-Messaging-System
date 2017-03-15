#!/usr/bin/python3

######################################################
#Christian Cornelis        ccorneli@mail.uoguelph.ca
#CIS*2750                  ID# 0939357
#February 19th, 2017       Assignment 2
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
def printPost(username, stream):
    string = "messages/" + stream + "StreamData"
    with open(string) as f:
        bytesList = f.readlines()

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
    if (toStart == len(bytesList)):
        toStart = 0
    elif (toStart == 0):
        toStart = 1

    print("START " + str(toStart))
    #printing data from <stream>Stream file

    if(toStart == 0):
        dataFptr.seek(0, 0)
    else:
        offset = 0
        #using seek to offset where the posts are in the file
        for k in range(0, toStart):
            offset += int(bytesList[k])
        dataFptr.seek(offset, 0)
        print("OFFSET " + str(offset))
    #printing post with correct formatting
    for j in range(0, int(bytesList[toStart])):
        c = dataFptr.read(1)
        print(c, end="")
    if (initToStart is not len(bytesList)):
        updatePostsRead(userFile, username, toStart+1)
    dataFptr.close()
    return

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

			#for i in userStreams:
				#print (i.strip(), " ", end ="")

			#if userStreams is empty
			if not userStreams:
				print("Error: This user has access to no streams currently. Use the addauthor program to add a user to a stream.")
				exit()
			else:
				userStreams.append("all")
	            #print("all")
		else:
			print("Error: No streams are present.")
			exit()

	else:
		print("Error: No streams are present.")
		exit()
	return userStreams
stream = sys.argv[1]
username = sys.argv[2]
postOffset = sys.argv[3]
if (stream == "*OUTPUT*"):
	userStreams = getStreams(username)
	for i in userStreams:
		print (i + " ", end="")
	print("")

else:
    userStreams = getStreams(username)
    if (stream != 'all'):
        found = False
        for i in userStreams:
            if (stream == i):
                found = True
        #if the user doesn't have access to the stream, or the stream does not exist
        if (not found):
            print("Error: The user does not have access to the " + stream + " stream, or the stream does not exist.")
            exit()
        printPost(username, stream)
    else:
        print("Error: All selected, however, this feature was not implemented due to starting the view program too late : )")
        print("Exitting")
        exit()
