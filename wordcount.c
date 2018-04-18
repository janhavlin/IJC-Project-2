// ./wordcount- <input-book | grep -E "(our)"

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
int main()
{

	int c;
	htab_t *table = htab_init(10);

	while(42)
	{
		char tmp_word[KEY_MAX_LEN];
		int i = 0;
		
		while((c = getchar()) != EOF && i < KEY_MAX_LEN - 1 && !isspace(c))
		{
			// printf("chachar: --%c--", c);
			tmp_word[i++] = c;
		}
	
		// Vubec nebudeme vyhledavat, pokud se nenasel ani jeden znak
		if (isspace(c) && i == 0) continue;
		if (c == EOF && i == 0) break;
		
		tmp_word[i] = '\0';
		
		if (c == EOF) break;
	}
	
	htab_t *table2 = htab_move(5, table);
	htab_foreach(table2, &print);

	htab_free(table);
	htab_free(table2);
	return 0;
}