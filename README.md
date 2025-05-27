# Game_Of_Life

[Detalii](https://site-pa.netlify.app/proiecte/game_of_life/)

## Requirements:
Surse:
- Game_Of_Life.c
- Graph.c
- Graph.h

Instalare compilator:
```
sudo apt update
```
```
sudo apt install build-essential
```
```
gcc --version
```

Compilare:
```
gcc -O2 -Wall Game_Of_Life.c Graph.c -o a.out
```

Rulare:
```
./a.out InputFile/data2.in InputFile/data14.in
```

dupa ./a.out se poate adauga orice denumire, cat timp primele 2 litere din fisierul de input se numeste "In" iar ultimele 2 sunt "in" deoarece sunt inlocuite cu "Out" si "out"
1 sau mai multe argumente
```
InputFisier/informatii.in
OutputFisier/informatii.out
```






Fisierul de input este formatat in modul urmator:
```
1     //numar task
5 13 //numarul de linii si coloane
50    //numarul de generatii
+++++++++++++
+++++++X+++++
++++++++X++++
++++++XXX++++
+++++++++++++
```
---



### Task Bonus

Fisierul de input a taskului bonus este formatat in modul urmator:
```
5
20 50
50
1 1 7 2 6 3 6 4 7
2 2 6 3 6 3 7 4 8
3 2 7 2 8 3 6 3 9
4 2 7 2 8 3 8 4 9
5 2 8 3 7 4 7 5 8
6 3 7 4 7 4 8 5 9
7 3 8 3 9 4 7 4 10
...
48 13 18 13 19 14 19 15 20
49 13 19 14 18 15 18 16 19
50 14 18 15 18 15 19 16 20
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++X+++++++++++++++++++++++++++++
++++++++++++++++++X+X+++++++++++++++++++++++++++++
+++++++++++++++++++XX+++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
```
Numarul taskului
Numarul de linii si coloane
Numarul de generatii
Listele pentru fiecare generatie
Matricea Finala


Fisierul de output a taskului bonus este formatat in modul urmator:
```
++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++X++++++++++++++++++++++++++++++++++++++++++
++++++++X+++++++++++++++++++++++++++++++++++++++++
++++++XXX+++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++

```
Matricea initiala si un spatiu la final

---
Pentru task-ul bonus:
- a trebuit sa pot citi listele de la task 2 si a le adauga in stiva, asadar, am facut o functie numita list2list ce transforma lista afisata in fisierul input intr-o lista din stiva.
- Dupa transformarea tuturor listelor, se adauga si matricea intr-o lista noua
- La final se afiseaza identic ca la task 1 si 3 matricea rezultata

---


### Functii explicate


---

### [Game_Of_Life.c](https://github.com/edi3d3d/Game_Of_Life/blob/main/Game_Of_Life.c)

## add_in_list()
- adauga un set de coordonate "l" si "c" intr-o lista

## in_list()
- cauta un set de coordonate "l" si "c" dintr-o lista (cautare binara deoarece acestea sunt adaugate in ordine lexicografica"

## is_alive()
- apeleaza functia `in_list()` pentru fiecare element din stiva pana la o anumita generatie si numara de cate ori a fost gasit
- aceasta suma poate fii interpretata ca numarul de schimbari a unei celule, asadar o suma para reprezinta starea moarta a celulei, iar suma impara reprezinta starea vie a celulei

## neighbour_count()
- apeleaza functia `is_alive()` pentru toti vecinii coordonatei "l" si "c", returnand numarul vecinilor vii

## printf_cells()
- afiseaza tabla sau lista unei anumite generatii din stiva.
- tabla este afisata folosind functia `is_alive()` pentru fiecare element din matricea de dimensiuni "Numar Linii" x "Numar Coloane"

## list2list()
- adauga o linie a fisierului de input intr-o lista din stiva
  
- citeste numarul generatiei iar apoi un set de 2 numere, linia si coloana
- acestea sunt adaugate la finalul stivei

## setup()
- citeste cele 4 numere initiale din fisierul de input
- initializeaza primul nod din stiva
- in cazul taskului bonus citeste listele si le adauga in stiva
- citeste matricea, adaugand celulele vii in stiva

## update_cells()
- initializeaza nodul curent al stivei
- parcurge matricea de dimensiuni "Numar Linii" x "Numar Coloane"
- in cazul schimbarii starii celulei, coordonatele acestea sunt adaugate in lista nodului curent.  

## task_cells()
- afiseaza tabla
- creaza matricea pentru task 4
- apeleaza functia `update_cells()` cu cele 2 reguli


---

### [graph.c](https://github.com/edi3d3d/Game_Of_Life/blob/main/graph.c)

## GetValue()
- retuneaza 0 daca elementul din matrice cu linia "l" si coloana "c" se afla in afara matricei
- altfel returneaza valoarea elementului

## add_in_vector()
- adauga linia "l" si coloana "c" in vector

## floodSave()
- este un algoritm oarecare de `Fill()` care salveaza coordonatele "umplute" intr-un vector
- schimba toate elementele din insula din care fac parte coordonatele "l" si "c"

## getIslands()
- returneaza un Vector de Vectori cu toate coodonatele din fiecare insula, folosind functia `floodSave()` pe fiecare celula din matrice

## Hamiltonian()
- folosind recursivitate, backtracking si bruteforce adauga coordonatele lantului Hamiltonian intr-un vector, returnand:
-  1 daca lantul curent este de Hamiltonian
-  0 daca coordonatele sunt invalide
- -1 daca nu s-a gasit un lant Hamiltonian

## sortVector()
- sorteaza un vector lexicografic in functie de coordonate

## LongestHamiltonian()
- apeleaza `getIslands()` pentru a face rost de lista cu insule
- parcurge fiecare insula pe rand
- apeleaza Hamiltonian pentru fiecare element din insula respectiva pana la gasirea unui astfel de lant
- compara lantul gasit cu cel mai lung si il salveaza daca acesta este mai lung
- la final afiseaza lantul cel mai lung si lungimea acestuia

---
