// htab_foreach.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce, ktera vola funkci pro kazdy zaznam v tabulce

#include "htab.h"

void htab_foreach(htab_t *t, void (* func)(const char *, unsigned))
{
	for (unsigned i = 0; i < t->arr_size; i++)
	{
		struct htab_listitem *tmp = t->ptr[i];
		while(tmp != NULL)
		{
			// Volani funkce s parametrem key a data
			(* func)(tmp->key, tmp->data);
			tmp = tmp->next;
		}
	}
}
