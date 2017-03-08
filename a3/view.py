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
def runCurses(streamList, stream, username):
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
    for i in streamUsers:
        tokens = i.split(" ")
        nameToCompare = ""
        for j in range(0, len(tokens)-1):
            nameToCompare += " "
            nameToCompare += tokens[j]
        nameToCompare = nameToCompare.strip()
        if (nameToCompare and nameToCompare == username):
            toStart = int(tokens[len(tokens)-1])

    #init curses
    screen = curses.initscr()
    curses.noecho()
    curses.cbreak()
    screen.keypad(1)
    event = 0
    pad = curses.newpad(10000, 80)
    padPos = 0
    pad.refresh(padPos, 0, 0, 0, 23, 80)
    screemFullOffset = 0

    x = 0
    y = 0
    postLines = []

    #printing data from <stream>Stream file
    for i in range (0, len(bytesList)):
        if(i == 0):
            dataFptr.seek(0, 0)
        else:
            offset = 0
            #using seek to offset where the posts are in the file
            for k in range(0, i):
                offset += int(bytesList[k])
            dataFptr.seek(offset, 0)
        postLines.append(y)
        #printing post with correct formatting
        for j in range(0, int(bytesList[i])):
            c = dataFptr.read(1)
            pad.addch(y, x, c)
            pad.refresh(padPos, 0, 0, 0, 23, 80)
            if c == '\n':
                y += 1
                x = 0
            else:
                x += 1
            pad.refresh(padPos, 0, 0, 0, 23, 80)
        y+= 1
        x = 0
        pad.addstr(y, x, "--------------------------------------------------------------------------------")
        y+= 1
        x = 0
        pad.refresh(padPos, 0, 0, 0, 23, 80)
    dataFptr.close()

    screen.refresh()

    #setting the start position for the pad
    if (toStart >= len(postLines) or toStart == -1):
        padPos = 0
    else:
        padPos = postLines[toStart]
    pos = padPos + 23
    numRead = 0
    if (toStart < len(postLines) and pos > postLines[toStart]):
        for i in postLines:
            if pos >= int(i):
                numRead += 1
        #if the user will have seen an unread post upon initting the screen, update what has been read
        if numRead > toStart:
            updatePostsRead(userFile, username, numRead)

    #while input != q OR s
    while(event != 113 and event != 115):
        screen.refresh()
        #printing menu
        pad.refresh(padPos, 0, 0, 0, 23, 80)
        screen.addstr(23, 0, "Up-pg up  Down-pg down  O-order toggle  M-mark all  S-stream  C-check for new  ")
        screen.refresh()
        #if user presses the up arrow key
        if event == curses.KEY_UP:
            if padPos > 0:
                padPos -= 23
                pad.refresh(padPos, 0, 0, 0, 23, 80)
                screen.addstr(23, 0, "Up-pg up  Down-pg down  O-order toggle  M-mark all  S-stream  C-check for new  ")
        #if the user presses the down arow key
        elif event == curses.KEY_DOWN:
            if padPos < y:
                padPos += 23
                if padPos > y:
                    padPos = y
                pos = padPos + 23
                numRead = 0
                if (toStart < len(postLines) and pos > postLines[toStart]):
                    for i in postLines:
                        if pos >= int(i):
                            numRead += 1

                    if numRead > toStart:
                        updatePostsRead(userFile, username, numRead)
                pad.refresh(padPos, 0, 0, 0, 23, 80)
                screen.addstr(23, 0, "Up-pg up  Down-pg down  O-order toggle  M-mark all  S-stream  C-check for new  ")
        #else if the user presses 'c'
        elif event == 99:
            #getting the position to start the posts at
            userFile = "messages/" + stream + "StreamUsers"
            with open(userFile) as f:
                streamUsers = f.readlines()
            streamUsers = [i.strip() for i in streamUsers]
            nameToCompare = ""
            toStart = -1
            for i in streamUsers:
                nameToCompare = ""
                tokens = i.split(" ")
                for j in range(0, len(tokens)-1):
                    nameToCompare += " "
                    nameToCompare += tokens[j]
                nameToCompare = nameToCompare.strip()
                if (nameToCompare and nameToCompare == username):
                    toStart = int(tokens[len(tokens)-1])
            pad.clear()
            screen.refresh()
            with open(string) as f:
                bytesList = f.readlines()
            #stripping off spacing from each element
            bytesList = [i.strip() for i in bytesList]

            streamStr = "messages/" +stream + "Stream"
            dataFptr = open(streamStr, "r")
            x = 0
            y = 0
            postLines = []
            #printing out the stream using the <stream>StreamData file
            for i in range (0, len(bytesList)):
                if(i == 0):
                    dataFptr.seek(0, 0)
                else:
                    offset = 0
                    for k in range(0, i):
                        offset += int(bytesList[k])
                    dataFptr.seek(offset, 0)
                postLines.append(y)
                for j in range(0, int(bytesList[i])):
                    c = dataFptr.read(1)
                    pad.addch(y, x, c)
                    pad.refresh(padPos, 0, 0, 0, 23, 80)
                    if c == '\n':
                        y += 1
                        x = 0
                    else:
                        x += 1
                    pad.refresh(padPos, 0, 0, 0, 23, 80)
                y+= 1
                x = 0
                pad.addstr(y, x, "--------------------------------------------------------------------------------")
                y+= 1
                x = 0
                pad.refresh(padPos, 0, 0, 0, 23, 80)
            dataFptr.close()
            #determining whether the number of posts seen by the user needs to be updated
            if (toStart >= len(postLines) or toStart == -1):
                padPos = 0
            else:
                padPos = postLines[toStart]
            pos = padPos + 23
            numRead = 0
            if (toStart < len(postLines) and pos > postLines[toStart]):
                for i in postLines:
                    if pos >= int(i):
                        numRead += 1
                #updating the number of posts read
                if numRead > toStart:
                    updatePostsRead(userFile, username, numRead)

            pad.refresh(padPos, 0, 0, 0, 23, 80)
            screen.addstr(23, 0, "Up-pg up  Down-pg down  O-order toggle  M-mark all  S-stream  C-check for new  ")
            screen.refresh()

        #if the user selects 'm', updating all posts to be read
        elif event == 109:
            length = len(postLines)
            updatePostsRead(userFile, username, length)

        event = screen.getch()

    #cleaning up curses
    curses.nocbreak()
    screen.keypad(0)
    curses.echo()
    curses.endwin()

    return event;

