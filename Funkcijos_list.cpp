#include "Funkcijos_list.h"
#include <sstream>
#include <random>
#include <algorithm>
#include <chrono>
#include <list>
#include <string>

using namespace std;

// --- Pagalbinė funkcija vidurkiui ---
double vidurkis(const vector<int>& nd) {
    if (nd.empty()) return 0;
    double suma = 0;
    for (auto x : nd) suma += x;
    return suma / nd.size();
}

// --- Studentų įvedimas ranka ---
Studentas stud_iv() {
    Studentas s;
    cout << "Iveskite varda: ";
    cin >> s.vardas;
    cout << "Iveskite pavarde: ";
    cin >> s.pavarde;

    int kiekis;
    cout << "Kiek namu darbu? ";
    cin >> kiekis;

    s.paz.clear();
    for (int i = 0; i < kiekis; i++) {
        int paz;
        cout << "ND " << i + 1 << ": ";
        cin >> paz;
        s.paz.push_back(paz);
    }

    cout << "Iveskite egzamino rezultata: ";
    cin >> s.egzaminas;

    s.gal_rezultatas = 0.4 * vidurkis(s.paz) + 0.6 * s.egzaminas;
    return s;
}

// --- Spausdinimas lentelės forma ---
void spausdinti_grupe(const list<Studentas>& grupe) {
    cout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(15) << "Galutinis (vid.)" << endl;
    cout << string(45, '-') << endl;

    for (const auto& s : grupe) {
        cout << left << setw(15) << s.vardas
             << setw(15) << s.pavarde
             << setw(15) << fixed << setprecision(2) << s.gal_rezultatas << endl;
    }
}

void rikiuoti_studentus(list<Studentas>& grupe, bool pagal_varda) {
    if (pagal_varda) {
        grupe.sort([](const Studentas& a, const Studentas& b) {
            return a.vardas < b.vardas;
        });
    } else {
        grupe.sort([](const Studentas& a, const Studentas& b) {
            return a.gal_rezultatas > b.gal_rezultatas;
        });
    }
}

// --- Skaitymas iš failo į list ---
void skaityti_is_failo(list<Studentas>& grupe, const string& failo_vardas) {
    ifstream fd(failo_vardas);
    if (!fd.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << failo_vardas << endl;
        return;
    }

    string eil;
    getline(fd, eil); // praleidžiam antraštę

    grupe.clear();
    while (getline(fd, eil)) {
        stringstream ss(eil);
        Studentas s;
        ss >> s.vardas >> s.pavarde;

        int paz;
        s.paz.clear();
        while (ss >> paz)
            s.paz.push_back(paz);

        if (!s.paz.empty()) {
            s.egzaminas = s.paz.back();
            s.paz.pop_back();
        } else s.egzaminas = 0;

        s.gal_rezultatas = 0.4 * vidurkis(s.paz) + 0.6 * s.egzaminas;
        grupe.push_back(s);
    }
}

// --- Failo generavimas ---
void generuoti_studentu_faila(long long n, int nd_kiekis) {
    string failo_vardas = "studentai_" + to_string(n) + ".txt";
    ofstream fr(failo_vardas);

    fr << left << setw(15) << "Vardas"
       << setw(15) << "Pavarde";

    for (int i = 1; i <= nd_kiekis; i++)
        fr << setw(10) << ("ND" + to_string(i));
    fr << setw(10) << "Egz." << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    for (long long i = 0; i < n; i++) {
        fr << left << setw(15) << ("Vardas" + to_string(i + 1))
           << setw(15) << ("Pavarde" + to_string(i + 1));

        for (int j = 0; j < nd_kiekis; j++)
            fr << setw(10) << dist(gen);

        fr << setw(10) << dist(gen) << endl;
    }

    fr.close();
}

// --- Studentų padalijimas ---
StudentGroups padalinti_studentus(const list<Studentas>& grupe) {
    StudentGroups groups;

    for (const auto& s : grupe) {
        if (s.gal_rezultatas >= 5.0)
            groups.kietiakiai.push_back(s);
        else
            groups.vargsiukai.push_back(s);
    }
    return groups;
}

// --- Įrašymas į failą ---
void issaugoti_i_faila(const list<Studentas>& grupe, const string& failo_vardas) {
    ofstream fr(failo_vardas);
    fr << left << setw(15) << "Vardas"
       << setw(15) << "Pavarde"
       << setw(15) << "Galutinis" << endl;
    fr << string(45, '-') << endl;

    for (const auto& s : grupe) {
        fr << left << setw(15) << s.vardas
           << setw(15) << s.pavarde
           << setw(15) << fixed << setprecision(2) << s.gal_rezultatas << endl;
    }
}
