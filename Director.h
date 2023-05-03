//
// Created by Daria on 3/24/2021.
//

#ifndef ESSENSYS_DIRECTOR_H
#define ESSENSYS_DIRECTOR_H


#include "Angajat.h"

class Director: public Angajat {
public:
    Director(const std::string &nume, const std::string &prenume,
            const Data &d, const Data &a );

    void afisare(std::ostream &o) override;
    double getCoeficient() const override;
};


#endif //ESSENSYS_DIRECTOR_H