#if incorrect number of args
if (len(sys.argv) == 1):
    print("Error: Incorrect number of arguments.\nExitting.")
    exit()
username = ""
#building username
for i in range (1, len(sys.argv)):
    username += (sys.argv[i])
    username += " "

username = username.strip()
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

        for i in userStreams:
            print (i.strip(), " ", end ="")

        if not userStreams:
            print("Error: This user has access to no streams currently. Use the addauthor program to add a user to a stream.\nExitting")
            exit()
        else:
            print("all")
    else:
        print("Error: No streams are present\nExitting.")
        exit()

else:
    print("Error: No streams are present.\nExitting.")
    exit()

stream = ""
stream = input()
if (stream != 'all'):
    found = False
    for i in userStreams:
        if (stream == i):
            found = True
    #if the user doesn't have access to the stream, or the stream does not exist
    if (not found):
        print("Error: The user does not have access to the " + stream + " stream, or the stream does not exist.\nExitting")
        exit()
else:
    print("Error: All selected, however, this feature was not implemented due to starting the view program too late : )")
    print("Exitting")
    exit()

#saving the terminal's current size
rows, columns = os.popen('stty size', 'r').read().split()
#setting size to 80x24
sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows=24, cols=80))

while (runCurses(userStreams, stream, username) != 113):
    print("Select a new stream to choose from:")
    for i in userStreams:
        print (i.strip(), " ", end ="")
    if not userStreams:
        print("Error: This user has access to no streams currently. Use the addauthor program to add a user to a stream.\nExitting")
        exit()
    else:
        print("all")

    stream = ""
    stream = input()
    if (stream != 'all'):
        found = False
        for i in userStreams:
            if (stream == i):
                found = True
        #if the user doesn't have access to the stream, or the stream does not exist
        if (not found):
            print("Error: The user does not have access to the " + stream + " stream, or the stream does not exist.\nExitting")
            exit()
    else:
        print("Error: All selected, however, this feature was not implemented due to starting the view program too late : )")
        print("Exitting")
        exit()

#resetting size of terminal
sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows=rows, cols=columns))