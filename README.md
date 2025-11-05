# Skirtingų strategijų analizės programa

## Strategijų tyrimas

Programa turi dvi strategijas studentų padalijimui pagal galutinį rezultatą:  

| Strategija | Aprašymas | Panaudota funkcija |
|------------|-----------|------------------|
| Strategija 1 | Padalijimas į kietakius ir vargšiukus pagal galutinį rezultatą >= 5  | `strategija1_list/strategija1_vector` |
| Strategija 2 | Padalijimas naudojant `erase` funkciją, kuri pašalina vargšiukus iš studentų failo | `strategija2_list/strategija2_vector` |

### Strategijos 1 pavyzdys

 Toliau pateikiami testavimo rezultatai, kai konteineriui buvo naudojamas **std::list<Studentas>**.  

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_1000     | 0.007        | 0.000       | 0.001        | 0.008    | **0.017**          |
| studentai_10000    | 0.034        | 0.003       | 0.012        | 0.067    | **0.116**          |
| studentai_100000   | 0.327        | 0.056       | 0.133        | 0.611    | **1.127**          |
| studentai_1000000  | 3.379        | 0.970       | 1.411        | 6.839    | **12.620**         |
| studentai_10000000 | 34.220       | 15.929      | 14.842       | 51.843   | **116.233**        |

![List konteinerio testų išvedimas](Testavimas_list.png)


Toliau pateikiami testavimo rezultatai, kai konteineriui buvo naudojamas **std::vector<Studentas>**.  

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_1000     | 0.005        | 0.001       | 0.000        | 0.009    | **0.015**          |
| studentai_10000    | 0.022        | 0.018       | 0.005        | 0.066    | **0.110**          |
| studentai_100000   | 0.203        | 0.235       | 0.047        | 0.623    | **1.106**          |
| studentai_1000000  | 1.996        | 3.073       | 0.513        | 5.796    | **11.574**         |
| studentai_10000000 | 21.078       | 38.997      | 4.927        | 48.976   | **113.979**        |
