// wordcount.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Nacteni slov ze vstupniho souboru a vypsani jejich cetnosti

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "htab.h"
#include "io.h"

void print(const char *key, unsigned data)
{
	printf("%s\t%d\n", key, data);
}

int main(int argc, char *argv[])
{
	// Idealni velikost hashovaci tabulky je takova, aby mel 1 bucket max. 1 zaznam, tudiz aby vyhledavani bylo O(1)
	// Velikost tabulky tedy zavisi na velikosti nacitaneho souboru, pokud nevime, jak velky je soubor je lepsi plytvat pameti nez vypocetnim casem procesoru
	// Pokud je velikost tabulky prvocislo, pro nektere hashovaci funkce se snizi sance na shlukovani
	htab_t *table = htab_init(14741);
		
	FILE *f = NULL;
	if (argc >= 2)
		f = fopen(argv[1], "r");
		
	if (f == NULL)
		f = stdin;

	char word[KEY_MAX_LEN];
	
	short warnings = 1;
	int word_len;
	
	while((word_len = get_word(word, KEY_MAX_LEN, f)) != EOF)
	{
		// get_word vraci skutecnou delku slova (ne oriznutou), pokud je tedy vetsi nez maximum, vypiseme varovani
		if (word_len > KEY_MAX_LEN && warnings--)
			fprintf(stderr, "Varovani: Zkraceno prilis dlouhe slovo\n"); 

		if (htab_lookup_add(table, word) == NULL)
		{
			htab_free(table);
			return 1;
		}
	}
	
	// Pouziti funkce htab_move a nasledne vypsani nove tabulky pomoci htab_foreach
	htab_t *table2 = htab_move(5741, table);
	if (table2 == NULL)
	{
		htab_free(table);
		htab_free(table2);
		return 1;
	}
	
	htab_foreach(table2, &print);
	
	htab_free(table);
	htab_free(table2);
	
	fclose(f);
		
	return 0;
}
