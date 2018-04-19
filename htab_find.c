// htab_find.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce, ktera vyhleda v tabulce zaznam dle zadaneho klice, pokud neexistuje, vraci NULL

#include "htab.h"

struct htab_listitem * htab_find(htab_t *t, const char *key)
{
	unsigned hash = htab_hash_function(key) % t->arr_size;
	
	struct htab_listitem *tmp = t->ptr[hash];
	while(tmp != NULL)
	{
		if (!strcmp(tmp->key, key))
			return tmp;
		
		if (tmp->next != NULL)
			tmp = tmp->next;
		
		else
			break;
	}
	return NULL;
}
