#include <unordered_map>
#include <vector>

#include "Solution.h"

#include <iostream>

template<class Container, class Object>
inline bool contains(Container& container, const Object& value) {
	return !container.empty() && std::find(container.begin(), container.end(), value) != container.end();
}
template<class Container, class Object>
inline u32 getIndex(Container& container, const Object& value) { // If not in container it will be the lenght of the container. [2, 3] search for 1 => 3
	return std::distance(container.begin(), std::find(container.begin(), container.end(), value));
}
template<class Container, class Object>
inline Object* getElement(Container& container, const Object& value) {
	u32 index = getIndex(container, value);
	if (index == container.end() - container.begin()) return nullptr;
	return &container[index];
}

static inline u32 minimum(u32 a, u32 b) {
	return (a < b) ? a : b;
}
static inline u32 minimum(u32 a, u32 b, u32 c) {
	return minimum(minimum(a, c), minimum(b, c));
}
static void addThing(std::vector<Thing>& rest, Thing& thing, u32 n) {
	Thing* t = getElement(rest, thing);
	if(t == nullptr) {
		Thing t(thing);
		t.n = n;
		rest.push_back(t);
	}
	else {
		t->n += n;
	}
}

static const std::vector<Combination>* generateCombinations(const std::vector<Pair>& pairs, u32 r) {
	std::unordered_map<u32, std::vector<u32>> pmap;

	for (int i = 1; i <= r; i++) pmap[i].push_back(i);
	for (const Pair& pair : pairs) {
		pmap[pair.x].push_back(pair.y);
		pmap[pair.y].push_back(pair.x);
	}

	std::vector<Combination>* combinations = new std::vector<Combination>;
	for (auto& kv : pmap) {
		u32 i = kv.first;
		std::vector<u32>& a = kv.second;
		for (u32 j : a) {
			std::vector<u32>& b = pmap[j];
			for (u32 k : b) {
				Combination c = Combination(i, j, k);
				if (contains(a, k) && !contains(*combinations, c)) {
					combinations->push_back(c);
				}
			}
		}
	}
	return combinations;
}


const Solution Solve(const std::vector<Pair>& pairs, const std::vector<Thing>& things, u32 s, u32 r) {
	std::vector<Packet>* packets = new std::vector<Packet>;
	std::vector<Thing>* rest = new std::vector<Thing>;

	std::unordered_map<u32, std::vector<Thing>> smap;
	std::unordered_map<Thing*, std::vector<u32>> cmap;

	for (const Thing& thing : things)
		smap[thing.j].push_back(thing);

	const std::vector<Combination>* combinations = generateCombinations(pairs, r);
	for (const Combination& c : *combinations) {
		for (Thing& a : smap[c.a]) {
			for ( Thing& b : smap[c.b]) {
				for (Thing& c : smap[c.c]) {
					if (a == b || a == c || b == c) continue;
					if (a.i == b.i || a.i == c.i || b.i == c.i) continue;
					
					Packet p = Packet(a, b, c);
					if (contains(*packets, p)) continue;

					u32 index = packets->size();
					packets->push_back(p);

					if (!contains(cmap[&a], index)) cmap[&a].push_back(index);
					if (!contains(cmap[&b], index)) cmap[&b].push_back(index);
					if (!contains(cmap[&c], index)) cmap[&c].push_back(index);
				}
			}
		}
	}

	for (auto& kv : cmap) {
		Thing t = *kv.first;
		std::vector<u32> packetIndexes = kv.second;

		Thing rt = Thing(t);
		u32 n = t.n / packetIndexes.size();
		rt.n = t.n % packetIndexes.size();

		for (u32 index : packetIndexes) {
			Packet& p = (*packets)[index];
			p.SetThingCount(t, n);
		}
		if(rt.n > 0)
			rest->push_back(rt);
	}

	for (Packet& p : *packets) {
		u32 m = minimum(p.a.n, p.b.n, p.c.n);
		u32 ar = p.a.n - m, br = p.b.n - m, cr = p.c.n;
		p.n = p.a.n = p.b.n = p.c.n = m;

		if (ar > 0) addThing(*rest, p.a, ar);
		if (br > 0) addThing(*rest, p.b, br);
		if (cr > 0) addThing(*rest, p.c, cr);
	}
	
	delete combinations;
	return Solution(packets, rest);
}