#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::setprecision;
using std::sort;
using std::fixed;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct studentas {
    string vardas;
    string pavarde;
    vector<int> paz;
    int egzaminas;
    double gal_rezultatas;
    double mediana;
};

studentas stud_iv();
void skaityti_is_failo(vector<studentas>& grupe, const string& failo_vardas);
void spausdinti_grupe(vector<studentas>& grupe);
void surusiuoti_pagal_varda(vector<studentas>& grupe);
void generuoti_studentu_failus(); // nauja funkcija

int main() {
    srand(time(0));

    vector<studentas> grupe;
    int pasirinkimas;

    do {
        cout << "\nKa norite atlikti?" << endl;
        cout << "1. Ivesti nauja studenta" << endl;
        cout << "2. Atspausdinti rezultatus" << endl;
        cout << "3. Iseiti" << endl;
        cout << "4. Nuskaityti studentus is failo" << endl;
        cout << "5. Sugeneruoti atsitiktinius studentu failus" << endl;
        cout << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {
        case 1:
            grupe.push_back(stud_iv());
            break;
        case 2:
            surusiuoti_pagal_varda(grupe);
            spausdinti_grupe(grupe);
            break;
        case 3:
            cout << "Pabaiga." << endl;
            break;
        case 4:
            skaityti_is_failo(grupe, "studentai_1000.txt");
            break;
        case 5:
            generuoti_studentu_failus();
            break;
        default:
            cout << "Neteisingas pasirinkimas." << endl;
        }

    } while (pasirinkimas != 3);

    return 0;
}

studentas stud_iv() {
    studentas pirmas;
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

void spausdinti_grupe(vector<studentas>& grupe) {
    if (grupe.empty()) {
        cout << "Nera studentu" << endl;
        return;
    }

    cout << setw(10) << left << "Vardas" << "|"
         << setw(15) << right << "Pavarde" << "|"
         << setw(20) << right << "Galutinis (Vid.)" << "|"
         << setw(20) << right << "Galutinis (Med.)" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (auto& stud : grupe) {
        cout << setw(11) << left << stud.vardas << "|"
             << setw(15) << right << stud.pavarde << "|"
             << fixed << setprecision(2) << setw(20) << right << stud.gal_rezultatas << "|"
             << fixed << setprecision(2) << setw(20) << right << stud.mediana << endl;
    }
}

void surusiuoti_pagal_varda(vector<studentas>& grupe) {
    sort(grupe.begin(), grupe.end(), [](const studentas& a, const studentas& b) {
        return a.vardas < b.vardas;
    });
}

void skaityti_is_failo(vector<studentas>& grupe, const string& failo_vardas) {
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
        studentas temp;
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

// Nauja funkcija: generuoja studentų failus
void generuoti_studentu_failus() {
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};

    for (int dydis : dydziai) {
        string failo_vardas = "studentai_" + std::to_string(dydis) + ".txt";
        ofstream failas(failo_vardas);
        if (!failas) {
            cout << "Nepavyko sukurti failo: " << failo_vardas << endl;
            continue;
        }

        // Sukuriame header
        failas << "Vardas Pavarde";
        for (int i = 1; i <= 5; i++) failas << " ND" << i; // 5 namu darbu pazymiai
        failas << " Egzaminas" << endl;

        for (int i = 1; i <= dydis; i++) {
            failas << "Vardas" << i << " Pavarde" << i;
            for (int j = 0; j < 5; j++) {
                failas << " " << (rand() % 10 + 1);
            }
            failas << " " << (rand() % 10 + 1) << endl;
        }

        cout << "Sugeneruotas failas: " << failo_vardas << " su " << dydis << " irasu" << endl;
    }
}
