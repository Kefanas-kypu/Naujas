#include "Funkcijos_list.h"
#include <sstream>
#include <random>
#include <algorithm>
#include <chrono>
#include <list>
#include <string>

using namespace std;

double vidurkis(const list<int>& nd) {
    if (nd.empty()) return 0;
    double suma = 0;
    for (auto x : nd) suma += x;
    return suma / nd.size();
}

Studentas stud_iv() {
    Studentas pirmas;
    int sum = 0;
    int laik_paz;

    std::cout << "Iveskite studento duomenis" << std::endl;
    std::cout << "Vardas: ";
    std::cin >> pirmas.vardas;
    std::cout << "Pavarde: ";
    std::cin >> pirmas.pavarde;

    int generuoti;
    std::cout << "Ar pazymius generuoti atsitiktinai? (1 - generuoti, 0 - vesti ranka): ";
    std::cin >> generuoti;

    if (generuoti == 1) {
        int kiek = rand() % 10 + 1;
        for (int i = 0; i < kiek; i++) {
            int random_paz = rand() % 10 + 1;
            pirmas.paz.push_back(random_paz);
            sum += random_paz;
        }
        pirmas.egzaminas = rand() % 10 + 1;
    } else {
        int kl;
        std::cout << "Ar zinote, kiek pazymiu turi studentas? (1 - taip, 0 - ne): ";
        std::cin >> kl;

        if (kl == 0) {
            int laik_paz_local = -1;
            while (laik_paz_local != 0) {
                std::cout << "Iveskite pazymi (arba 0, jei daugiau pazymiu nera): ";
                std::cin >> laik_paz_local;
                if (laik_paz_local != 0) {
                    pirmas.paz.push_back(laik_paz_local);
                    sum += laik_paz_local;
                }
            }
            std::cout << "Iveskite egzamino pazymi: ";
            std::cin >> pirmas.egzaminas;
        } else {
            int kiek_paz;
            std::cout << "Kiek pazymiu turi studentas? ";
            std::cin >> kiek_paz;

            for (int a = 0; a < kiek_paz; a++) {
                std::cout << a + 1 << ": ";
                std::cin >> laik_paz;
                pirmas.paz.push_back(laik_paz);
                sum += laik_paz;
            }
            std::cout << "Iveskite egzamino pazymi: ";
            std::cin >> pirmas.egzaminas;
        }
    }

    int n = pirmas.paz.size();
    if (n == 0)
        pirmas.gal_rezultatas = pirmas.egzaminas;
    else
        pirmas.gal_rezultatas = double(sum) / n * 0.4 + pirmas.egzaminas * 0.6;

    std::vector<int> paz_temp(pirmas.paz.begin(), pirmas.paz.end());
    paz_temp.push_back(pirmas.egzaminas);
    std::sort(paz_temp.begin(), paz_temp.end());

    int kiek = paz_temp.size();
    if (kiek == 0)
        pirmas.mediana = 0.0;
    else if (kiek % 2 != 0)
        pirmas.mediana = double(paz_temp[kiek / 2]);
    else
        pirmas.mediana = double(paz_temp[(kiek - 1) / 2] + paz_temp[kiek / 2]) / 2.0;

    return pirmas;
}



