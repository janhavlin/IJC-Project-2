#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"

#define MAX_LINE_LEN 1024

int get_char(FILE *f)
{
	// Cteni ze stdin
	if (f == NULL)
		return getchar();

	// Cteni ze souboru
	else
		return fgetc(f);
}

int main(int argc, char *argv[])
{
	// printf("Hello, %d World!\n", argc);
	int lines = 10;
	FILE *f = NULL;
	
	// tail soubor || tail -n 20 soubor
	if (argc == 2 || argc == 4)
	{
		if ((argc == 4 && !strcmp(argv[1], "-n")))
			lines = atoi(argv[2]);
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
		lines = atoi(argv[2]);
	}
	
	// tail <soubor
	else if (argc != 1)
	{
		fprintf(stderr, "Chyba: Nespravne zadane argumenty\n");
		return 1;
	}
	
	// printf("Lines: %d\n", lines);
	if (lines < 0)
	{
		fprintf(stderr, "Chyba: Zadany pocet radku nesmi byt zaporny\n");
		return 1;
	}
	
	char buffer[lines][MAX_LINE_LEN];
	
	int c;
	int i = 0;
	// for (i = 0;; i++)
	while(42)
	{
		int j = 0;
		while ((c = get_char(f)) != EOF && j < MAX_LINE_LEN - 1)
		{
			// Pomoci modula prepisujeme radek
			buffer[i%lines][j++] = c;
			
			// Znak konce radku zapiseme a vyskocime z cyklu
			if(c == '\n')
				break;
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
	for (int k = i - lines; k < i; k++)
	{
		// Pokud bylo zadano mene radku, nez je v souboru, dostali bychom se do zaporu
		if (k < 0)
			k = 0;
		for (unsigned l = 0; l < strlen(buffer[k%lines]); l++)
			putc(buffer[k%lines][l], stdout);
	}

	return 0;
}