#include "Funkcijos.h"   // tavo funkcijos, Studentas ir StudentGroups struktūros
#include <iostream>      // cout, cin, endl
#include <iomanip>       // setw, setprecision, left, right, fixed
#include <vector>        // vector
#include <string>        // string
#include <algorithm>     // sort
#include <cstdlib>       // rand, srand
#include <ctime>         // time
#include <chrono>        // chrono laikui matuoti
#include <fstream>       // ifstream, ofstream
#include <sstream>       // istringstream

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string fail;  // naudojamas visuose case
    vector<Studentas> grupe;
    int pasirinkimas;

    do {
        cout << "\nKa norite atlikti?" << endl;
        cout << "1. Ivesti nauja studenta" << endl;
        cout << "2. Atspausdinti rezultatus" << endl;
        cout << "3. Iseiti" << endl;
        cout << "4. Nuskaityti studentus is failo" << endl;
        cout << "5. Sugeneruoti atsitiktinius studentu failus" << endl;
        cout << "6. Padalinti studentus i grupes ir issaugoti i failus" << endl;
        cout << "7. Automatiskas testas su 5 failais (1000, 10000, 100000, 1000000, 10000000)" << endl;
        cout << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                grupe.push_back(stud_iv());
                break;

            case 2:
                if (grupe.empty()) {
                    cout << "Nera studentu duomenu!" << endl;
                    break;
                }
                surusiuoti_pagal_varda(grupe);
                spausdinti_grupe(grupe);
                break;

            case 3:
                cout << "Programa baigta." << endl;
                break;

            // ------------------ Case 4: Nuskaityti studentus is failo ------------------
            case 4: {
                cout << "Iveskite failo pavadinima: ";
                cin >> fail;  // įrašome į globalų main() kintamąjį
                auto start = chrono::high_resolution_clock::now();
                skaityti_is_failo(grupe, fail);
                auto end = chrono::high_resolution_clock::now();
                auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
                cout << "Duomenu nuskaitymas uztruko: " << ms << " ms\n";
                break;
            }

            // ------------------ Case 5: Sugeneruoti naujus studentus ir issaugoti i faila ------------------
            case 5: {
                long long n;
                int nd_count;
                cout << "Kiek studentu sugeneruoti? ";
                cin >> n;
                cout << "Kiek ND pazymiu kiekvienam studentui? ";
                cin >> nd_count;

                auto start = chrono::high_resolution_clock::now();
                generuoti_studentu_faila(n, nd_count);
                auto end = chrono::high_resolution_clock::now();
                auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
                cout << "Failo generavimas uztruko: " << ms << " ms\n";
                break;
            }

            // ------------------ Case 6: Padalinti studentus i kietiakius ir vargsiukus ------------------
            case 6: {
                string fail;
                cout << "Iveskite failo pavadinima, kuri norite dalinti: ";
                cin >> fail;

                vector<Studentas> grupe_temp;
                skaityti_is_failo(grupe_temp, fail);

                if (grupe_temp.empty()) {
                    cout << "Nera studentu faile arba nepavyko nuskaityti." << endl;
                    break;
                }

                // Pasirinkimas, pagal ka rikiuoti
                int rusiavimas;
                cout << "Pagal ka rusioti studentus? (1 - pagal varda, 0 - pagal galutini bala): ";
                cin >> rusiavimas;

                StudentGroups groups = padalinti_studentus(grupe_temp);

                if (rusiavimas == 1) {
                    sort(groups.kietiakiai.begin(), groups.kietiakiai.end(), [](const Studentas& a, const Studentas& b){
                        return a.vardas < b.vardas;
                    });
                    sort(groups.vargsiukai.begin(), groups.vargsiukai.end(), [](const Studentas& a, const Studentas& b){
                        return a.vardas < b.vardas;
                    });
                } else {
                    sort(groups.kietiakiai.begin(), groups.kietiakiai.end(), [](const Studentas& a, const Studentas& b){
                        return a.gal_rezultatas > b.gal_rezultatas;
                    });
                    sort(groups.vargsiukai.begin(), groups.vargsiukai.end(), [](const Studentas& a, const Studentas& b){
                        return a.gal_rezultatas > b.gal_rezultatas;
                    });
                }

                // Automatinis naujo failo pavadinimo sudarymas
                size_t pos1 = fail.find_last_of('_');
                size_t pos2 = fail.find_last_of('.');
                string number = (pos1 != string::npos && pos2 != string::npos && pos2 > pos1)
                                ? fail.substr(pos1 + 1, pos2 - pos1 - 1)
                                : "output";

                issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + number + ".txt");
                issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + number + ".txt");

                cout << "Studentai issaugoti i kietiakiai_" << number 
                     << ".txt ir vargsiukai_" << number << ".txt" << endl;
                break;
            }

            // ------------------ Case 7: Automatiskas testas su 5 failais ------------------
           // ------------------ Case 7: Automatiskas testas su jau sukurtomis failu ------------------
