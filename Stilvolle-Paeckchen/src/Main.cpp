#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//E:\dev\BWINF42-2\Stilvolle-Paeckchen\res\paeckchen1.txt

struct Pair {
    uint32_t x, y;
};
struct Sorte {
    uint32_t i, j, n;
};

int main() {
    // Ask user for the file path
    std::ifstream file;
    do {
        std::cout << "Gib die Datei an: ";
        std::string inputFile;

        std::cin >> inputFile;
        file.open(inputFile.c_str());
    } while (!file.is_open());

    //Reading S and R
    std::string line;
    std::getline(file, line);

    uint32_t spaceIndex = line.find(' ');
    uint32_t s = std::stoi(line.substr(0, spaceIndex));
    uint32_t r = std::stoi(line.substr(spaceIndex + 1));

    //Reading Conditions
    std::vector<Pair> conditions;
    while (std::getline(file, line) && !line.empty()) {
        uint32_t spaceIndex = line.find(' ');

        Pair pair;
        pair.x = std::stoi(line.substr(0, spaceIndex));
        pair.y = std::stoi(line.substr(spaceIndex + 1));
        conditions.push_back(pair);
    }

    //Reading Sorten
    std::vector<Sorte> sorten;
    while (std::getline(file, line) && !line.empty()) {
        uint32_t firstSpaceIndex = line.find(' ');
        uint32_t secondSpaceIndex = line.find(' ', firstSpaceIndex + 1);

        Sorte sorte;
        sorte.i = std::stoi(line.substr(0, firstSpaceIndex));
        sorte.j = std::stoi(line.substr(firstSpaceIndex, secondSpaceIndex - firstSpaceIndex));
        sorte.n = std::stoi(line.substr(secondSpaceIndex));
        sorten.push_back(sorte);
    }
    file.close();

    std::cout << "Sorten: " << s << ", Stilrichtungen: " << r << std::endl;
    std::cout << "- Bedingungen - " << std::endl;
    for (Pair p : conditions) {
        std::cout << p.x << " - " << p.y << std::endl;
    }

    std::cout << "- Sorten -" << std::endl;
    for (Sorte s : sorten) {
        std::cout << s.i << " + " << s.j << " = " << s.n << std::endl;
    }
}
