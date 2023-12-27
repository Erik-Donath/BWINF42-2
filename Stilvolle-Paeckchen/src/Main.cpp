#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Solution.h"
// E:\dev\BWINF42-2\Stilvolle-Paeckchen\res\paeckchen1.txt
// E:\dev\BWINF42-2\Stilvolle-Paeckchen\res\a.txt

i32 main(i32 argc, char* argv[]) {
    std::setlocale(LC_ALL, "de");

    std::ifstream file;
    std::string filePath;

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
    std::string line;
    std::stringstream stream;

    u32 s = 0, r = 0;
    if (std::getline(file, line)) {
        stream.clear();
        stream << line;

        stream >> s >> r;
    }

    std::vector<Kombination> kombinationen;
    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        Kombination k;
        stream >> k.x >> k.y;
        kombinationen.push_back(k);
    }

    std::vector<Sorte> sorten;
    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        Sorte s;
        stream >> s.i >> s.j >> s.n;
        sorten.push_back(s);
    }

    file.close();

    if (s == 0 || r == 0 || kombinationen.size() == 0 || sorten.size() == 0) {
        std::cout << "Konnte Daten nicht laden. Die Datei könnte Fehler enthalten." << std::endl;
        return 1;
    }
    
    // Löst die Aufgabe. Siehe Solution.cpp bzw. Solution.h
    std::vector<Packet> packete = Solve(s, r, kombinationen, sorten);

    // Gibt die Informationen auf der Konsole wieder
    std::cout << std::endl;
    std::cout << "Sorten Anzahl: " << s << std::endl;
    std::cout << "Still Anzahl:  " << r << std::endl;

    std::cout << std::endl << "Kombinationen: " << std::endl;
    for (const Kombination& k : kombinationen) {
        std::cout << "  " << k.x << " <> " << k.y << std::endl;
    }

    std::cout << std::endl << "Sorten: " << std::endl;
    for (const Sorte& s : sorten) {
        std::cout << "  " << s.i << " + " << s.j << " => " << s.n << std::endl;
    }

    std::cout << std::endl << "Packete: " << std::endl;
    for (const Packet& p : packete) {
        std::cout << "  "
                  << "("     << p.a.i << " + " << p.a.j
                  << ") + (" << p.b.i << " + " << p.b.j
                  << ") + (" << p.c.i << " + " << p.c.j
                  << ")"
                  << std::endl;
    }

    return 0;
}
