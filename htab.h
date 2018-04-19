// htab.h
// Reseni IJC-DU2, priklad B), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: Definice funkci knihovny pro operace s tabulkou

#ifndef HTAB_H_
#define HTAB_H_

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define KEY_MAX_LEN 128

typedef struct {
	unsigned size;
	unsigned arr_size;
	struct htab_listitem *ptr[];
} htab_t;

struct htab_listitem {
	char *key;
	unsigned data;
	struct htab_listitem *next;
};

/**
 * @brief Hashovaci funkce
 * @param str Vstupni retezec
 * @return Celociselny hash
 */
unsigned int htab_hash_function(const char *str);

/**
 * @brief Konstruktor: vytvori a inicializuje tabulku
 * @param size Velikost pole ukazatelu na seznamy
 * @return Ukazatel na tabulku
 */
htab_t * htab_init(size_t size);

/**
 * @brief Vytvori a inicializuje tabulku s daty z tabulky t2, t2 bude prazdna a alokovana
 * @param size Velikost pole ukazatelu na seznamy
 * @param t2 Puvodni tabulka
 * @return Ukazatel na novou tabulku
 */
htab_t * htab_move(size_t newsize,htab_t *t2);

/**
 * @brief Vrati pocet prvku tabulky
 * @param t Ukazatel na tabulku
 * @return Pocet prvku (zaznamu) v tabulce
 */
size_t htab_size(htab_t *t);

/**
 * @brief Vrati pocet prvku pole ukazatelu na seznamy
 * @param t Ukazatel na tabulku
 * @return Pocet ukazatelu v poli
 */
size_t htab_bucket_count(htab_t *t);

/**
 * @brief Vyhleda v tabulce zaznam dle zadaneho klice, pokud neexistuje, prida zaznam
 * @param t Ukazatel na tabulku
 * @param key Retezec, podle ktereho bude vyhledavat
 * @return Ukazatel na zaznam
 */
struct htab_listitem * htab_lookup_add(htab_t *t,const char *key);

/**
 * @brief Vyhleda v tabulce zaznam dle zadaneho klice, pokud neexistuje, vraci NULL
 * @param t Ukazatel na tabulku
 * @param key Retezec, podle ktereho bude vyhledavat
 * @return Ukazatel na zaznam
 */
struct htab_listitem * htab_find(htab_t *t, const char *key);

/**
 * @brief Vola funkci func pro kazdy zaznam v tabulce
 * @param t Ukazatel na tabulku
 * @param func Ukazatel na funkci s parametry (const char *, struct htab_listitem *)
 */
void htab_foreach(htab_t *t, void (* func)(const char *, struct htab_listitem *));

/**
 * @brief Vyhleda a zrusi zadany zaznam
 * @param t Ukazatel na tabulku
 * @param key Retezec, podle ktereho se bude vyhledavat
 * @return True pokud byl smazan, false pokud neexistuje
 */
bool htab_remove(htab_t *t, char *key);

/**
 * @brief Zrusi vsechny zaznamy, tabulka zustava prazdna
 * @param t Ukazatel na tabulku
 */
void htab_clear(htab_t *t);

/**
 * @brief Zrusi vsechny zaznamy vcetne tabulky
 * @param t Ukazatel na tabulku
 */
void htab_free(htab_t *t);

#endif