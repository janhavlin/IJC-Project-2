CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
OBJLIB = htab_hash_function.o htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_lookup_add.o htab_find.o htab_remove.o htab_clear.o htab_free.o

tail: tail.c
	$(CC) $(CFLAGS) tail.c

wordcount: wordcount.o libtab.a
	$(CC) $(CFLAGS) -static wordcount.o libtab.a -o wordcount
	

	
# htab.o: htab.c
	# $(CC) $(CFLAGS) -c htab.c

all:
	gcc -std=c99 -Wall -Wextra -pedantic -g tail.c -o tail
	g++ -std=c++11 -pedantic -Wall wordcount-.cc -o wordcount-


	
# Staticka a dynamicka knihovna
libtab.a: $(OBJLIB)
	ar crs libtab.a $(OBJLIB)
	
libtab.so:	
	$(CC) $(CFLAGS) -shared -fPIC -o libtab.so $(OBJLIB)

# Objektove soubory
wordcount.o: htab.o wordcount.c
	$(CC) $(CFLAGS) -fPIC -c wordcount.c	

htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS) -fPIC -c htab_hash_function.c

htab_init.o: htab_init.c
	$(CC) $(CFLAGS) -fPIC -c htab_init.c
	
htab_move.o: htab_move.c
	$(CC) $(CFLAGS) -fPIC -c htab_move.c

htab_size.o: htab_size.c
	$(CC) $(CFLAGS) -fPIC -c htab_size.c

htab_bucket_count.o: htab_bucket_count.c
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c
	
htab_lookup_add.o: htab_lookup_add.c htab_hash_function.o
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c
	
htab_find.o: htab_find.c htab_hash_function.o
	$(CC) $(CFLAGS) -fPIC -c htab_find.c
	
htab_remove.o: htab_remove.c htab_hash_function.o
	$(CC) $(CFLAGS) -fPIC -c htab_remove.c
	
htab_clear.o: htab_clear.c
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c
	
htab_free.o: htab_free.c
	$(CC) $(CFLAGS) -fPIC -c htab_free.c
	
clean:
	rm *.o tail wordcount libtab.a libtab.so
