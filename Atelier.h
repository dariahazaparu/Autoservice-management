//
// Created by Daria on 3/25/2021.
//

#ifndef ESSENSYS_ATELIER_H
#define ESSENSYS_ATELIER_H

#include <queue>
#include "Masina.h"
#include "Standard.h"
#include "Autobuz.h"
#include "Camion.h"
#include "Angajat.h"

class Atelier {
    std::queue<std :: pair<int, int>> asteptare;
    std::vector<std::priority_queue<std::pair<std::pair<int, int>, int>>> reparatii;
    //1 pt standard, 2 pt masini mari
    std::vector<std::queue<int>> asteptare_ang_standard;
    std::vector<std::queue<std::pair<int, int>>> asteptare_ang_mare;
    static bool instanceFlag;
    static Atelier *single;

    Atelier();

public:
    static Atelier *getInstance();

    void masina_noua(int units);

    Angajat *find(int id);

    void procesare(Standard s, int units);

    void procesare(Autobuz a, int units);

    void procesare(Camion c, int units);

    void afisare();

    void parcurgere(int units);
};


#endif //ESSENSYS_ATELIER_H
