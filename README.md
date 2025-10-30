# Studentų programos testavimas – v0.3

## Testavimo sistema

Šiame tyrime programos veikimas buvo matuojamas naudojant šią aparatūrą:

| Komponentas           | Aprašymas                                                      |
|-----------------------|---------------------------------------------------------------|
| **CPU**               | AMD Ryzen 7 PRO 4750U with Radeon Graphics (1.70 GHz)         |
| **RAM**               | 16.0 GB (15.3 GB usable)                                      |
| **Diskas**            | SSD                                                            |
| **Operacinė sistema** | Windows 10                                                    |

> **Pastaba:** visi rezultatai buvo matuojami naudojant tuos pačius failus su 1000, 10000, 100000, 1000000 ir 10000000 įrašų, kaip ir v0.2 versijoje.

---

##  Testavimo metodika

1. Programos veikimas buvo tikrinamas tiek su `std::vector<Studentas>`, tiek su `std::list<Studentas>`.  
2. Matavimai apėmė:
   - studentų rūšiavimą į dvi grupes/kategorijas;
   - duomenų įrašymą į failus;
   - bendrą programos vykdymo laiką.  
3. Kiekvienam failui buvo fiksuojami laikai (`s`) ir, vėliau, bus apskaičiuotas kelių bandymų vidurkis, kad būtų patikimesni rezultatai.

##  Rezultatai – `std::list<Studentas>`

Toliau pateikiami testavimo rezultatai, kai konteineriui buvo naudojamas **`std::list<Studentas>`**.  
Kiekvienas testas buvo kartojamas kelis kartus, o lentelėje pateikti **vidutiniai laikai (sekundėmis)**.

| Failas             | Nuskaitymas (s) | Rikiavimas (s) | Padalijimas (s) | Įrašymas (s) | **Bendras laikas (s)** |
| ------------------ | --------------- | -------------- | --------------- | ------------ | ---------------------- |
| studentai_1000     | 0.007           | 0.000          | 0.001           | 0.008        | **0.017**              |
| studentai_10000    | 0.034           | 0.003          | 0.012           | 0.067        | **0.116**              |
| studentai_100000   | 0.327           | 0.056          | 0.133           | 0.611        | **1.127**              |
| studentai_1000000  | 3.379           | 0.970          | 1.411           | 6.839        | **12.620**             |
| studentai_10000000 | 34.220          | 15.929         | 14.842          | 51.843       | **116.233**            |

---

### Pastabos

- Matyti, kad **programos laikas didėja beveik tiesiškai** didėjant įrašų kiekiui, tačiau po 1 mln. įrašų pradeda ryškėti I/O (įrašymo ir skaitymo) proceso dominavimas.
- **Didžiausia laiko dalis** nuo 100 tūkst. įrašų ir daugiau tenka **failo įrašymui** – šis procesas tampa pagrindiniu siaurąja vieta (bottleneck).
- `list` konteinerio atveju **rikiavimas ir padalijimas** trunka žymiai ilgiau nei mažesnių dydžių failuose, nes elementų prieigos sudėtingumas yra didesnis nei `vector`.

---

> 💡 Kitoje dalyje bus pateikti `std::vector<Studentas>` rezultatai ir tiesioginis jų palyginimas su `list` konteineriu (lentelė + grafikas).


##  Rezultatai – `std::vector<Studentas>`

Toliau pateikiami testavimo rezultatai, kai konteineriui buvo naudojamas **`std::vector<Studentas>`**.  
Kiekvienas testas buvo kartojamas kelis kartus, o lentelėje pateikti **vidutiniai laikai (sekundėmis)**.

| Failas             | Nuskaitymas (s) | Rikiavimas (s) | Padalijimas (s) | Įrašymas (s) | **Bendras laikas (s)** |
| ------------------ | --------------- | -------------- | --------------- | ------------ | ---------------------- |
| studentai_1000     | 0.005           | 0.001          | 0.000           | 0.009        | **0.015**              |
| studentai_10000    | 0.022           | 0.018          | 0.005           | 0.066        | **0.110**              |
| studentai_100000   | 0.203           | 0.235          | 0.047           | 0.623        | **1.106**              |
| studentai_1000000  | 1.996           | 3.073          | 0.513           | 5.796        | **11.574**             |
| studentai_10000000 | 21.078          | 38.997         | 4.927           | 48.976       | **113.979**            |

---

### Pastabos

- `vector` konteinerio atveju **rikiavimas vyksta žymiai greičiau nei `list`**, ypač dideliuose failuose, nes elementai yra saugomi **tęstinėje atminties vietoje** ir `std::sort` gali efektyviai naudoti indeksus.
- Didžiausi laikai ir toliau tenka **įrašymui į failą** – I/O procesas tampa pagrindine laiko sąnaudų dalimi.
- Skirtumas tarp `vector` ir `list` konteinerių ryškiausias **rikiavimo ir padalijimo etapuose**, ypač didesniuose failuose.

---

> 💡 Kitoje dalyje bus pateiktas **tiesioginis `vector` vs `list` palyginimas** lentelėse ir grafikuose, kad būtų galima aiškiai vizualizuoti spartos skirtumus.
