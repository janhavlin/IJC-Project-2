// htab_bucket_count.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce vrati pocet prvku pole ukazatelu na seznamy

#include "htab.h"

size_t htab_bucket_count(htab_t *t)
{
	return t->arr_size;
}
