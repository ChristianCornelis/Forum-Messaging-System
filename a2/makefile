all: a1 addAuthor

a1: parser.c helperFunctions.c helperFunctions.h
	gcc -Wall -ansi parser.c helperFunctions.c -g -o a1
addAuthor: addAuthor.o libstream.a helperFunctions.c
	gcc addAuthor.o helperFunctions.c -o addAuthor -lstream -L.

libstream.a: stream.c stream.h helperFunctions.h
	gcc -Wall -ansi -c stream.c -o stream.o; \
	ar cr libstream.a stream.o

addAuthor.o: addAuthor.c helperFunctions.h stream.h
	gcc -Wall -ansi -c addAuthor.c -o addAuthor.o

clean:
	rm *.o
	
