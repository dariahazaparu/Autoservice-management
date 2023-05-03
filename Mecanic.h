//
// Created by Daria on 3/24/2021.
//

#ifndef ESSENSYS_MECANIC_H
#define ESSENSYS_MECANIC_H


#include "Angajat.h"

class Mecanic: public Angajat {
public:
    Mecanic(const std::string &nume, const std::string &prenume,
            const Data &d, const Data &a );
    double getCoeficient() const override;
    void afisare(std::ostream &o) override;

};


#endif //ESSENSYS_MECANIC_H
