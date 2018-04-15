#include "htab.h"

void htab_foreach(htab_t *t, void (* func)(const char *, struct htab_listitem *))
{
	for (unsigned i = 0; i < t->arr_size; i++)
	{
		struct htab_listitem *tmp = t->ptr[i];
		while(tmp != NULL)
		{
			// volat fci nad tmp
			(* func)(tmp->key, tmp);
			tmp = tmp->next;
		}
	}
}
