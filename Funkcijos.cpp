#include "Funkcijos.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// ------------------ stud_iv (ivedimas is klaviaturos) ------------------
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
            int laik_paz_local = -1;
            while (laik_paz_local != 0) {
                cout << "Iveskite pazymi (arba 0, jei daugiau pazymiu nera): ";
                cin >> laik_paz_local;
                if (laik_paz_local != 0) {
                    pirmas.paz.push_back(laik_paz_local);
                    sum += laik_paz_local;
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

    if (n == 0) {
        pirmas.gal_rezultatas = pirmas.egzaminas;
    } else {
        pirmas.gal_rezultatas = double(sum) / double(n) * 0.4 + pirmas.egzaminas * 0.6;
    }

    vector<int> paz_temp = pirmas.paz;
    paz_temp.push_back(pirmas.egzaminas);
    sort(paz_temp.begin(), paz_temp.end());
    int kiek = static_cast<int>(paz_temp.size());
    if (kiek == 0)
        pirmas.mediana = 0.0;
    else if (kiek % 2 != 0)
        pirmas.mediana = double(paz_temp[kiek / 2]);
    else
        pirmas.mediana = double(paz_temp[(kiek - 1) / 2] + paz_temp[kiek / 2]) / 2.0;

    return pirmas;
}

// ------------------ atspausdinti grupe i ekrana ------------------
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

// ------------------ rusiavimas pagal varda ------------------
void surusiuoti_pagal_varda(vector<Studentas>& grupe) {
    sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.vardas < b.vardas;
    });
}

// ------------------ bendras rusiavimas pagal pasirinkima ------------------
void rikiuoti_studentus(vector<Studentas>& grupe, bool pagal_varda) {
    if (pagal_varda) {
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas < b.vardas;
        });
    } else {
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.gal_rezultatas > b.gal_rezultatas;
        });
    }
}

// ------------------ skaityti is failo ------------------
void skaityti_is_failo(vector<Studentas>& grupe, const string& failo_vardas) {
    ifstream failas(failo_vardas);
    if (!failas) {
        cout << "Nepavyko atidaryti failo: " << failo_vardas << endl;
        return;
    }

    string header;
    getline(failas, header);
    if (header.empty()) {
        cout << "Failas " << failo_vardas << " tuščias arba netinkamas." << endl;
        return;
    }

    int nd_kiekis = 0;
    istringstream iss(header);
    string word;
    while (iss >> word) {
        if (word.find("ND") != string::npos) nd_kiekis++;
    }

    string vardas, pavarde;
    while (failas >> vardas >> pavarde) {
        Studentas temp;
        temp.vardas = vardas;
        temp.pavarde = pavarde;
        temp.paz.clear();

        int pazymys;
        for (int i = 0; i < nd_kiekis; i++) {
            if (!(failas >> pazymys)) return;
            temp.paz.push_back(pazymys);
        }

        if (!(failas >> temp.egzaminas)) return;

        int sum = 0;
        for (auto p : temp.paz) sum += p;
        int n = static_cast<int>(temp.paz.size());
        temp.gal_rezultatas = (n == 0) ? temp.egzaminas : double(sum) / n * 0.4 + temp.egzaminas * 0.6;

        vector<int> paz_temp = temp.paz;
        paz_temp.push_back(temp.egzaminas);
        sort(paz_temp.begin(), paz_temp.end());
        int kiek = static_cast<int>(paz_temp.size());
        temp.mediana = (kiek == 0) ? 0.0 :
                       (kiek % 2 != 0 ? paz_temp[kiek / 2] :
                       double(paz_temp[(kiek - 1) / 2] + paz_temp[kiek / 2]) / 2.0);

        grupe.push_back(temp);
    }

    cout << "Studentai nuskaityti is failo: " << failo_vardas << endl;
}

// ------------------ padalinti studentus ------------------
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

// ------------------ issaugoti i faila ------------------
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
}

// ------------------ generuoti faila ------------------
void generuoti_studentu_faila(long long n, int nd_count) {
    ofstream fout("studentai_" + to_string(n) + ".txt");
    if (!fout) {
        cout << "Nepavyko sukurti failo\n";
        return;
    }

    fout << "Vardas Pavarde";
    for (int i = 1; i <= nd_count; ++i) fout << " ND" << i;
    fout << " Egzaminas\n";

    for (long long i = 1; i <= n; ++i) {
        fout << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < nd_count; ++j) fout << " " << (rand() % 10 + 1);
        fout << " " << (rand() % 10 + 1) << "\n";
    }

    fout.close();
    cout << "Sugeneruotas failas studentai_" << n << ".txt su " << n << " studentais.\n";
}

// ------------------ generuoti atsitiktini studenta ------------------
Studentas generuoti_atsitiktini_studenta() {
    Studentas s;
    s.vardas = "Vardas" + to_string(rand() % 1000000);
    s.pavarde = "Pavarde" + to_string(rand() % 1000000);
    int kiek = rand() % 10 + 1;
    int sum = 0;
    for (int i = 0; i < kiek; i++) {
        int paz = rand() % 10 + 1;
        s.paz.push_back(paz);
        sum += paz;
    }
    s.egzaminas = rand() % 10 + 1;
    if (kiek == 0) s.gal_rezultatas = s.egzaminas;
    else s.gal_rezultatas = double(sum) / double(kiek) * 0.4 + s.egzaminas * 0.6;

    vector<int> tmp = s.paz;
    tmp.push_back(s.egzaminas);
    sort(tmp.begin(), tmp.end());
    int size = static_cast<int>(tmp.size());
    if (size == 0) s.mediana = 0.0;
    else if (size % 2 != 0) s.mediana = tmp[size / 2];
    else s.mediana = (tmp[(size - 1) / 2] + tmp[size / 2]) / 2.0;

    return s;
}
