// htab_lookup_add.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Hashovaci funkce

#include "htab.h"
#include <stdio.h>

struct htab_listitem *htab_lookup_add(htab_t *t, const char *key)
{
	unsigned hash = htab_hash_function(key) % t->arr_size;

	// Hledani, jestli existuje prvek se stejnym klicem
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

	// Pridavani noveho prvku
	struct htab_listitem *new = (struct htab_listitem *) malloc(sizeof(struct htab_listitem));
	
	if (new == NULL)
	{
		fprintf(stderr, "Chyba pri alokaci zaznamu\n");
		return NULL;
	}
	
	new->key = NULL;
	new->key = malloc(sizeof(char) * (strlen(key) + 1));
	
	if (new->key == NULL)
	{
		free(new);
		return NULL;
	}
	
	strcpy(new->key, key);
	new->data = 1;
	new->next = NULL;
	
	// Zaznam se prida na zacatek, pokud je pole prazdne
	if (t->ptr[hash] == NULL)
		t->ptr[hash] = new;
	
	// Pokud neni pole prazdne, tmp ukazuje na posledni zaznam, ulozime ho za tmp
	else if (tmp->next == NULL)
		tmp->next = new;
	
	t->size++;
	return new;
}
