// ./wordcount- <book | grep -E "(our)"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "htab.h"

int main()
{
	// char word[KEY_MAX_LEN];
	int c;
	htab_t table = {.size = 0, .arr_size = 1, .ptr[0] = NULL};
	// struct htab_listitem *head = NULL;
	// int size = 0;
	
	// printf("%c %c %c", getchar(), getchar(), getchar());
	// return 0;
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
		// printf("'%s' Volani lookup -- ", tmp_word);
		struct htab_listitem *tmp_item = htab_lookup_add(&table, tmp_word);
		tmp_item->data++;
		// printf("data: %d\n", tmp_item->data);
		
		if (c == EOF) break;
	}
	
	struct htab_listitem *tmp = table.ptr[0];
	for (int i = 0; i < htab_size(&table); i++)
	{
		printf("%s\t%d\n", tmp->key, tmp->data);
		tmp = tmp->next;
	}
	htab_clear(&table);
	// htab_free(&table);
	return 0;
}