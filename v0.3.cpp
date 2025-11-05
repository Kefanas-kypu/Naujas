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
        cout << "8. Lyginti strategijas" << endl;
        cout << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        switch(pasirinkimas) {
case 1: {
    Studentas s = stud_iv();
    std::cout << "Objekto adresas: " << &s << std::endl;
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
            cout << "Kiek ND kiekvienam studentui? ";
            cin >> nd;
            auto start = chrono::high_resolution_clock::now();
            generuoti_studentu_faila(n, nd);
            auto end = chrono::high_resolution_clock::now();
            cout << "Sugeneruota per: "
                 << chrono::duration<double>(end - start).count() << " s\n";
            break;
        }
        case 6: {
    cout << "Iveskite failo pavadinima, kuri norite dalinti: ";
    cin >> fail;

    list<Studentas> grupe;
    skaityti_is_failo(grupe, fail);

    if (grupe.empty()) {
        cout << "Nera studentu faile arba nepavyko nuskaityti." << endl;
        break;
    }

    int rusiavimas;
    cout << "Pagal ka rusioti studentus? (1 - pagal varda, 0 - pagal galutini bala): ";
    cin >> rusiavimas;

    auto start_rusiavimas = chrono::high_resolution_clock::now();

    StudentGroups groups = strategija1_list(grupe);

    if (rusiavimas == 1) {
        groups.kietiakiai.sort([](const Studentas& a, const Studentas& b){
            return a.vardas < b.vardas;
        });
        groups.vargsiukai.sort([](const Studentas& a, const Studentas& b){
            return a.vardas < b.vardas;
        });
    } else {
        groups.kietiakiai.sort([](const Studentas& a, const Studentas& b){
            return a.gal_rezultatas > b.gal_rezultatas;
        });
        groups.vargsiukai.sort([](const Studentas& a, const Studentas& b){
            return a.gal_rezultatas > b.gal_rezultatas;
        });
    }

    auto end_rusiavimas = chrono::high_resolution_clock::now();
    double laikas_rusiavimas = chrono::duration<double>(end_rusiavimas - start_rusiavimas).count();

    size_t pos1 = fail.find_last_of('_');
    size_t pos2 = fail.find_last_of('.');
    string number = (pos1 != string::npos && pos2 != string::npos && pos2 > pos1)
                    ? fail.substr(pos1 + 1, pos2 - pos1 - 1)
                    : "output";

    auto start_irasymas = chrono::high_resolution_clock::now();

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
        skaityti_is_failo(test_grupe, fail_name);  
        auto end_nuskaitymas = chrono::high_resolution_clock::now();
        double laikas_nuskaitymas = chrono::duration<double>(end_nuskaitymas - start_nuskaitymas).count();

        if (test_grupe.empty()) {
            cout << "Failas " << fail_name << " tuščias arba nepavyko nuskaityti.\n";
            continue;
        }

        auto start_rikiavimas = chrono::high_resolution_clock::now();
        test_grupe.sort([](const Studentas& a, const Studentas& b) {
            return a.gal_rezultatas < b.gal_rezultatas;
        });
        auto end_rikiavimas = chrono::high_resolution_clock::now();
        double laikas_rikiavimas = chrono::duration<double>(end_rikiavimas - start_rikiavimas).count();

        auto start_padalijimas = chrono::high_resolution_clock::now();
        StudentGroups groups = strategija1_list(test_grupe);
        auto end_padalijimas = chrono::high_resolution_clock::now();
        double laikas_padalijimas = chrono::duration<double>(end_padalijimas - start_padalijimas).count();

        auto start_irasymas = chrono::high_resolution_clock::now();
        issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + to_string(n) + ".txt");
        issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + to_string(n) + ".txt");
        auto end_irasymas = chrono::high_resolution_clock::now();
        double laikas_irasymas = chrono::duration<double>(end_irasymas - start_irasymas).count();

        double laikas_total = laikas_nuskaitymas + laikas_rikiavimas + laikas_padalijimas + laikas_irasymas;

        cout << "Failo nuskaitymo laikas: " << laikas_nuskaitymas << " s\n";
        cout << "Rikiavimo laikas: " << laikas_rikiavimas << " s\n";
        cout << "Padalijimo i vargsiukus ir kietakius laikas: " << laikas_padalijimas << " s\n";
        cout << "Irasymo laikas i failus laikas: " << laikas_irasymas << " s\n";
        cout << "Bendras laikas: " << laikas_total << " s\n";
    }
    break;
}
   case 8: {
    int strategija;
    std::cout << "Pasirinkite strategija:\n";
    std::cout << "1 - Strategija 1 (grupavimas i vargsiukus ir kietiakus)\n";
    std::cout << "2 - Strategija 2 (erase, vargsiukai isbraukiami)\n";
    std::cout << "Jusu pasirinkimas: ";
    std::cin >> strategija;

    auto start = std::chrono::high_resolution_clock::now();

    if (strategija == 1) {
        std::cout << "Vykdoma strategija 1...\n";
        vykdyti_strategija1();
    } 
    else if (strategija == 2) {
    std::cout << "Vykdoma strategija 2...\n";

    std::vector<long long> sizes = {1000, 10000, 100000, 1000000, 10000000};
    for (auto n : sizes) {
        std::string fail_name = "studentai_" + std::to_string(n) + ".txt";
        std::list<Studentas> grupe;
        std::list<Studentas> vargsiukai;

        auto start_total = std::chrono::high_resolution_clock::now();

        auto start_read = std::chrono::high_resolution_clock::now();
        skaityti_is_failo(grupe, fail_name);
        auto end_read = std::chrono::high_resolution_clock::now();

        if (grupe.empty()) {
            std::cout << "Failas " << fail_name << " tuščias arba nepavyko nuskaityti.\n";
            continue;
        }

        auto start_sort = std::chrono::high_resolution_clock::now();
        grupe.sort([](const Studentas& a, const Studentas& b){
            return a.gal_rezultatas > b.gal_rezultatas;
        });
        auto end_sort = std::chrono::high_resolution_clock::now();

        auto start_split = std::chrono::high_resolution_clock::now();
        strategija2_list(grupe, vargsiukai);
        auto end_split = std::chrono::high_resolution_clock::now();

        auto start_write = std::chrono::high_resolution_clock::now();
        issaugoti_i_faila(grupe, "studentai_" + std::to_string(n) + ".txt");
        issaugoti_i_faila(vargsiukai, "vargsiukai_" + std::to_string(n) + ".txt");
        auto end_write = std::chrono::high_resolution_clock::now();

        auto end_total = std::chrono::high_resolution_clock::now();

        std::cout << "--- Testuojama su failu " << fail_name << " ---\n";
        std::cout << "Failo nuskaitymo laikas: " 
                  << std::chrono::duration<double>(end_read - start_read).count() << " s\n";
        std::cout << "Rikiavimo laikas: " 
                  << std::chrono::duration<double>(end_sort - start_sort).count() << " s\n";
        std::cout << "Padalijimo laikas: " 
                  << std::chrono::duration<double>(end_split - start_split).count() << " s\n";
        std::cout << "Irasymo i failus laikas: " 
                  << std::chrono::duration<double>(end_write - start_write).count() << " s\n";
        std::cout << "Bendras laikas: " 
                  << std::chrono::duration<double>(end_total - start_total).count() << " s\n\n";
    }
}
    else {
        std::cout << "Neteisingas pasirinkimas!\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Strategijos vykdymo laikas: "
              << std::chrono::duration<double>(end - start).count() << " s\n";
    break;
}

        default:
            cout << "Neteisingas pasirinkimas!\n";
        }
    } while (pasirinkimas != 3);

    return 0;
}