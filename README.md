# Game_Of_Life

In fisierul `Game_Of_Life.c` se primeste un numar de argumente, acestea fiind numele fisierelor de input. In cod se creeaza un fisier nou in care se inlocuieste `in` cu `out` pentru fisierul de output.

## Functiile principale din `main`

- `setup()`
- `task_cells()`

---

### `setup()`

Se citesc patru valori:
- numarul taskului,
- numarul de linii,
- numarul de coloane,
- numarul de generatii care trebuie simulate.

Se citeste matricea si se adauga intr-o lista din stiva coordonatele celulelor vii.

---

### `task_cells()`

Se afiseaza tabla in functie de numarul taskului:
- pentru taskurile 1 si 3, sub forma unei matrici;
- pentru taskul 2, sub forma unei liste de coordonate.

Daca generatia curenta este egala cu numarul de generatii ce trebuie simulate, executia se opreste.

Se genereaza un element nou in stiva cu listele de coordonate si se adauga elementele care se modifica pentru generatia urmatoare. Regula de modificare se aplica in functie de task:
- pentru taskurile 1 si 2, se foloseste regula originala;
- pentru taskurile 3 si 4, regula alternativa si o regula originala, in ordinea aceasta.

Dupa adaugarea noilor elemente in liste, se apeleaza din nou functia `task_cells()` cu lista noua creata.  
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
