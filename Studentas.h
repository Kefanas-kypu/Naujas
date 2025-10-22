#pragma once
#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> paz;
    int egzaminas = 0;
    double gal_rezultatas = 0.0;
    double mediana = 0.0;
};

struct StudentGroups {
    std::vector<Studentas> kietiakiai;
    std::vector<Studentas> vargsiukai;
};
