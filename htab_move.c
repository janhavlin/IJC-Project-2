#include "htab.h"

htab_t * htab_move(size_t newsize, htab_t *t2)
{
	htab_t *t = htab_init(newsize);
	
	for (unsigned i = 0; i < t2->arr_size; i++)
	{
		struct htab_listitem *tmp = t2->ptr[i];
		while(tmp != NULL)
		{
			// printf("bla %d\n", i);
			htab_lookup_add(t, tmp->key);

			htab_find(t, tmp->key)->data = htab_find(t2, tmp->key)->data;
			
			tmp = tmp->next;
		}
	}
	htab_clear(t2);
	return t;
}
