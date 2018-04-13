#include <stdio.h>
#include "htab.h"



// htab_t * htab_init(int size)
// {
	// htab_t *t = malloc(sizeof(htab_t));
	// t->size = 0;
	// t->arr_size = 1;
	// t->ptr[0] = NULL;
	// return t;
// }

size_t htab_size(htab_t *t)
{
	return t->size;
}

size_t htab_bucket_count(htab_t *t)
{
	// printf("returning arr_size %d\n", t->arr_size);
	return t->arr_size;
}

struct htab_listitem *htab_lookup_add(htab_t *t, const char *key)
{
	struct htab_listitem *tmp = t->ptr[0];
	for (int i = 0; i < t->size; i++)
	{
		if (!strcmp(tmp->key, key))
			return tmp;
		
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
	
	struct htab_listitem *new = (struct htab_listitem *) malloc(sizeof(struct htab_listitem));
	if (new == NULL)
		fprintf(stderr, "Chyba pri alokaci zaznamu\n");

	// puts("Adding a new item");
	strcpy(new->key, key);
	new->data = 0;
	new->next = NULL;
	
	// printf("Size: %d\n", t->size);

	if (t->size == 0)
		t->ptr[0] = new;
	
	
	else if (tmp->next == NULL)
	{
		// printf("Yes, tmp NEXT is NULL, adding a new item with key %s\n", key);
		tmp->next = new;
	}
	
	t->size++;
	return new;
}

void htab_clear(htab_t *t)
{
	for (int i = 0; i < htab_bucket_count(t); i++)
	{
		while(t->ptr[i] != NULL)
		{
		struct htab_listitem *tmp = t->ptr[i];
		struct htab_listitem *tmp_prev = tmp;
			
			while(tmp != NULL)
			{
				
				if (tmp->next != NULL)
				{
					tmp_prev = tmp;
					tmp = tmp->next;
				}
				
				else
				{
					t->size--;
					// printf("FREEING %d -- ", t->size);
					tmp_prev->next = NULL;
					free(tmp);
					
					if (t->size == 0)
						t->ptr[i] = NULL;
					break;
				}
			}
		}
	}
}

void htab_free(htab_t *t)
{
	htab_clear(t);
	free(t);
}