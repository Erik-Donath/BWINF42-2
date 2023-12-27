#include <vector>
#include <unordered_map>

#include <iostream>

#include "Solution.h"

void debugSolution(const std::unordered_map<u32, std::vector<Sorte>>& smap, const std::unordered_map<u32, std::vector<u32>>& kmap);

// Muss implementiert werden!
const std::vector<Packet>& Solve(const u32 sortenAnzahl, const u32 stillAnzahl, const std::vector<Kombination>& kombinationen, const std::vector<Sorte>& sorten) {
	// Sortiert die Sorten in eine Map, so das man die Sorten anhand der Stille einfacher ansprechen kann.
	std::unordered_map<u32, std::vector<Sorte>> smap;
	for (Sorte s : sorten) {
		smap[s.j].push_back(s);
	}

	// Erstellt eine Map, die für ein Still anzeigt, mit welchen anderen Stillen er kombienert werden kann.
	std::unordered_map<u32, std::vector<u32>> kmap;
	for (Kombination k : kombinationen) {
		kmap[k.x].push_back(k.y);
		kmap[k.y].push_back(k.x);
	}

	debugSolution(smap, kmap);
	std::vector<Packet> packete;
	return packete;
}

void debugSolution(const std::unordered_map<u32, std::vector<Sorte>>& smap, const std::unordered_map<u32, std::vector<u32>>& kmap) {
	std::cout << "Smap: " << std::endl;
	for (auto i : smap) {
		std::cout << i.first << " => ";

		for (Sorte j : i.second)
			std::cout << j.i << "(" << j.n << ") ";
		std::cout << std::endl;
	}

	std::cout << "Kmap: " << std::endl;
	for (auto i : kmap) {
		std::cout << i.first << ": ";

		for (u32 j : i.second)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}
