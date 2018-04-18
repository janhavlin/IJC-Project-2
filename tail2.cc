// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <istream>

int main(int argc, char **argv)
{
	long lines = 10;
	FILE *f = NULL;
	std::ifstream file;
	
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
		
		file.open (argv[argc - 1]);
	}
	
	if (file)
		std::cout << "BLABLA";
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
	
	// printf("Lines: %ld\n", lines);
	if (lines < 0)
	{
		fprintf(stderr, "Chyba: Zadany pocet radku nesmi byt zaporny\n");
		return 1;
	}
	
	int i = 0;
	std::queue<std::string> buffer;
	std::string line;
	// std::istream stream (std::cin);
	// int i = 0;
	do
	{
		if (file.is_open())
		{
		std::cout << i++ << '\n';
			std::getline(file, line);
		}
		else
		{
			std::getline(std::cin, line);
		}
		buffer.push(line);
		
		// Smazeme nejstarsi string ve fronte, pokud jich je vic nez se ma vypsat radku
		if (buffer.size() > lines)
			buffer.pop();
	}
	while (!std::cin.eof() && !file.eof());
	
	while (buffer.size() > 0)
	{
		std::cout << buffer.front();// << '\n';
		buffer.pop();
	}

	return 0;
}