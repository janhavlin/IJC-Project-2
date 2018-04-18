#ifndef HTAB_H_
#define HTAB_H_

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define KEY_MAX_LEN 128

typedef struct {
	unsigned size;
	unsigned arr_size;
	struct htab_listitem *ptr[];
} htab_t;

struct htab_listitem {
	char key[128];
	unsigned data;
	struct htab_listitem *next;
};

unsigned int htab_hash_function(const char *str);

htab_t * htab_init(size_t size);	// konstruktor: vytvoření a inicializace tabulky

htab_t * htab_move(size_t newsize,htab_t *t2); // move konstruktor: vytvoření a inicializace tabulky daty z tabulky t2, t2 nakonec zůstane prázdná a alokovaná (tuto funkci cvičně použijte v programu)

size_t htab_size(htab_t *t);		// vrátí počet prvků tabulky (.size)

size_t htab_bucket_count(htab_t *t);   // vrátí počet prvků pole (.arr_size)

struct htab_listitem * htab_lookup_add(htab_t *t,const char *key);    // vyhledávání - viz dále

struct htab_listitem * htab_find(htab_t *t, const char *key);          // vyhledávání - viz dále

void htab_foreach(htab_t *t, void (* func)(const char *, struct htab_listitem *));      // volání funkce func pro každý prvek

bool htab_remove(htab_t *t, char *key);      // vyhledání a zrušení zadané položky vrací b==false pokud neexistuje

void htab_clear(htab_t *t);             // zrušení všech položek, tabulka zůstane prázdná

void htab_free(htab_t *t);              // destruktor: zrušení tabulky (volá htab_clear())

// kde t,t2    je ukazatel na tabulku (typu htab_t *),
// b       je typu bool,
// ptr     je ukazatel na záznam (položku tabulky),
// func    je funkce s parametry: func(constkey,valueptr)
		  

#endif