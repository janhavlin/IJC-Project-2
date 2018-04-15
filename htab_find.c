#include "htab.h"

struct htab_listitem * htab_find(htab_t *t,char *key)
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
