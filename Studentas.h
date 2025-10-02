#pragma once
#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> paz;
    int egzaminas;
    double gal_rezultatas;
    double mediana;
};

struct StudentGroups {
    std::vector<Studentas> kietiakiai;
    std::vector<Studentas> vargsiukai;
};
