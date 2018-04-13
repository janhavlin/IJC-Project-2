// ./wordcount- <input-book | grep -E "(our)"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "htab.h"

void print(const char *key, struct htab_listitem *item)
{
	printf("%s\t%d\n", key, item->data);
}

void printTable(htab_t *table)
{
	struct htab_listitem *list = NULL;
	for(unsigned int i = 0; i < table->arr_size; i++){
		list = table->ptr[i];

		printf("[%d]", i);
		while(list != NULL){
			printf("-[%s]", list->key);
			list = list->next;
		}
		
		printf("-|\n");		
	}
}
int main()
{
	// char word[KEY_MAX_LEN];
	int c;
	htab_t *table = htab_init(10);
	printf("SIZE: %d ARR SIZE: %d\n", table->size, table->arr_size);
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
		// printf("'%s' Volani lookup --\n", tmp_word);
		struct htab_listitem *tmp_item = htab_lookup_add(table, tmp_word);
		// printf("data: %d\n", tmp_item->data);
		
		if (c == EOF) break;
	}
	
	// if(htab_remove(table, "19")) puts("yes");
	// puts("A");
	// if(htab_remove(table, "20")) puts("yes");
	// puts("B");
	// if(htab_remove(table, "18")) puts("yes");
	// puts("C");
	// if(htab_remove(table, "96")) puts("yes");
	// puts("D");
	// if(htab_remove(table, "52")) puts("yes");
	// if(!htab_remove(table, "100")) puts("no");	
	// if(!htab_remove(table, "0")) puts("no");
	
	// for (int i = 0; i < htab_bucket_count(table); i++)
	// {
		// struct htab_listitem *tmp = table->ptr[i];
		// while(tmp != NULL)
		// {
			// printf("arr %d: ", i);
			// printf("%s\t%d\n", tmp->key, tmp->data);
			// tmp = tmp->next;
		// }
	// }
	htab_t *table2 = htab_move(5, table);
	htab_foreach(table2, &print);
	// printTable(table);
	

	// puts("*** VOLANI CLEAR ***");
	// htab_clear(table);
	htab_free(table);
	return 0;
}