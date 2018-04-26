// tail.c
// Reseni IJC-DU2, priklad A), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: C implementace POSIX prikazu tail
//			pro nacitani radku pouzito staticky alokovane 2D pole (kralikarna)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int main(int argc, char *argv[])
{
	long lines = 10;
	FILE *f = NULL;
	
	// tail soubor || tail -n 20 soubor
	if (argc == 2 || argc == 4)
	{
		if ((argc == 4 && !strcmp(argv[1], "-n")))
			lines = strtol(argv[2], NULL, 0);
		else if (argc != 2)
		{
			fprintf(stderr, "Chyba: Pouziti: tail -n CISLO SOUBOR\n");
			return 1;			
		}
		
		f = fopen(argv[argc - 1], "r");
		if (f == NULL)
		{
			fprintf(stderr, "Chyba pri nacitani souboru\n");
			return 1;
		}
	}
	
	// tail -n 20 <soubor
	else if (argc == 3 && !strcmp(argv[1], "-n"))
	{
		lines = strtol(argv[2], NULL, 0);
	}
	
	// tail <soubor
	else if (argc != 1)
	{
		fprintf(stderr, "Chyba: Nespravne zadane argumenty\n");
		return 1;
	}
	
	if (lines == 0)
		return 0;
		
	else if (lines < 0)
	{
		fprintf(stderr, "Chyba: Zadan chybny pocet radku\n");
		return 1;
	}
	
	if (f == NULL)
		f = stdin;
	
	char buffer[lines][MAX_LINE_LEN];
	
	int c;
	long i = 0;
	short warnings = 1;
	while(42)
	{
		int j = 0;
		while ((c = fgetc(f)) != EOF && j < MAX_LINE_LEN - 2)
		{
			// Pomoci modula prepisujeme radek
			buffer[i%lines][j++] = c;

			// Znak konce radku zapiseme a vyskocime z cyklu
			if(c == '\n')
				break;
		}
		
		// Rezervace mista pro '\n' a pro '\0'
		if (j == MAX_LINE_LEN - 2)
		{
			if (warnings--)
				fprintf(stderr, "Varovani: Zkracen prilis dlouhy radek\n");
			while((c = fgetc(f)) != EOF && c != '\n');
			buffer[i%lines][j++] = '\n';
		}
		
		if (c == EOF)
		{
			// Pokud je j 0, znamena to, ze posledni znak souboru je '\n'EOF, i se zvysi o 1, provede se dalsi iterace cyklu a dosteneme se do teto vetve
			// Pokud soubor konci pouze EOF, iterator i ma hodnotu o 1 mensi, protoze mu posledni znak souboru '\n' nezvysi hodnotu,
			// tudiz i zvysime tady, aby byly tyto 2 varianty synchronizovane
			if (j != 0)
				i++;
			break;
		}
		
		buffer[i%lines][j++] = '\0';
		i++;
	}
	
	// i = prvni radek
	// i - lines = prvni radek
	// interval <i-lines, i) = vsechny radky na vypis
	for (long k = i - lines; k < i; k++)
	{
		// Pokud bylo zadano mene radku, nez je v souboru, dostali bychom se do zaporu
		if (k < 0)
			k = 0;
		for (unsigned l = 0; l < strlen(buffer[k%lines]); l++)
			putc(buffer[k%lines][l], stdout);
	}

	return 0;
}
