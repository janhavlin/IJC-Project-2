CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

wordcount: wordcount.o
	$(CC) $(CFLAGS) wordcount.o htab.o -o wordcount
	
wordcount.o: htab.o wordcount.c
	$(CC) $(CFLAGS) -c wordcount.c
	
htab.o: htab.c
	$(CC) $(CFLAGS) -c htab.c

all:
	gcc -std=c99 -Wall -Wextra -pedantic -g tail.c -o tail
	g++ -std=c++11 -pedantic -Wall wordcount-.cc -o wordcount-
