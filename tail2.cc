// tail2.cc
// Reseni IJC-DU2, priklad A), 24.4.2018
// Autor: Jan Havlin, 1BIT, xhavli47@stud.fit.vutbr.cz
// Prelozeno: gcc 6.4.0
// Popis: C++ implementace POSIX prikazu tail

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

int main(int argc, char **argv)
{
	std::ios::sync_with_stdio(false);
	
	long lines = 10;
	
	std::ifstream file;
	std::string par;
	
	// tail soubor || tail -n 20 soubor
	if (argc == 2 || argc == 4)
	{
		par = argv[1];
		if ((argc == 4 && !par.compare("-n")))
			lines = strtol(argv[2], NULL, 0);
		else if (argc != 2)
		{
			fprintf(stderr, "Chyba: Pouziti: tail -n CISLO SOUBOR\n");
			return 1;			
		}
		
		file.open(argv[argc - 1]);
		if (!file.is_open())
		{
			fprintf(stderr, "Chyba pri nacitani souboru\n");
			return 1;
		}
	}
	
	// tail -n 20 <soubor
	else if (argc == 3)
	{
		par = argv[1];
		if(!par.compare("-n"))
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
		fprintf(stderr, "Chyba: Zadany pocet radku nesmi byt zaporny\n");
		return 1;
	}
	
	int i = 0;
	std::queue<std::string> buffer;
	std::string line;

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
		
		// Ve stringu je na poslednim radku pouze EOF, tento radek uz nebudeme pushovat
		if ((std::cin.eof() || file.eof()) && line.length() == 0)
			break;
		
		buffer.push(line);
		
		// Smazeme nejstarsi string ve fronte, pokud jich je vic nez se ma vypsat radku
		if (buffer.size() > lines)
			buffer.pop();
		
		if ((std::cin.eof() || file.eof()) && line.length() > 0)
			break;
	}
	while(42);
	
	while (buffer.size() > 0)
	{
		std::cout << buffer.front() << '\n';
		buffer.pop();
	}

	return 0;
}