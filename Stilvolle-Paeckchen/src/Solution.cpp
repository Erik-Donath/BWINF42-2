#include "Solution.h"

// Muss implementiert werden!
std::vector<Packet> Solve(u32 sortenAnzahl, u32 stillAnzahl, std::vector<Kombination> kombinationen, std::vector<Sorte> sorten) {
	std::vector<Packet> packete;
	packete.push_back(Packet(Sorte(1,  2),  Sorte(3,  4),  Sorte(5,  6 )));
	packete.push_back(Packet(Sorte(7,  8),  Sorte(9,  10), Sorte(11, 12)));
	packete.push_back(Packet(Sorte(13, 14), Sorte(15, 16), Sorte(17, 18)));

	return packete;
}