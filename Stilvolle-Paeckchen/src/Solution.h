#pragma once
#include <iostream>
#include <vector>

typedef int32_t  i32;
typedef uint32_t u32;

struct Kombination {
    u32 x, y;

    Kombination()             : x(0), y(0) { }
    Kombination(u32 x, u32 y) : x(x), y(y) { }
};
struct Sorte {
    u32 i, j, n;

    Sorte()                    : i(0), j(0), n(1) { }
    Sorte(u32 i, u32 j)        : i(i), j(j), n(1) { }
    Sorte(u32 i, u32 j, u32 n) : i(i), j(j), n(n) { }
};

struct Packet {
    Sorte a, b, c; // [Sorte].n sollte hier 1 sein.

    Packet()        : a(Sorte()), b(Sorte()), c(Sorte()) { }
    Packet(Sorte a, Sorte b, Sorte c) : a(a), b(b), c(c) { }
};

std::vector<Packet> Solve(u32 sortenAnzahl, u32 stillAnzahl, std::vector<Kombination> kombinationen, std::vector<Sorte> sorten);