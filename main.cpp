#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include "Studentas.h"
#include "Funkcijos.h"

using namespace std;

int main() {
    srand(time(0));

    vector<Studentas> grupe;
    int pasirinkimas;

    do {
        cout << "\nKa norite atlikti?" << endl;
        cout << "1. Ivesti nauja studenta" << endl;
        cout << "2. Atspausdinti rezultatus" << endl;
        cout << "3. Iseiti" << endl;
        cout << "4. Nuskaityti studentus is failo" << endl;
        cout << "5. Sugeneruoti atsitiktiniu studentu faila" << endl;
        cout << "6. Padalinti studentus i grupes ir issaugoti i failus" << endl;
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
        case 5: {
            long long n;
            int nd_count;
            cout << "Kiek studentu sugeneruoti? ";
            cin >> n;
            cout << "Kiek namu darbu (ND)? ";
            cin >> nd_count;

            auto start = chrono::high_resolution_clock::now();
            generuoti_studentu_faila(n, nd_count);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            cout << "Sugeneravimas uztruko: " << duration << " ms\n";
            break;
        }
        case 6: {
            StudentGroups groups = padalinti_studentus(grupe);
            issaugoti_i_faila(groups.kietiakiai, "kietiakiai.txt");
            issaugoti_i_faila(groups.vargsiukai, "vargsiukai.txt");
            cout << "Studentai issaugoti i 'kietiakiai.txt' ir 'vargsiukai.txt'" << endl;
            break;
        }
        default:
            cout << "Neteisingas pasirinkimas." << endl;
        }

    } while (pasirinkimas != 3);

    return 0;
}
