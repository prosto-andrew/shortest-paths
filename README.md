#### Tema: Nejkratší cesty mezi všemi vrcholy (shortest paths)
---
- Shortest-path je program pro vyhledávání nejkratshich cest ve grafu pomoci algoritmu Dijkstry.
- Pro tuto aplikaci jsou přípravena data (1-dijkstra.txt), obsahující inicializační daty.
---

#### Format vstupních dat
---
- Pro data jsem vytvořil format:
```
    vertexes    // znamená, že po něm jdou vrcholy
    1 Red       // číslo označující id AND string označující jmeno vrcholu
    2 Blue
    a tak dalé
    edges    // znamená, že po něm jdou hrany
    0 1 5   // číslo označující zdroj, cíl, hrany
    a tak dalé
```
---

#### Implementace
---
- Tento program může běžet ve dvou režimech: s pouze jedním vláknem a s více vlákny.
- Na začátku program načte data z textového souboru a vytváří dva vektory s vrcholy (vertex) a hranami(edge), pak vytváří graph.
- Při používání více vláken postupuje stejným způsobem jako při jednom vlákně, jenže počita minimalní cestý pro každy vrchol ve vlasthim vlakně.
- Pro simulaci naročných vupočtů použil jsem tento řadek:
    ```
    std::this_thread::sleep_for(0.5s);
    ```
---

#### Build and Run

jděte do složky "/shortest-path" a spustit z terminálu tyto řadky

```bash
- cmake CMakeLists.txt
- make
- ./shortest-paths -opt filename.txt
```
 kde **opt** je jedním z těchto možností:
 
* `-help`  (pomoc)  
* `-one`   (jednovláknový režim)  
* `-multi` (vicevláknový režim)
* `filename` (název souboru)

WARNING! 
After building the project through the terminal, a problem with multi-threaded mode may occur.
To fix this, delete this fragment "../" in path of file in the following lines:
```
// BEFORE

dijkstra.cpp(line54) in method createFile()
ofstream outfile("../temp_files/" + to_string(number) + ".txt");

dijkstra.cpp(line101) in method createOutputWithShorterPathTo()
ofstream outfile("../temp_files/" + to_string(number) + ".txt");

main.cpp(line59) in method multiThread()
string way = "../temp_files/" + to_string(j) + ".txt";

// AFTER

dijkstra.cpp(line54) in method createFile()
ofstream outfile("temp_files/" + to_string(number) + ".txt");

dijkstra.cpp(line101) in method createOutputWithShorterPathTo()
ofstream outfile("temp_files/" + to_string(number) + ".txt");

main.cpp(line59) in method multiThread()
string way = "temp_files/" + to_string(j) + ".txt";
```
---


#### Měření
---
Měření proběhlo vůči kódu v kommitu 667060ca na počítači s následujicí parametry:
- 8GB operační paměti(DDR5)
- procesor Intel CORE i7 (5. generace, 4 jáder )
- SSD


##### Výstup z měření
- [Jednovláknový program](https://gitlab.fel.cvut.cz/B191_B6B36PJC/zhikuand/blob/master/images/single.png) :
```graf o 5 vrcholech běžel 0 ms
  graf o 100 vrcholech běžel 781 ms
  graf o 152 vrcholech běžel 2521 ms
  graf o 200 vrcholech běžel 5815 ms
  graf o 300 vrcholech běžel 18599 ms
  graf o 800 vrcholech běžel 337466 ms
```
- [Vícevláknový program běžel](https://gitlab.fel.cvut.cz/B191_B6B36PJC/zhikuand/blob/master/images/multi.png) :
```
  graf o 5 vrcholech běžel 0 ms
  graf o 100 vrcholech běžel 376 ms
  graf o 152 vrcholech běžel 1316 ms
  graf o 200 vrcholech běžel 2883 ms
  graf o 300 vrcholech běžel 9902 ms
  graf o 800 vrcholech běžel 178560 ms
```
---