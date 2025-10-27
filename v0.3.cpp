#include "Funkcijos_list.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>

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
        cout << "7. Automatizuotas testas (5 failai)" << endl;
        cout << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        switch(pasirinkimas) {
        case 1: {
            Studentas s = stud_iv();
            grupe.push_back(s);
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
            spausdinti_grupe(grupe);
            break;
        }
        case 3:
            cout << "Programa baigta." << endl;
            break;

        case 4: {
            cout << "Iveskite failo pavadinima: ";
            cin >> fail;
            auto start = chrono::high_resolution_clock::now();
            skaityti_is_failo(grupe, fail);
            auto end = chrono::high_resolution_clock::now();
            cout << "Nuskaitymas uztruko: "
                 << chrono::duration<double>(end - start).count() << " s\n";
            break;
        }
        case 5: {
            long long n; int nd;
            cout << "Kiek studentu sugeneruoti? ";
            cin >> n;
            cout << "Kiek ND kiekvienam? ";
            cin >> nd;
            auto start = chrono::high_resolution_clock::now();
            generuoti_studentu_faila(n, nd);
            auto end = chrono::high_resolution_clock::now();
            cout << "Sugeneruota per: "
                 << chrono::duration<double>(end - start).count() << " s\n";
            break;
        }
        case 6: {
            cout << "Failo pavadinimas: ";
            cin >> fail;
            skaityti_is_failo(grupe, fail);
            auto start = chrono::high_resolution_clock::now();
            StudentGroups g = padalinti_studentus(grupe);
            auto end = chrono::high_resolution_clock::now();
            double padalijimo = chrono::duration<double>(end - start).count();

            auto startW = chrono::high_resolution_clock::now();
            issaugoti_i_faila(g.kietiakiai, "kietiakiai_" + fail);
            issaugoti_i_faila(g.vargsiukai, "vargsiukai_" + fail);
            auto endW = chrono::high_resolution_clock::now();
            double irasymo = chrono::duration<double>(endW - startW).count();

            cout << "Padalijimo laikas: " << padalijimo << " s\n";
            cout << "Irasymo laikas: " << irasymo << " s\n";
            break;
        }
        case 7: {
    vector<long long> sizes = {1000, 10000, 100000, 1000000, 10000000};
    cout << fixed << setprecision(3);

    for (auto n : sizes) {
        cout << "\n--- Testuojama su failu studentai_" << n << ".txt ---\n";
        string fail_name = "studentai_" + to_string(n) + ".txt";
        list<Studentas> test_grupe;

        // 🔹 Nuskaitymas į list
        auto start_nuskaitymas = chrono::high_resolution_clock::now();
        skaityti_is_failo(test_grupe, fail_name);   // perrašyta funkcija Funkcijos_list.cpp
        auto end_nuskaitymas = chrono::high_resolution_clock::now();
        double laikas_nuskaitymas = chrono::duration<double>(end_nuskaitymas - start_nuskaitymas).count();

        if (test_grupe.empty()) {
            cout << "Failas " << fail_name << " tuščias arba nepavyko nuskaityti.\n";
            continue;
        }

        // 🔹 Rikiavimas (naudojamas list.sort)
        auto start_rikiavimas = chrono::high_resolution_clock::now();
        test_grupe.sort([](const Studentas& a, const Studentas& b) {
            return a.gal_rezultatas < b.gal_rezultatas;
        });
        auto end_rikiavimas = chrono::high_resolution_clock::now();
        double laikas_rikiavimas = chrono::duration<double>(end_rikiavimas - start_rikiavimas).count();

        // 🔹 Padalijimas į dvi grupes (funkcija su list)
        auto start_padalijimas = chrono::high_resolution_clock::now();
        StudentGroups groups = padalinti_studentus(test_grupe);
        auto end_padalijimas = chrono::high_resolution_clock::now();
        double laikas_padalijimas = chrono::duration<double>(end_padalijimas - start_padalijimas).count();

        // 🔹 Įrašymas į failus
        auto start_irasymas = chrono::high_resolution_clock::now();
        issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + to_string(n) + ".txt");
        issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + to_string(n) + ".txt");
        auto end_irasymas = chrono::high_resolution_clock::now();
        double laikas_irasymas = chrono::duration<double>(end_irasymas - start_irasymas).count();

        // 🔹 Bendra laiko suvestinė
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
            cout << "Neteisingas pasirinkimas!\n";
        }
    } while (pasirinkimas != 3);

    return 0;
}
