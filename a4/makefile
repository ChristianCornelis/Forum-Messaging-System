######################################################
#Christian Cornelis        ccorneli@mail.uoguelph.ca
#CIS*2750                  ID# 0939357
#March 19th, 2017          Assignment 3
######################################################

all: a1 addAuthor post.c post converter view db

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

converter: configConverter.c
	gcc  -Wall -ansi -g configConverter.c -o converter
clean:
	rm *.o libstream.a addauthor post converter a1 post.c test.tar
cleanStreams:
	rm messages -r

test:
	sudo php -S localhost:81

ssh:
	ssh ccorneli@2750web.socs.uoguelph.ca

tar:
	tar cf test.tar *.php *.py *.c *.cc *.txt *.wpml *.h makefile

scp:
	scp *.php *.py *.c *.cc *.txt *.wpml *.h makefile ccorneli@2750web.socs.uoguelph.ca:/srv/www/ccorneli
db: db.o
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

db.o: db.c db.h
	gcc -Wall -ansi -g db.c -o db.o -c
