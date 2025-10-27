#include "Funkcijos.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <list>
#include <chrono>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    list<Studentas> grupe;
    string fail;
    int pasirinkimas;

    do {
        cout << "\nKa norite atlikti?" << endl;
        cout << "1. Ivesti nauja studenta" << endl;
        cout << "2. Atspausdinti rezultatus" << endl;
        cout << "3. Iseiti" << endl;
        cout << "4. Nuskaityti studentus is failo" << endl;
        cout << "5. Sugeneruoti atsitiktinius studentu failus" << endl;
        cout << "6. Padalinti studentus i grupes ir issaugoti i failus" << endl;
        cout << "7. Automatizuotas testas su 5 failais" << endl;
        cout << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        switch(pasirinkimas) {

        case 1: {
            Studentas s = stud_iv();
            grupe.push_back(s);
            cout << "Studento objektas saugomas adrese: " << &(*grupe.rbegin()) << endl;
            break;
        }

        case 2: {
            if (grupe.empty()) {
                cout << "Nera studentu duomenu!" << endl;
                break;
            }
            grupe.sort([](const Studentas& a, const Studentas& b){
                return a.vardas < b.vardas;
            });
            spausdinti_grupe(vector<Studentas>(grupe.begin(), grupe.end()));
            break;
        }

        case 3:
            cout << "Programa baigta." << endl;
            break;

        case 4: {
            cout << "Iveskite failo pavadinima: ";
            cin >> fail;
            auto start = chrono::high_resolution_clock::now();
            vector<Studentas> tmp;
            skaityti_is_failo(tmp, fail);
            grupe.assign(tmp.begin(), tmp.end());
            auto end = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double>(end - start).count();
            cout << "Duomenu nuskaitymas uztruko: " << ms << " s\n";
            break;
        }

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
            double ms = chrono::duration<double>(end - start).count();
            cout << "Failo generavimas uztruko: " << ms << " s\n";
            break;
        }

        case 6: {
            cout << "Iveskite failo pavadinima, kuri norite dalinti: ";
            cin >> fail;

            vector<Studentas> tmp;
            skaityti_is_failo(tmp, fail);
            grupe.assign(tmp.begin(), tmp.end());

            if (grupe.empty()) {
                cout << "Nera studentu faile arba nepavyko nuskaityti." << endl;
                break;
            }

            int rusiavimas;
            cout << "Pagal ka rusioti studentus? (1 - pagal varda, 0 - pagal galutini bala): ";
            cin >> rusiavimas;

            auto start_rusiavimas = chrono::high_resolution_clock::now();
            vector<Studentas> tmp_vec(grupe.begin(), grupe.end());
            StudentGroups groups = padalinti_studentus(tmp_vec);

            if (rusiavimas == 1) {
                sort(groups.kietiakiai.begin(), groups.kietiakiai.end(),
                     [](const Studentas& a, const Studentas& b){ return a.vardas < b.vardas; });
                sort(groups.vargsiukai.begin(), groups.vargsiukai.end(),
                     [](const Studentas& a, const Studentas& b){ return a.vardas < b.vardas; });
            } else {
                sort(groups.kietiakiai.begin(), groups.kietiakiai.end(),
                     [](const Studentas& a, const Studentas& b){ return a.gal_rezultatas > b.gal_rezultatas; });
                sort(groups.vargsiukai.begin(), groups.vargsiukai.end(),
                     [](const Studentas& a, const Studentas& b){ return a.gal_rezultatas > b.gal_rezultatas; });
            }
            auto end_rusiavimas = chrono::high_resolution_clock::now();
            double laikas_rusiavimas = chrono::duration<double>(end_rusiavimas - start_rusiavimas).count();

            auto start_irasymas = chrono::high_resolution_clock::now();
            size_t pos1 = fail.find_last_of('_');
            size_t pos2 = fail.find_last_of('.');
            string number = (pos1 != string::npos && pos2 != string::npos && pos2 > pos1)
                            ? fail.substr(pos1 + 1, pos2 - pos1 - 1)
                            : "output";

            issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + number + ".txt");
            issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + number + ".txt");
            auto end_irasymas = chrono::high_resolution_clock::now();
            double laikas_irasymas = chrono::duration<double>(end_irasymas - start_irasymas).count();

            cout << "Studentai issaugoti i kietiakiai_" << number 
                 << ".txt ir vargsiukai_" << number << ".txt" << endl;

            cout << "Rusiavimo laikas: " << laikas_rusiavimas << " s" << endl;
            cout << "Irasymo i faila laikas: " << laikas_irasymas << " s" << endl;
            break;
        }

        case 7: {
            vector<long long> sizes = {1000, 10000, 100000, 1000000, 10000000};
            cout << fixed << setprecision(3);

            for (auto n : sizes) {
                cout << "\n--- Testuojama su failu studentai_" << n << ".txt ---\n";
                string fail_name = "studentai_" + to_string(n) + ".txt";
                list<Studentas> test_grupe;

                auto start_nuskaitymas = chrono::high_resolution_clock::now();
                vector<Studentas> tmp;
                skaityti_is_failo(tmp, fail_name);
                test_grupe.assign(tmp.begin(), tmp.end());
                auto end_nuskaitymas = chrono::high_resolution_clock::now();
                double laikas_nuskaitymas = chrono::duration<double>(end_nuskaitymas - start_nuskaitymas).count();

                if (test_grupe.empty()) {
                    cout << "Failas " << fail_name << " tuscias arba nepavyko nuskaityti." << endl;
                    continue;
                }

                auto start_rikiavimas = chrono::high_resolution_clock::now();
                test_grupe.sort([](const Studentas& a, const Studentas& b){
                    return a.gal_rezultatas < b.gal_rezultatas;
                });
                auto end_rikiavimas = chrono::high_resolution_clock::now();
                double laikas_rikiavimas = chrono::duration<double>(end_rikiavimas - start_rikiavimas).count();

                auto start_padalijimas = chrono::high_resolution_clock::now();
                StudentGroups groups = padalinti_studentus(vector<Studentas>(test_grupe.begin(), test_grupe.end()));
                auto end_padalijimas = chrono::high_resolution_clock::now();
                double laikas_padalijimas = chrono::duration<double>(end_padalijimas - start_padalijimas).count();

                auto start_irasymas = chrono::high_resolution_clock::now();
                issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + to_string(n) + ".txt");
                issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + to_string(n) + ".txt");
                auto end_irasymas = chrono::high_resolution_clock::now();
                double laikas_irasymas = chrono::duration<double>(end_irasymas - start_irasymas).count();

                double laikas_total = laikas_nuskaitymas + laikas_rikiavimas + laikas_padalijimas + laikas_irasymas;

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
