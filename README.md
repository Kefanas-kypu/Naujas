# Studentų programos testavimas – v0.3

## Testavimo sistema

Šiame tyrime programos veikimas buvo matuojamas naudojant šią sistemą:

| Komponentas           | Aprašymas                                                      |
|-----------------------|---------------------------------------------------------------|
| **CPU**               | AMD Ryzen 7 PRO 4750U with Radeon Graphics (1.70 GHz)         |
| **RAM**               | 16.0 GB (15.3 GB usable)                                      |
| **Diskas**            | SSD                                                            |
| **Operacinė sistema** | Windows 10                                                    |

---

## Testavimo metodika

1. Programos veikimas buvo tikrinamas tiek su `std::vector<Studentas>`, tiek su `std::list<Studentas>`.  
2. Rankinio įvedimo metu programa išveda kiekvieno **Studentas** objekto atminties adresą:
   
   ![Rankinio įvedimo išvedimas su objekto adresu](Objekto_adresas.png)
3. Matavimai apėmė:
   - studentų nuskaitymą iš pradinio failo;
   - studentų rikiavimą didėjimo tvarka;
   - studentų padalijimą į dvi kategorijas;
   - duomenų įrašymą į failus;
   - bendrą programos vykdymo laiką.  
4. Kiekvienam failui buvo atlikti keli matavimai ir pateikti jų **vidurkiai**, kad rezultatai būtų patikimesni.

---

## Rezultatai – std::list<Studentas>

Toliau pateikiami testavimo rezultatai, kai konteineriui buvo naudojamas **std::list<Studentas>**.  

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_1000     | 0.007        | 0.000       | 0.001        | 0.008    | **0.017**          |
| studentai_10000    | 0.034        | 0.003       | 0.012        | 0.067    | **0.116**          |
| studentai_100000   | 0.327        | 0.056       | 0.133        | 0.611    | **1.127**          |
| studentai_1000000  | 3.379        | 0.970       | 1.411        | 6.839    | **12.620**         |
| studentai_10000000 | 34.220       | 15.929      | 14.842       | 51.843   | **116.233**        |

![List konteinerio testų išvedimas](Testavimas_list.png)

### Pastabos

- Programos laikas didėja proporcingai įrašų kiekiui, tačiau nuo 1 mln. įrašų pastebima, kad daugiausia laiko užima **įrašymo į failą** procesas.  
- **List** konteineris užima daugiau laiko **padalijimo** etape, nes prieiga prie elementų nėra tiesioginė.  
- Rikiavimo operacija vis dar išlieka gana efektyvi, nes `std::list` turi savo vidinį `sort()` metodą.

---

## Rezultatai – std::vector<Studentas>

Toliau pateikiami testavimo rezultatai, kai konteineriui buvo naudojamas **std::vector<Studentas>**.  

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_1000     | 0.005        | 0.001       | 0.000        | 0.009    | **0.015**          |
| studentai_10000    | 0.022        | 0.018       | 0.005        | 0.066    | **0.110**          |
| studentai_100000   | 0.203        | 0.235       | 0.047        | 0.623    | **1.106**          |
| studentai_1000000  | 1.996        | 3.073       | 0.513        | 5.796    | **11.574**         |
| studentai_10000000 | 21.078       | 38.997      | 4.927        | 48.976   | **113.979**        |

### Pastabos

- **Vector** konteinerio atveju rikiavimas trunka ilgiau nei `list`, ypač kai duomenų kiekis labai didelis.  
  Taip yra todėl, kad `std::sort` turi dirbti su tęstine atmintimi ir reikalauja papildomo elementų kopijavimo.  
- **Padalijimas ir nuskaitymas** vyksta greičiau nei `list`, nes `vector` leidžia tiesioginę prieigą prie elementų.  
- Kaip ir `list` atveju, daugiausia laiko vis tiek užima **failų įrašymas**.

---

## Apibendrinimas

- **Rikiavimas:** `list` veikia greičiau nei `vector` su dideliais duomenų kiekiais.  
- **Padalijimas / nuskaitymas:** `vector` yra spartesnis dėl tęstinės atminties struktūros.  
- **Įrašymas:** abiem atvejais I/O (skaitymo / rašymo) procesas tampa ribojančiu veiksniu.  
- **Bendras laikas:** abu konteineriai elgiasi panašiai iki ~1 mln. įrašų, bet su 10 mln. įrašų `vector` tampa lėtesnis dėl rikiavimo sąnaudų.

---

## Vizualizacija

Kitoje ataskaitos dalyje galima pateikti grafikus (pvz., su Excel ar Python), kurie aiškiai parodytų skirtumus tarp `list` ir `vector` konteinerių skirtingo dydžio failuose.
