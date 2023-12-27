#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Solution.h"
//E:\dev\BWINF42-2\Stilvolle-Paeckchen\res\paeckchen1.txt

i32 main(i32 argc, char* argv[]) {
    std::setlocale(LC_ALL, "de");
    std::ifstream file;
    std::string filePath;

    // Parameter Datei wird gelesen
    if (argc >= 2) {
        filePath = argv[1];
        file.open(argv[1], std::ios::in);
        std::cout << "Die Datei, die als Parameter übergeben wurde, "
                  << (file.is_open() ? "wird verwendet!" : "konnte nicht gelesen werden!")
                  << std::endl;
    }

    // Nutzer wird nach Datei gefragt
    while (!file.is_open()) {
        std::cout << "Gib den Pfad zur Datei an: ";
        std::cin >> filePath;
        file.open(filePath.c_str(), std::ios::in);
    }

    file.close();
    std::cout << "Die Datei ist: " << filePath << std::endl;

    return 0;
}
