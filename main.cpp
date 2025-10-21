#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>
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
        cout << "5. Sugeneruoti atsitiktinius studentu failus" << endl;
        cout << "6. Padalinti studentus i grupes ir issaugoti i failus" << endl;
        cout << "7. Atlikti spartos analize skirtingo dydzio failams" << endl;
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

        case 4: {
            auto start = chrono::high_resolution_clock::now();
            skaityti_is_failo(grupe, "studentai_100000.txt");
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            cout << "Duomenu nuskaitymas uztruko: " << duration << " ms\n";
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
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            cout << "Failo generavimas uztruko: " << duration << " ms\n";
            break;
        }

        case 6: {
            auto start_split = chrono::high_resolution_clock::now();
            StudentGroups groups = padalinti_studentus(grupe);
            auto end_split = chrono::high_resolution_clock::now();
            auto duration_split = chrono::duration_cast<chrono::milliseconds>(end_split - start_split).count();
            cout << "Studentu rusiavimas uztruko: " << duration_split << " ms\n";

            auto start_save = chrono::high_resolution_clock::now();
            issaugoti_i_faila(groups.kietiakiai, "kietiakiai.txt");
            issaugoti_i_faila(groups.vargsiukai, "vargsiukai.txt");
            auto end_save = chrono::high_resolution_clock::now();
            auto duration_save = chrono::duration_cast<chrono::milliseconds>(end_save - start_save).count();
            cout << "Surusiuotu studentu issaugojimas i failus uztruko: " << duration_save << " ms\n";

            cout << "Studentai issaugoti i 'kietiakiai.txt' ir 'vargsiukai.txt'" << endl;
            break;
        }

        case 7: {
            vector<long long> failu_dydziai = {1000, 10000, 100000, 1000000, 10000000};

            for (auto n : failu_dydziai) {
                vector<Studentas> laikina_grupe;
                string failo_vardas = "studentai_" + to_string(n) + ".txt";

                auto start_total = chrono::high_resolution_clock::now();

                // Nuskaitymas
                auto start_read = chrono::high_resolution_clock::now();
                skaityti_is_failo(laikina_grupe, failo_vardas);
                auto end_read = chrono::high_resolution_clock::now();
                chrono::duration<double> readTime = end_read - start_read;

                // Rūšiavimas
                auto start_split = chrono::high_resolution_clock::now();
                StudentGroups groups = padalinti_studentus(laikina_grupe);
                auto end_split = chrono::high_resolution_clock::now();
                chrono::duration<double> sortTime = end_split - start_split;

                // Vargšiukai
                auto start_save_vargsiukai = chrono::high_resolution_clock::now();
                issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + to_string(n) + ".txt");
                auto end_save_vargsiukai = chrono::high_resolution_clock::now();
                chrono::duration<double> writeVargsiukaiTime = end_save_vargsiukai - start_save_vargsiukai;

                // Kietekai
                auto start_save_kietekai = chrono::high_resolution_clock::now();
                issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + to_string(n) + ".txt");
                auto end_save_kietekai = chrono::high_resolution_clock::now();
                chrono::duration<double> writeKietekaiTime = end_save_kietekai - start_save_kietekai;

                auto end_total = chrono::high_resolution_clock::now();
                chrono::duration<double> totalTime = end_total - start_total;

                // Išvedimas gražiai per naujas eilutes
                cout << "\nFailo su " << n << " irasu nuskaitymo laikas: "
                     << fixed << setprecision(4) << readTime.count() << " s" << endl;

                cout << n << " irasu rusiavimo didejimo tvarka laikas: "
                     << fixed << setprecision(4) << sortTime.count() << " s" << endl;

                cout << n << " irasu vargsiuku irasymo i faila laikas: "
                     << fixed << setprecision(4) << writeVargsiukaiTime.count() << " s" << endl;

                cout << n << " irasu kieteku irasymo i faila laikas: "
                     << fixed << setprecision(4) << writeKietekaiTime.count() << " s" << endl;

                cout << "Bendras laikas: "
                     << fixed << setprecision(4) << totalTime.count() << " s" << endl;
            }

            break;
        }

        default:
            cout << "Neteisingas pasirinkimas." << endl;
        }

    } while (pasirinkimas != 3);

    return 0;
}
