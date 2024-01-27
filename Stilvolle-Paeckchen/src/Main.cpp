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
    Input input;

    std::string line;
    std::stringstream stream;

    if (std::getline(file, line)) {
        stream.clear();
        stream << line;

        stream >> input.s >> input.r;
    }

    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        CPair pair;
        stream >> pair.x >> pair.y;
        input.combinations.push_back(pair);
    }

    while (std::getline(file, line) && !line.empty()) {
        stream.clear();
        stream << line;

        Thing thing;
        stream >> thing.i >> thing.j >> thing.n;
        input.things.push_back(thing);
    }

    file.close();

    if (input.invalid()) {
        std::cout << "Konnte Daten nicht laden. Die Datei könnte Fehler enthalten." << std::endl;
        return 1;
    }

    // Gibt die Informationen auf der Konsole wieder
    std::cout << std::endl;
    std::cout << "Sorten Anzahl: " << input.s << std::endl;
    std::cout << "Still Anzahl:  " << input.r << std::endl;

    std::cout << std::endl << "Kombinationen: " << std::endl;
    for (const CPair& pair : input.combinations) {
        std::cout << "  " << pair.x << " <> " << pair.y << std::endl;
    }

    std::cout << std::endl << "Dinge: " << std::endl;
    for (const Thing& thing : input.things) {
        std::cout << "  " << thing.i << " + " << thing.j << " => " << thing.n << std::endl;
    }

    // Löst die Aufgabe. Siehe Solution.cpp bzw. Solution.h
    const Output output = Solve(input);

    return 0;
}