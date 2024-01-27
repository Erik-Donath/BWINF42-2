#pragma once
#include <vector>

typedef int32_t     i32;
typedef uint32_t    u32;
typedef const char  cstr;

struct CPair { // CombinationPair
    u32 x, y; // x: Still 1, y: Still 2
};
struct Thing {
    u32 i, j, n; // i: Sorte, j: Still, n: Anzahl

    Thing() = default;
    Thing(u32 i, u32 j, u32 n)   : i(i),   j(j),   n(n)   { }
    Thing(const Thing& o)        : i(o.i), j(o.j), n(o.n) { }
    Thing(const Thing& o, u32 n) : i(o.i), j(o.j), n(n)   { }

    inline bool operator==(const Thing& other) {
        return (
            this->i == other.i &&
            this->j == other.j &&
            this->n == other.n
        );
    }
};
struct Packet {
    Thing a, b, c;

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
            (this->b == other.b && this->a == other.c && this->c == other.a) ||
            (this->c == other.c && this->a == other.b && this->b == other.c)
        );
    }
};
struct Input {
    u32 s = 0, r = 0; // s: Sorten, r: Still anzahl

    std::vector<CPair> combinations;
    std::vector<Thing> things;

    inline bool invalid() {
        return (
            s == 0 ||
            r == 0 ||
            combinations.size() == 0 ||
            things.size() == 0
        );
    }
};
struct Output {
    std::vector<Packet> packets;

    Output(const std::vector<Packet>& packets) : packets(packets) { }
};
const Output& Solve(const Input& input);