// ------------------ Case 7: Automatiskas testas su jau egzistuojanciais failais ------------------
case 7: {
    vector<long long> sizes = {1000, 10000, 100000, 1000000, 10000000};

    for (auto n : sizes) {
        cout << "\n--- Testuojama su failu studentai_" << n << ".txt ---\n";

        string fail_name = "studentai_" + to_string(n) + ".txt";
        vector<Studentas> test_grupe;

        // Nuskaitymas
        auto start_nuskaitymas = chrono::high_resolution_clock::now();
        skaityti_is_failo(test_grupe, fail_name);
        auto end_nuskaitymas = chrono::high_resolution_clock::now();
        double laikas_nuskaitymas = chrono::duration_cast<chrono::duration<double>>(end_nuskaitymas - start_nuskaitymas).count();

        if (test_grupe.empty()) {
            cout << "Failas " << fail_name << " tuscias arba nepavyko nuskaityti." << endl;
            continue;
        }

        // Rikiavimas pagal galutini bala (didejimo tvarka)
        auto start_rikiavimas = chrono::high_resolution_clock::now();
        sort(test_grupe.begin(), test_grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.gal_rezultatas < b.gal_rezultatas;
        });
        auto end_rikiavimas = chrono::high_resolution_clock::now();
        double laikas_rikiavimas = chrono::duration_cast<chrono::duration<double>>(end_rikiavimas - start_rikiavimas).count();

        // Padalijimas
        auto start_padalijimas = chrono::high_resolution_clock::now();
        StudentGroups groups = padalinti_studentus(test_grupe);
        auto end_padalijimas = chrono::high_resolution_clock::now();
        double laikas_padalijimas = chrono::duration_cast<chrono::duration<double>>(end_padalijimas - start_padalijimas).count();

        // Irasymas i failus
        auto start_irasymas = chrono::high_resolution_clock::now();
        issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + to_string(n) + ".txt");
        issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + to_string(n) + ".txt");
        auto end_irasymas = chrono::high_resolution_clock::now();
        double laikas_irasymas = chrono::duration_cast<chrono::duration<double>>(end_irasymas - start_irasymas).count();

        // Bendras laikas
        double laikas_total = laikas_nuskaitymas + laikas_rikiavimas + laikas_padalijimas + laikas_irasymas;

        cout << fixed << setprecision(3);
        cout << "Nuskaitymas: " << laikas_nuskaitymas << " s\n";
        cout << "Rikiavimas: " << laikas_rikiavimas << " s\n";
        cout << "Padalijimas: " << laikas_padalijimas << " s\n";
        cout << "Irasymas: " << laikas_irasymas << " s\n";
        cout << "Bendras laikas: " << laikas_total << " s\n";
    }
    break;
}

            default:
                cout << "Neteisingas pasirinkimas." << endl;
        }

    } while (pasirinkimas != 3);

    return 0;
}
