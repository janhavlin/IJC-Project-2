// ZASTARALA VERZE //

#include <stdio.h>
#include "htab.h"

unsigned int htab_hash_function(const char *str)
{
	unsigned int h=0;     // 32bit
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
		h = 65599*h + *p;
	return h;
}

htab_t * htab_init(size_t size)
{
	htab_t *t = (htab_t *) malloc(sizeof(htab_t) + sizeof(struct htab_listitem *) * size);
	if (t == NULL)
		return NULL;

	t->size = 0;
	t->arr_size = size;
	for (unsigned i = 0; i < size; i++)
		t->ptr[i] = NULL;
	return t;
}

// TODO
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
	unsigned hash = htab_hash_function(key) % t->arr_size;
	// printf("HASH: %u\n", hash);
	
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

void htab_clear(htab_t *t)
{
	for (unsigned i = 0; i < htab_bucket_count(t); i++)
	{
		// printf("CLEAR ITERACE %d\n", i);
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

void htab_free(htab_t *t)
{
	htab_clear(t);
	free(t);
}