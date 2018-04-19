// htab_hash_function.c
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Hashovaci funkce

#include "htab.h"

unsigned int htab_hash_function(const char *str)
{
	unsigned int h=0;     // 32bit
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
		h = 65599*h + *p;
	return h;
}
