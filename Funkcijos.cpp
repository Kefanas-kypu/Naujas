#include "Funkcijos.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

Studentas stud_iv() {
    Studentas pirmas;
    int sum = 0, n = 0;
    int laik_paz;

    cout << "Iveskite studento duomenis" << endl;
    cout << "Vardas: ";
    cin >> pirmas.vardas;
    cout << "Pavarde: ";
    cin >> pirmas.pavarde;

    int generuoti;
    cout << "Ar pazymius generuoti atsitiktinai? (1 - generuoti, 0 - vesti ranka): ";
    cin >> generuoti;

    if (generuoti == 1) {
        int kiek = rand() % 10 + 1;
        for (int i = 0; i < kiek; i++) {
            int random_paz = rand() % 10 + 1;
            pirmas.paz.push_back(random_paz);
            sum += random_paz;
            n++;
        }
        pirmas.egzaminas = rand() % 10 + 1;
    } else {
        int kl;
        cout << "Ar zinote, kiek pazymiu turi studentas? (1 - taip, 0 - ne): ";
        cin >> kl;

        if (kl == 0) {
            int laik_paz = -1;
            while (laik_paz != 0) {
                cout << "Iveskite pazymi (arba 0, jei daugiau pazymiu nera): ";
                cin >> laik_paz;
                if (laik_paz != 0) {
                    pirmas.paz.push_back(laik_paz);
                    sum += laik_paz;
                    n++;
                }
            }
            cout << "Iveskite egzamino pazymi: ";
            cin >> pirmas.egzaminas;
        } else {
            cout << "Kiek pazymiu turi studentas? ";
            cin >> n;
            for (int a = 0; a < n; a++) {
                cout << a + 1 << ": ";
                cin >> laik_paz;
                pirmas.paz.push_back(laik_paz);
                sum += laik_paz;
            }
            cout << "Iveskite egzamino pazymi: ";
            cin >> pirmas.egzaminas;
        }
    }

    pirmas.gal_rezultatas = double(sum) / double(n) * 0.4 + pirmas.egzaminas * 0.6;

    vector<int> paz_temp = pirmas.paz;
    paz_temp.push_back(pirmas.egzaminas);
    sort(paz_temp.begin(), paz_temp.end());
    int kiek = paz_temp.size();
    if (kiek % 2 != 0) pirmas.mediana = double(paz_temp[kiek / 2]);
    else pirmas.mediana = double(paz_temp[(kiek - 1) / 2] + paz_temp[kiek / 2]) / 2.0;

    return pirmas;
}

void spausdinti_grupe(const vector<Studentas>& grupe) {
    if (grupe.empty()) {
        cout << "Nera studentu" << endl;
        return;
    }

    cout << setw(10) << left << "Vardas" << "|"
         << setw(15) << right << "Pavarde" << "|"
         << setw(20) << right << "Galutinis (Vid.)" << "|"
         << setw(20) << right << "Galutinis (Med.)" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (const auto& stud : grupe) {
        cout << setw(11) << left << stud.vardas << "|"
             << setw(15) << right << stud.pavarde << "|"
             << fixed << setprecision(2) << setw(20) << right << stud.gal_rezultatas << "|"
             << fixed << setprecision(2) << setw(20) << right << stud.mediana << endl;
    }
}

void surusiuoti_pagal_varda(vector<Studentas>& grupe) {
    sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.vardas < b.vardas;
    });
}

void skaityti_is_failo(vector<Studentas>& grupe, const string& failo_vardas) {
    ifstream failas(failo_vardas);
    if (!failas) {
        cout << "Nepavyko atidaryti failo: " << failo_vardas << endl;
        return;
    }

    string header;
    getline(failas, header);

    int nd_kiekis = 0;
    {
        istringstream iss(header);
        string word;
        while (iss >> word) {
            if (word.find("ND") != string::npos) nd_kiekis++;
        }
    }

    string vardas, pavarde;
    while (failas >> vardas >> pavarde) {
        Studentas temp;
        temp.vardas = vardas;
        temp.pavarde = pavarde;
        temp.paz.clear();

        int pazymys;
        for (int i = 0; i < nd_kiekis; i++) {
            failas >> pazymys;
            temp.paz.push_back(pazymys);
        }

        failas >> temp.egzaminas;

        int sum = 0;
        for (auto p : temp.paz) sum += p;
        int n = temp.paz.size();

        temp.gal_rezultatas = double(sum) / double(n) * 0.4 + temp.egzaminas * 0.6;

        vector<int> paz_temp = temp.paz;
        paz_temp.push_back(temp.egzaminas);
        sort(paz_temp.begin(), paz_temp.end());
        int kiek = paz_temp.size();
        if (kiek % 2 != 0) temp.mediana = double(paz_temp[kiek / 2]);
        else temp.mediana = double(paz_temp[(kiek - 1) / 2] + paz_temp[kiek / 2]) / 2.0;

        grupe.push_back(temp);
    }

    cout << "Studentai nuskaityti is failo " << failo_vardas << endl;
}

StudentGroups padalinti_studentus(const vector<Studentas>& grupe) {
    StudentGroups groups;
    for (const auto& stud : grupe) {
        if (stud.gal_rezultatas >= 5.0)
            groups.kietiakiai.push_back(stud);
        else
            groups.vargsiukai.push_back(stud);
    }
    return groups;
}

void issaugoti_i_faila(const vector<Studentas>& grupe, const string& failo_vardas) {
    ofstream out(failo_vardas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failo_vardas << endl;
        return;
    }

    out << setw(10) << left << "Vardas" << "|"
        << setw(15) << right << "Pavarde" << "|"
        << setw(20) << right << "Galutinis (Vid.)" << "|"
        << setw(20) << right << "Galutinis (Med.)" << endl;
    out << "--------------------------------------------------------------------" << endl;

    for (const auto& stud : grupe) {
        out << setw(11) << left << stud.vardas << "|"
            << setw(15) << right << stud.pavarde << "|"
            << fixed << setprecision(2) << setw(20) << right << stud.gal_rezultatas << "|"
            << fixed << setprecision(2) << setw(20) << right << stud.mediana << endl;
    }

    out.close();
}
