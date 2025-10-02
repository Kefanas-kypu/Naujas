#include <iostream>
#include <vector>
#include "Funkcijos.h"

using namespace std;

int main() {
    srand(time(0));
    vector<Studentas> grupe;
    int pasirinkimas;

    do {
        cout << "1. Ivesti nauja studenta\n"
             << "2. Atspausdinti rezultatus\n"
             << "3. Iseiti\n"
             << "4. Nuskaityti studentus is failo\n"
             << "6. Padalinti studentus i grupes ir issaugoti i failus\n"
             << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1: grupe.push_back(stud_iv()); break;
            case 2: surusiuoti_pagal_varda(grupe); spausdinti_grupe(grupe); break;
            case 3: cout << "Pabaiga.\n"; break;
            case 4: skaityti_is_failo(grupe, "studentai_1000.txt"); break;
            case 6: {
                StudentGroups groups = padalinti_studentus(grupe);
                issaugoti_i_faila(groups.kietiakiai, "kietiakiai.txt");
                issaugoti_i_faila(groups.vargsiukai, "vargsiukai.txt");
                cout << "Studentai issaugoti i failus.\n";
                break;
            }
            default: cout << "Neteisingas pasirinkimas.\n";
        }
    } while (pasirinkimas != 3);

    return 0;
}
