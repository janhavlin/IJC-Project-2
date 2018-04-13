// wordcount-.cc
// Použijte: g++ -std=c++11
// Příklad použití STL kontejneru map<> nebo unordered_map<>
// Program počítá četnost slov ve vstupním textu,
// slovo je cokoli oddělené "bílým znakem" === isspace

#include <string>
#include <iostream>
#include <unordered_map>

int main() {
	using namespace std;
	unordered_map<string,int> m;  // asociativní pole
	string word;

	while (cin >> word) // čtení slova
		m[word]++;      // počítání výskytů slova

	for (auto &mi: m)   // pro všechny prvky kontejneru m
		cout << mi.first << "\t" << mi.second << "\n";
	// tisk     slovo (klíč)        počet (data)
}