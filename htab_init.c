// htab_init.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Hashovaci funkce

#include "htab.h"

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
