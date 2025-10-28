#pragma once
#include "Studentas.h"
#include <vector>
#include <string>

// Funkciju deklaracijos (prototipai)
Studentas stud_iv();  
Studentas generuoti_atsitiktini_studenta(); 
void spausdinti_grupe(const std::vector<Studentas>& grupe);
void surusiuoti_pagal_varda(std::vector<Studentas>& grupe);
void skaityti_is_failo(std::vector<Studentas>& grupe, const std::string& failo_vardas);
void generuoti_studentu_faila(long long n, int nd_count);
StudentGroups padalinti_studentus(const std::vector<Studentas>& grupe);
void issaugoti_i_faila(const std::vector<Studentas>& grupe, const std::string& failo_vardas);