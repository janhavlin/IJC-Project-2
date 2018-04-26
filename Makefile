# Makefile
# Reseni IJC-DU2, priklad A), B), 24.4.2018
# Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
# Prelozeno: gcc 6.4.0
# Popis:	make: vytvori programy tail, tail2, wordcount-dynamic
#			make tail: vytvori C program tail
#			make tail2: vytvori C++ program tail2
#			make wordcount: vytvori program wordcount se statickou knihovnou
#			make wordcount-dynamic: vytvori program wordcount-dynamic se sdilenou knihovnou
#									spusteni: LD_LIBRARY_PATH="." ./wordcount-dynamic file


CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
OBJLIB = htab_hash_function.o htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_lookup_add.o htab_find.o htab_foreach.o htab_remove.o htab_clear.o htab_free.o

all: tail tail2 wordcount wordcount-dynamic

# Sestaveni vyslednych programu
tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail

tail2: tail2.cc
	g++ -std=c++11 tail2.cc -o tail2

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o wordcount wordcount.o io.o -L . libhtab.a
	
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.o io.o libhtab.so
	
# Staticka a dynamicka knihovna
libhtab.a: $(OBJLIB)
	ar -rcs libhtab.a $(OBJLIB)
	
libhtab.so:	$(OBJLIB)
	$(CC) $(CFLAGS) -shared -fPIC -o libhtab.so $(OBJLIB)

# Objektove soubory
io.o: io.c
	$(CC) $(CFLAGS) -c io.c
	
wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c wordcount.c

htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS) -fPIC -c htab_hash_function.c

htab_init.o: htab_init.c
	$(CC) $(CFLAGS) -fPIC -c htab_init.c
	
htab_move.o: htab_move.c htab_lookup_add.o htab_find.o htab_clear.o
	$(CC) $(CFLAGS) -fPIC -c htab_move.c

htab_size.o: htab_size.c
	$(CC) $(CFLAGS) -fPIC -c htab_size.c

htab_bucket_count.o: htab_bucket_count.c
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c
	
htab_lookup_add.o: htab_lookup_add.c htab_hash_function.o htab_find.o
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c
	
htab_find.o: htab_find.c htab_hash_function.o
	$(CC) $(CFLAGS) -fPIC -c htab_find.c

htab_foreach.o: htab_foreach.c
	$(CC) $(CFLAGS) -fPIC -c htab_foreach.c

htab_remove.o: htab_remove.c htab_hash_function.o
	$(CC) $(CFLAGS) -fPIC -c htab_remove.c
	
htab_clear.o: htab_clear.c htab_bucket_count.o
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c
	
htab_free.o: htab_free.c htab_clear.o
	$(CC) $(CFLAGS) -fPIC -c htab_free.c
	
clean:
	rm *.o tail tail2 wordcount wordcount-dynamic libhtab.a libhtab.so

zip:
	zip xhavli47.zip *.c *.cc *.h Makefile
