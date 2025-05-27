# Game_Of_Life

In fisierul `Game_Of_Life.c` se primeste un numar de argumente, acestea fiind numele fisierelor de input.
In cod se creeaza un fisier nou in care se inlocuieste `in` cu `out` pentru fisierul de output.

## Functiile principale din `main`

- `setup()`
- `task_cells()`

---

### `setup()`

Se citesc patru valori:
- numarul taskului,
- numarul de linii,
- numarul de coloane,
- numarul de generatii ce trebuiesc simulate.

Se citeste matricea si se adauga coordonatele celulelor vii intr-o lista din stiva.

---

### `task_cells()`

Se afiseaza tabla in functie de numarul taskului:
- pentru taskurile 1 si 3, sub forma unei matrici;
- pentru taskul 2, sub forma unei liste de coordonate.

Daca generatia curenta este egala cu numarul de generatii ce trebuie simulate, executia se opreste.

Se genereaza un nod nou in stiva si se adauga in lista elementele care se modifica pentru generatia urmatoare.
Regula de modificare se aplica in functie de task:
- pentru taskurile 1 si 2, se foloseste regula originala;
- pentru taskurile 3 si 4, regula alternativa si o regula originala, in ordinea aceasta.

Dupa adaugarea noilor elemente in lista, se apeleaza din nou functia `task_cells()` cu lista noua creata.
Acest mecanism permite apelarea recursiva si elimina necesitatea unei structuri suplimentare de tip arbore binar pentru a simula si afisa elementele, stiva de recursivitate si cea pentru listele de coordonate fiind suficiente.

---

### Taskul 4

Taskul 4 necesita determinarea celui mai lung lant Hamiltonian din generatia curenta.  
In functia `task_cells()`, in locul afisarii obisnuite, se creeaza o matrice cu starea curenta a tablei si se apeleaza functia `LongestHamiltonian()` din fisierul `graph.c`, care afiseaza lantul si lungimea acestuia.

---

## Fisierul `graph.c`

In `graph.c` se parcurge intreaga matrice si se creeaza o lista de liste.

In fiecare lista se salveaza toate coordonatele din fiecare componenta conexa, denumita in cod „insula”, deoarece aceste componente nu sunt conectate intre ele – similar cu doua insule separate de apa.

Se parcurge vectorul de insule:
- se sorteaza lexicografic fiecare set de coordonate din insula. 
- se verifica daca se poate forma un lant Hamiltonian de lungime maxima, in cazul in care nu se poate, se verifica cu urmatoarele coordonate din lista insulei curente.

Daca se gaseste un astfel de lant:
- cautarea pentru respectiva insula se opreste;
- daca lantul Hamiltonian gasit este mai lung decat cel mai lung lant identificat pana atunci, acesta este salvat.

Se continua cautarea pentru celelalte insule.

---

### Task Bonus

Fisierul de input a taskului bonus este formatat in modul urmator:
```
"Numar Task (5)"
"Numar linii" "Numar coloane"
"Numar generatii"
listele de la task 2
matricea ultimei generatii
```

Fisierul de output a taskului bonus este formatat in modul urmator:
```
matricea generatiei 0

```

---
Pentru task-ul bonus:
- a trebuit sa pot citi listele de la task 2 si a le adauga in stiva, asadar, am facut o functie numita list2list ce transforma lista afisata in fisierul input intr-o lista din stiva.
- Dupa transformarea tuturor listelor, se adauga si matricea intr-o lista noua
- La final se afiseaza identic ca la task 1 si 3 matricea rezultata

---


### Functii explicate


---

### Game_Of_Life.c

## add_in_list()
- adauga un set de coordonate "l" si "c" intr-o lista

## in_list()
- cauta un set de coordonate "l" si "c" dintr-o lista (cautare binara deoarece acestea sunt adaugate in ordine lexicografica"

## is_alive()
- apeleaza functia `in_list()` pentru fiecare element din stiva pana la o anumita generatie si numara de cate ori a fost gasit
- aceasta suma poate fii interpretata ca numarul de schimbari a unei celule, asadar o suma para reprezinta starea moarta a celulei, iar suma impara reprezinta starea vie a celulei

## neighbour_count()
- apeleaza functia `is_alive()` pentru toti vecinii coordonatei "l" si "c", returnant numarul vecinilor vii

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

### graph.c

## GetValue()
- retuneaza 0 daca elementul din matrice cu linia "l" si coloana "c" este in afara matricei
- altfel returneaza valoarea elementului

## add_in_vector()
- adauga linia "l" si coloana "c" in vector

## floodSave()
- este un algoritm oarecare de `Fill()` care salveaza coordonatele "umplute" intr-un vector
- schimba toate elementele din insula din care fac parte coordonatele "l" si "c"
- din valoarea "original" in valoarea "new",

## getIslands()
- returneaza un Vector de Vectori cu toate coodonatele din fiecare insula, folosindu-se de functia `floodSave()`

## Hamiltonian()
- folosind recursivitate, backtracking si bruteforce adauga coordonatele lantului Hamiltonian intr-un vector, returnand:
-  1 daca lantul curent este de Hamiltonian
-  0 daca coordonatele sunt invalide
-  -1 daca nu s-a gasit un lant Hamiltonian

## sortVector()
- sorteaza un vector lexicografic in functie de linii, si dupa de coordonate

## LongestHamiltonian()
- apeleaza `getIslands()` pentru a face rost de lista cu insule
- parcurge fiecare insula
- apeleaza Hamiltonian pentru fiecare element din insula respectiva pana la gasirea unui astfel de lant
- compara lantul gasit cu cel mai lung si il salveaza daca acesta este mai lung
- la final afiseaza lantul cel mai lung si lungimea acestuia

---
