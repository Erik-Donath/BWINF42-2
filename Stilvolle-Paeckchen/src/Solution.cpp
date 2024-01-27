#include <vector>
#include "Solution.h"

#include <iostream>

template<class Container, class Object>
inline bool contains(Container container, const Object& value) {
	return !container.empty() && std::find(container.begin(), container.end(), value) != container.end();
}

void debugSolution(const Input& input, const std::vector<Thing>* smap, const std::vector<u32>* kmap, const std::vector<Packet>& packets);
const Output& Solve(const Input& input) {
	// Sortiert die Sorten in eine Map, so das man die Sorten anhand der Stille einfacher ansprechen kann.
	std::vector<Thing>* smap = new std::vector<Thing>[input.r];
	for (Thing thing : input.things) {
		thing.j -= 1, thing.i -= 1;
		smap[thing.j].push_back(thing);
	}

	// Erstellt eine Map, die für ein Still anzeigt, mit welchen anderen Stillen er kombienert werden kann.
	std::vector<u32>* kmap = new std::vector<u32>[input.r];
	for (u32 i = 0; i < input.r; i++)
		kmap[i].push_back(i);
	for (CPair pair : input.combinations) {
		kmap[pair.x - 1].push_back(pair.y - 1);
		kmap[pair.y - 1].push_back(pair.x - 1);
	}

	std::vector<Packet> packets;
	for (u32 a = 0; a < input.r; a++) {
	for (u32 b : kmap[a]) { // Alle Combis von a werden durchgegangen. Das erspart unnötiges checken.
	for (u32 c : kmap[b]) {
		if (contains(kmap[a], c)) { // c muss auch mit a kompatible sein!
			for (Thing d : smap[a]) {
			for (Thing e : smap[b]) {
			for (Thing f : smap[c]) {
				Packet p(Thing(d, 0), Thing(e, 0), Thing(f, 0));
				if (!contains(packets, p)) {
					packets.push_back(p);
				}
			}}}
		}
	}}}
	
	for (Thing t : input.things) {
		t.i -= 1, t.j -= 1;
		std::vector<Packet> k;
		for (const Packet& p : packets) {
			if (p.hasThing(t)) {
				k.push_back(p);
			}
		}
		std::cout << "For Thing (" << (t.j + 1) << ' ' << (t.i + 1) << "):" << std::endl;
		if (k.empty()) std::cout << "  Empty" << std::endl;
		for (const Packet& p : k) {
			std::cout << "  ("
					  << (p.a.j + 1) << ' ' << (p.a.i + 1) << ' ' << p.a.n << ") + ("
					  << (p.b.j + 1) << ' ' << (p.b.i + 1) << ' ' << p.a.n << ") + ("
					  << (p.c.j + 1) << ' ' << (p.c.i + 1) << ' ' << p.a.n << ')'
					  << std::endl;
		}

	}

	debugSolution(input, smap, kmap, packets);

	delete[] smap;
	delete[] kmap;

	return Output(packets);
}

//#include <iostream>
#include <sstream>
void debugSolution(const Input& input, const std::vector<Thing>* smap, const std::vector<u32>* kmap, const std::vector<Packet>& packets) {
	std::stringstream ss;
	ss << "Smap: " << std::endl;
	for (u32 i = 0; i < input.r; i++) {
		ss << (i+1) << " => ";

		for (auto j : smap[i])
			ss << j.i << "(" << j.n << ") ";
		ss << std::endl;
	}

	ss << "Kmap: " << std::endl;
	for (u32 i = 0; i < input.r; i++) {
		ss << (i + 1) << ": ";

		for (u32 j : kmap[i])
			ss << (j+1) << " ";
		ss << std::endl;
	}
	ss << "Packets: " << std::endl;
	for (const Packet& p : packets) {
		ss << "  ("
			<< (p.a.j + 1) << ' ' << (p.a.i + 1) << ' ' << p.a.n << ") + ("
			<< (p.b.j + 1) << ' ' << (p.b.i + 1) << ' ' << p.a.n << ") + ("
			<< (p.c.j + 1) << ' ' << (p.c.i + 1) << ' ' << p.a.n << ')'
			<< std::endl;
	}
	std::cout << ss.str();
}
