// htab_free.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Funkce, ktera zrusi vsechny zaznamy vcetne tabulky

#include "htab.h"

void htab_free(htab_t *t)
{
	htab_clear(t);
	free(t);
}
