#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Solution.h"
//E:\dev\BWINF42-2\Stilvolle-Paeckchen\res\paeckchen1.txt

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
        std::cout << "Datei konnte nicht gelesen werden!" << std::endl;
        return 1;
    }

    // Read file
    std::string line;
    std::stringstream stream;

    u32 sortenAnzahl = 0, stillAnzahl = 0;
    if (std::getline(file, line)) {
        stream.clear();
        stream << line;

        stream >> sortenAnzahl;
        stream >> stillAnzahl;
    }

    std::vector<Kombination> kombinationen;
    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        Kombination k;
        stream >> k.x;
        stream >> k.y;
        kombinationen.push_back(k);
    }

    std::vector<Sorte> sorten;
    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        Sorte s;
        stream >> s.i;
        stream >> s.j;
        stream >> s.n;
        sorten.push_back(s);
    }
    file.close();

    // Solve
    if (sortenAnzahl == 0 || stillAnzahl == 0 || kombinationen.size() == 0 || sorten.size() == 0) {
        std::cout << "Datei ist fehlerhaft oder Kombinationen/Sorten sind falsch angegeben worden." << std::endl;
        return 1;
    }

    std::vector<Packet> packete = Solve(sortenAnzahl, stillAnzahl, kombinationen, sorten);

    // Output
    std::cout << "Sorten Anzahl: " << sortenAnzahl << std::endl;
    std::cout << "Still Anzahl:  "  << stillAnzahl  << std::endl;

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
