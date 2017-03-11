######################################################
#Christian Cornelis        ccorneli@mail.uoguelph.ca
#CIS*2750                  ID# 0939357
#February 19th, 2017       Assignment 2
######################################################

all: a1 addAuthor post.c post

a1: parser.c helperFunctions.c helperFunctions.h
	gcc -Wall -ansi parser.c helperFunctions.c -g -o a1

addAuthor: addAuthor.o libstream.a helperFunctions.c
	gcc addAuthor.o helperFunctions.c -o addauthor -lstream -L.

libstream.a: stream.c stream.h helperFunctions.h
	gcc -Wall -ansi -c stream.c -o stream.o; \
	ar cr libstream.a stream.o

addAuthor.o: addAuthor.c helperFunctions.h stream.h
	gcc -Wall -ansi -c addAuthor.c -o addAuthor.o

post.c: a1 post.cc
	./a1 post.cc

post: post.o helperFunctions.h stream.h
	gcc -Wall -ansi post.o helperFunctions.c -g -o post -lstream -L.

post.o: post.c helperFunctions.h stream.h
	gcc -Wall -ansi -c post.c -g -o post.o

view: view.py
	chmod +x view.py

config: configConverter.c
	gcc  -Wall -ansi configConverter.c -o converter
clean:
	rm *.o libstream.a addauthor post a1 post.c
