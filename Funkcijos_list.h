#ifndef FUNKCIJOS_LIST_H
#define FUNKCIJOS_LIST_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include "Studentas_list.h"

struct StudentGroups {
    std::list<Studentas> kietiakiai;
    std::list<Studentas> vargsiukai;
};

// --- Funkcijų deklaracijos ---

Studentas stud_iv();  // vartotojo įvedimas
void spausdinti_grupe(const std::list<Studentas>& grupe);
void skaityti_is_failo(std::list<Studentas>& grupe, const std::string& failo_vardas);
void generuoti_studentu_faila(long long n, int nd_kiekis);
StudentGroups padalinti_studentus(const std::list<Studentas>& grupe);
void issaugoti_i_faila(const std::list<Studentas>& grupe, const std::string& failo_vardas);

#endif
