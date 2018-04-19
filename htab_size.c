// htab_size.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce, ktera vrati pocet prvku tabulky

#include "htab.h"

size_t htab_size(htab_t *t)
{
	return t->size;
}
