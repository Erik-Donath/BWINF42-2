#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

#include "Solution.h"
// E:\dev\BWINF42-2\Stilvolle-Paeckchen\res\paeckchen1.txt
// E:\dev\BWINF42-2\Stilvolle-Paeckchen\res\a.txt

i32 main(i32 argc, char* argv[]) {
    std::setlocale(LC_ALL, "de");

    std::ifstream file;
    std::string   filePath;

    // Parameter Datei wird geöfnet
    if (argc >= 2) {
        filePath = argv[1];
        file.open(filePath.c_str(), std::ios::in);
        std::cout << "Die Datei, die als Parameter übergeben wurde, "
                  << (file.is_open() ? "wird verwendet!" : "konnte nicht gelesen werden!")
                  << std::endl;
    }

    // Nutzer wird nach Datei Pfad gefragt
    while (!file.is_open()) {
        std::cout << "Gib den Pfad zur Datei an: ";
        std::cin >> filePath;
        file.open(filePath.c_str(), std::ios::in);
    }

    if (!file.good()) {
        file.close();
        std::cout << "Die Datei konnte nicht gelesen werden!" << std::endl;
        return 1;
    }

    // Daten werden, wenn möglich, aus der Datei gelesen
    u32 s = 0, r = 0;
    std::vector<Pair> pairs;
    std::vector<Thing> things;

    std::string line;
    std::stringstream stream;

    if (std::getline(file, line)) {
        stream.clear();
        stream << line;

        stream >> s >> r;
    }

    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        Pair pair;
        stream >> pair.x >> pair.y;
        pairs.push_back(pair);
    }

    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        Thing thing;
        stream >> thing.i >> thing.j >> thing.n;
        things.push_back(thing);
    }

    file.close();

    if (s == 0 || r == 0 || pairs.size() == 0 || things.size() == 0) {
        std::cout << "Konnte Daten nicht laden. Die Datei könnte Fehler enthalten." << std::endl;
        return 1;
    }

    // Gibt die Informationen auf der Konsole wieder
    std::cout << std::endl;
    std::cout << "Sorten Anzahl: " << s << std::endl;
    std::cout << "Still Anzahl:  " << r << std::endl;

    std::cout << std::endl << "Kombinationen: " << std::endl;
    for (const Pair& pair : pairs) {
        std::cout << "  " << pair.x << " <> " << pair.y << std::endl;
    }

    std::cout << std::endl << "Dinge: " << std::endl;
    for (const Thing& thing : things) {
        std::cout << "  " << thing.i << " + " << thing.j << " => " << thing.n << std::endl;
    }

    // Löst die Aufgabe. Siehe Solution.cpp bzw. Solution.h
    auto start = std::chrono::high_resolution_clock::now();
    const Solution solution = Solve(pairs, things, s, r);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationNano = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    auto durationMili = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Funktion took " << durationNano << " nanoseconds (" << durationMili << " miliseconds)." << std::endl;

    std::cout << std::endl << "Packete: " << std::endl;
    for (const Packet& p : *solution.packets) {
        std::cout << "  " << p.n << " * ("
            << p.a.j << ' ' << p.a.i << ") + ("
            << p.b.j << ' ' << p.b.i << ") + ("
            << p.c.j << ' ' << p.c.i << ')'
            << std::endl;
    }

    std::cout << std::endl << "Rest: " << std::endl;
    for (const Thing& t : *solution.rest) {
        std::cout << "  " << t.n << " * (" << t.i << " " << t.j << ")" << std::endl;
    }

    return 0;
}