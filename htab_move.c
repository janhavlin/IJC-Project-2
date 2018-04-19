// htab_move.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce, ktera vytvori a inicializuje tabulku s daty z tabulky t2, t2 bude prazdna a alokovana

#include "htab.h"

htab_t * htab_move(size_t newsize, htab_t *t2)
{
	htab_t *t = htab_init(newsize);
	
	for (unsigned i = 0; i < t2->arr_size; i++)
	{
		struct htab_listitem *tmp = t2->ptr[i];
		while(tmp != NULL)
		{
			if (htab_lookup_add(t, tmp->key) == NULL)
			{
				return NULL;
			}
			htab_find(t, tmp->key)->data = htab_find(t2, tmp->key)->data;
			tmp = tmp->next;
		}
	}
	htab_clear(t2);
	return t;
}
