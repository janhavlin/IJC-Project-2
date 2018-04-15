#include "htab.h"

size_t htab_bucket_count(htab_t *t)
{
	return t->arr_size;
}
