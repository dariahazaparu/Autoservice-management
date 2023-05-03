//
// Created by Daria on 3/24/2021.
//

#ifndef ESSENSYS_GESTIONARE_ANGAJATI_H
#define ESSENSYS_GESTIONARE_ANGAJATI_H


#include <vector>
#include "Angajat.h"

class Gestionare_angajati {
private:
    std :: vector<Angajat*> angajati;
public:
    const std::vector<Angajat *> &getAngajati() const;

private:
    static bool instanceFlag;
    static Gestionare_angajati *single;
    Gestionare_angajati();

public:
    static Gestionare_angajati* getInstance();
    ~Gestionare_angajati()
    {
        instanceFlag = false;
    }

    void adauga(Angajat* angajat);
    void sterge(int id);
    void afisare();
    void editare(int id);
    double salariu (int id);

    bool deschis();
};


#endif //ESSENSYS_GESTIONARE_ANGAJATI_H
