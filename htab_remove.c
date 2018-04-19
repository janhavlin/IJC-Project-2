// htab_remove.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce, ktera vyhleda a zrusi zadany zaznam

#include "htab.h"

bool htab_remove(htab_t *t, char *key)
{
	unsigned hash = htab_hash_function(key) % t->arr_size;
	
	struct htab_listitem *tmp = t->ptr[hash];
	while(tmp != NULL)
	{
		// nalezena shoda u prvniho zaznamu
		if (!strcmp(tmp->key, key))
		{
			t->ptr[hash] = tmp->next;
			free(tmp);
			t->size--;
			return true;
		}
		
		// nalezena shoda u tmp->next
		else if (tmp->next != NULL && !strcmp(tmp->next->key, key))
		{
			struct htab_listitem *tmp_next = tmp->next->next;
			free(tmp->next);
			tmp->next = tmp_next;
			t->size--;
			return true;
		}
		
		// posun na dalsi prvek (pokud je NULL, neprojde podminka cyklu)
		else
		{
			tmp = tmp->next;
		}
	}
	return false;
}
