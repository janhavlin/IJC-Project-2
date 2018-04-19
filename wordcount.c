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

void print(const char *key, struct htab_listitem *item)
{
	printf("%s\t%d\n", key, item->data);
}

void printTable(htab_t *table)
{
	puts("********* Vypis tabulky *********:");
	struct htab_listitem *list = NULL;
	for(unsigned int i = 0; i < table->arr_size; i++){
		list = table->ptr[i];

		printf("[%d]", i);
		while(list != NULL){
			printf("-[%s]", list->key);
			list = list->next;
		}
		
		printf("-|\n\n");		
	}
}
int main(int argc, char *argv[])
{
	htab_t *table = htab_init(512);
	
	if (argc < 2)
	{
		fprintf(stderr, "Chyba: Nebyl zadan vstupni soubor\n");
		return 1;
	}
	
	FILE *f = fopen(argv[1], "r");	
	if (f == NULL)
	{
		fprintf(stderr, "Chyba pri otevirani souboru\n");
		return 1;
	}
	char word[KEY_MAX_LEN];
	
	short warnings = 1;
	int word_len;
	while((word_len = get_word(word, KEY_MAX_LEN, f)) != EOF)
	{
		if (word_len > KEY_MAX_LEN && warnings--)
		{
			fprintf(stderr, "Varovani: Zkraceno prilis dlouhe slovo\n"); 
		}
		if (htab_lookup_add(table, word) == NULL)
		{
			return 1;
		}
	}
	
	// Pouziti funkce htab_move a nasledne vypsani nove tabulky pomoci htab_foreach
	htab_t *table2 = htab_move(256, table);
	if (table2 == NULL)
	{
		return 1;
	}
	htab_foreach(table2, &print);
	
	htab_free(table);
	htab_free(table2);
	
	fclose(f);
		
	return 0;
}
