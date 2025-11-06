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

Studentas stud_iv(); 
void spausdinti_grupe(const std::list<Studentas>& grupe);
void skaityti_is_failo(std::list<Studentas>& grupe, const std::string& failo_vardas);
void generuoti_studentu_faila(long long n, int nd_kiekis);
StudentGroups strategija1_list(const std::list<Studentas>& grupe);
void vykdyti_strategija1();
void strategija2_list(std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai);
void vykdyti_strategija2();
void issaugoti_i_faila(const std::list<Studentas>& grupe, const std::string& failo_vardas);

#endif