void spausdinti_grupe(const std::list<Studentas>& grupe) {
    if (grupe.empty()) {
        std::cout << "Nera studentu" << std::endl;
        return;
    }

    std::cout << std::setw(10) << std::left << "Vardas" << "|"
              << std::setw(15) << std::right << "Pavarde" << "|"
              << std::setw(20) << std::right << "Galutinis (Vid.)" << "|"
              << std::setw(20) << std::right << "Galutinis (Med.)" << std::endl;
    std::cout << "--------------------------------------------------------------------" << std::endl;

    for (const auto& stud : grupe) {
        std::cout << std::setw(11) << std::left << stud.vardas << "|"
                  << std::setw(15) << std::right << stud.pavarde << "|"
                  << std::fixed << std::setprecision(2) << std::setw(20) << std::right << stud.gal_rezultatas << "|"
                  << std::fixed << std::setprecision(2) << std::setw(20) << std::right << stud.mediana << std::endl;
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

void skaityti_is_failo(list<Studentas>& grupe, const string& failo_vardas) {
    ifstream fd(failo_vardas);
    if (!fd.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << failo_vardas << endl;
        return;
    }

    string eil;
    getline(fd, eil);

    grupe.clear();

    while (getline(fd, eil)) {
        stringstream ss(eil);
        Studentas s;
        ss >> s.vardas >> s.pavarde;

        s.paz.clear();
        int paz;
        while (ss >> paz) {
            s.paz.push_back(paz);
        }

        if (!s.paz.empty()) {
            s.egzaminas = s.paz.back();
            s.paz.pop_back();
        } else {
            s.egzaminas = 0;
        }

        s.gal_rezultatas = 0.4 * vidurkis(s.paz) + 0.6 * s.egzaminas;

        std::vector<int> paz_temp(s.paz.begin(), s.paz.end());
        paz_temp.push_back(s.egzaminas); 
        std::sort(paz_temp.begin(), paz_temp.end());

        int kiek = paz_temp.size();
        if (kiek == 0) {
            s.mediana = 0.0;
        } else if (kiek % 2 != 0) {
            s.mediana = double(paz_temp[kiek / 2]);
        } else {
            s.mediana = double(paz_temp[(kiek - 1) / 2] + paz_temp[kiek / 2]) / 2.0;
        }

        grupe.push_back(s);
    }
}

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

StudentGroups strategija1_list(const list<Studentas>& grupe) {
    StudentGroups groups;

    for (const auto& s : grupe) {
        if (s.gal_rezultatas >= 5.0)
            groups.kietiakiai.push_back(s);
        else
            groups.vargsiukai.push_back(s);
    }
    return groups;
}

void vykdyti_strategija1() {
    vector<long long> sizes = {1000, 10000, 100000, 1000000, 10000000};

    for (auto n : sizes) {
        string fail_name = "studentai_" + to_string(n) + ".txt";
        list<Studentas> test_grupe;

        auto start_nuskaitymas = chrono::high_resolution_clock::now();
        skaityti_is_failo(test_grupe, fail_name);  
        auto end_nuskaitymas = chrono::high_resolution_clock::now();

        if (test_grupe.empty()) {
            cout << "Failas " << fail_name << " tuščias arba nepavyko nuskaityti.\n";
            continue;
        }

        auto start_rikiavimas = chrono::high_resolution_clock::now();
        test_grupe.sort([](const Studentas& a, const Studentas& b) {
            return a.gal_rezultatas < b.gal_rezultatas;
        });
        auto end_rikiavimas = chrono::high_resolution_clock::now();

        auto start_padalijimas = chrono::high_resolution_clock::now();
        StudentGroups groups = strategija1_list(test_grupe);
        auto end_padalijimas = chrono::high_resolution_clock::now();

        auto start_irasymas = chrono::high_resolution_clock::now();
        issaugoti_i_faila(groups.kietiakiai, "kietiakiai_" + to_string(n) + ".txt");
        issaugoti_i_faila(groups.vargsiukai, "vargsiukai_" + to_string(n) + ".txt");
        auto end_irasymas = chrono::high_resolution_clock::now();

        double laikas_nuskaitymas = chrono::duration<double>(end_nuskaitymas - start_nuskaitymas).count();
        double laikas_rikiavimas = chrono::duration<double>(end_rikiavimas - start_rikiavimas).count();
        double laikas_padalijimas = chrono::duration<double>(end_padalijimas - start_padalijimas).count();
        double laikas_irasymas = chrono::duration<double>(end_irasymas - start_irasymas).count();

        cout << "\n--- Testuojama su failu " << fail_name << " ---\n";
        cout << "Failo nuskaitymo laikas: " << laikas_nuskaitymas << " s\n";
        cout << "Rikiavimo laikas: " << laikas_rikiavimas << " s\n";
        cout << "Padalijimo laikas: " << laikas_padalijimas << " s\n";
        cout << "Irasymo i failus laikas: " << laikas_irasymas << " s\n";
        cout << "Bendras laikas: " << laikas_nuskaitymas + laikas_rikiavimas + laikas_padalijimas + laikas_irasymas << " s\n";
    }
}

void strategija2_list(std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end();) {
        if (it->gal_rezultatas < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}


void vykdyti_strategija2() {
    std::vector<long long> sizes = {1000, 10000, 100000, 1000000, 10000000};
    std::cout << std::fixed << std::setprecision(3);

    for (auto n : sizes) {
        std::string fail_name = "studentai_" + std::to_string(n) + ".txt";
        std::list<Studentas> grupe;

        skaityti_is_failo(grupe, fail_name);

        if (grupe.empty()) {
            std::cout << "Failas " << fail_name << " tuščias arba nepavyko nuskaityti.\n";
            continue;
        }

        auto start = std::chrono::high_resolution_clock::now();

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "\n--- Testuojama su failu " << fail_name << " ---\n";
        std::cout << "Strategijos laikas: "
                  << std::chrono::duration<double>(end - start).count() << " s\n";
    }
}

void issaugoti_i_faila(const std::list<Studentas>& grupe, const std::string& failo_vardas) {
    std::ofstream out(failo_vardas, std::ios::trunc); 
    if (!out) {
        std::cout << "Nepavyko sukurti failo: " << failo_vardas << std::endl;
        return;
    }

    out << std::setw(10) << std::left << "Vardas" << "|"
        << std::setw(15) << std::right << "Pavarde" << "|"
        << std::setw(20) << std::right << "Galutinis (Vid.)" << "|"
        << std::setw(20) << std::right << "Galutinis (Med.)" << std::endl;
    out << "--------------------------------------------------------------------" << std::endl;

    for (const auto& stud : grupe) {
        out << std::setw(11) << std::left << stud.vardas << "|"
            << std::setw(15) << std::right << stud.pavarde << "|"
            << std::fixed << std::setprecision(2) << std::setw(20) << std::right << stud.gal_rezultatas << "|"
            << std::fixed << std::setprecision(2) << std::setw(20) << std::right << stud.mediana << std::endl;
    }
}
