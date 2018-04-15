#include "htab.h"
#include <stdio.h>

struct htab_listitem *htab_lookup_add(htab_t *t, const char *key)
{
	unsigned hash = htab_hash_function(key) % t->arr_size;
	
	struct htab_listitem *tmp = t->ptr[hash];
	while(tmp != NULL)
	{
		if (!strcmp(tmp->key, key))
		{
			tmp->data++;
			return tmp;
		}
		
		if (tmp->next != NULL)
			tmp = tmp->next;
		
		else
			break;
	}
	
	struct htab_listitem *new = (struct htab_listitem *) malloc(sizeof(struct htab_listitem));
	if (new == NULL)
	{
		fprintf(stderr, "Chyba pri alokaci zaznamu\n");
		return NULL;
	}

	// puts("Adding a new item");
	strcpy(new->key, key);
	new->data = 1;
	new->next = NULL;
	
	// printf("Size: %d\n", t->size);

	if (t->ptr[hash] == NULL)
		t->ptr[hash] = new;
		
	else if (tmp->next == NULL)
	{
		// printf("Yes, tmp NEXT is NULL, adding a new item with key %s\n", key);
		tmp->next = new;
	}
	
	t->size++;
	return new;
}
