#pragma once
#include <vector>

typedef int32_t     i32;
typedef uint32_t    u32;
typedef const char  cstr;

struct Pair {
    u32 x, y; // x; Still 1, y: Still 2
};

struct Combination {
    u32 a, b, c;

    inline const bool operator==(const Combination& other) const {
        return (
            (a == other.a && b == other.b && c == other.c) ||
            (a == other.a && b == other.c && c == other.b) ||

            (a == other.b && b == other.c && c == other.a) ||
            (a == other.b && b == other.a && c == other.c) ||

            (a == other.c && b == other.a && c == other.b) ||
            (a == other.c && b == other.b && c == other.a)
        );
    }
};

struct Thing {
    u32 i, j, n; // i: Sorte, j: Still, n: Anzahl

    inline bool operator==(const Thing& other) {
        return (
            this->i == other.i &&
            this->j == other.j
        );
    }
    inline bool operator==(Thing& other) {
        return (
            this->i == other.i &&
            this->j == other.j
            );
    }
};

struct Packet {
    Thing a, b, c; // Things werden anzahl = 1 haben müssen.
    u32 n;

    Packet(Thing& a, Thing& b, Thing& c) : a(a), b(b), c(c), n(1) { }
    Packet(Combination& combi) {
        a.i = combi.a;
        b.i = combi.b;
        c.i = combi.c;
        n = 1;
    }
    inline void SetThingCount(Thing& t, u32 n) {
        if (a.i == t.i && a.j == t.j) a.n = n;
        if (b.i == t.i && b.j == t.j) b.n = n;
        if (c.i == t.i && c.j == t.j) c.n = n;
    }

    inline const bool hasThing(const Thing& thing) const {
        return (
            (this->a.i == thing.i && this->a.j == thing.j) ||
            (this->b.i == thing.i && this->b.j == thing.j) ||
            (this->c.i == thing.i && this->c.j == thing.j)
            );
    }
    inline bool operator==(const Packet& other) {
        return (
            (this->a == other.a && this->b == other.b && this->c == other.c) ||
            (this->a == other.a && this->b == other.c && this->c == other.b) ||

            (this->b == other.a && this->c == other.b && this->a == other.c) ||
            (this->b == other.a && this->c == other.c && this->a == other.b) ||

            (this->c == other.a && this->a == other.b && this->b == other.c) ||
            (this->c == other.a && this->a == other.c && this->b == other.b)
        );
    }
};

struct Solution {
    std::vector<Packet>* packets;
    std::vector<Thing>* rest;

    Solution(std::vector<Packet>* packets, std::vector<Thing>* rest) : packets(packets), rest(rest) { }

    ~Solution() {
        delete packets, rest;
    }
};

const Solution Solve(const std::vector<Pair>& pairs, const std::vector<Thing>& things, u32 s, u32 r);
