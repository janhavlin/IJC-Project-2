// htab_clear.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce zrusi vsechny zaznamy vcetne tabulky

#include "htab.h"

void htab_clear(htab_t *t)
{
	for (unsigned i = 0; i < htab_bucket_count(t); i++)
	{
		while(t->ptr[i] != NULL)
		{
		struct htab_listitem *tmp = t->ptr[i];
			while(42)
			{
				// jediny zaznam
				if (tmp->next == NULL)
				{
					t->size--;
					free(tmp->key);
					tmp->key = NULL;
					free(tmp);
					t->ptr[i] = NULL;
					break;
				}
				
				// nasledujici zaznam je posledni
				else if (tmp->next->next == NULL)
				{
					t->size--;
					free(tmp->next->key);
					tmp->next->key = NULL;
					free(tmp->next);
					tmp->next = NULL;
					break;
				}
				
				// presun na nasledujici prvek
				else
				{
					tmp = tmp->next;
				}
			}
		}
	}
}
