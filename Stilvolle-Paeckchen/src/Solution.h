#pragma once
#include <vector>

typedef int32_t  i32;
typedef uint32_t u32;

struct Kombination {
    u32 x, y;
};
struct Sorte {
    u32 i, j, n;
};

struct Packet {
    Sorte a, b, c; // [Sorte].n sollte hier 1 sein.
};

std::vector<Packet> Solve(u32 sortenAnzahl, u32 stillAnzahl, std::vector<Kombination> kombinationen, std::vector<Sorte> sorten);