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
					free(tmp);
					t->ptr[i] = NULL;
					break;
				}
				
				// nasledujici zaznam je posledni
				else if (tmp->next->next == NULL)
				{
					t->size--;
					free(tmp->next);
					tmp->next = NULL;
					break;
				}
				
				// presun na nasledujici prvek zaznam
				else
				{
					tmp = tmp->next;
				}
			}
		}
	}
}
