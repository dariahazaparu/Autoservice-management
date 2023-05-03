//
// Created by Daria on 3/24/2021.
//

#ifndef ESSENSYS_ASISTENT_H
#define ESSENSYS_ASISTENT_H


#include "Angajat.h"

class Asistent: public Angajat {
public:
    Asistent(const std::string &nume, const std::string &prenume,
            const Data &d, const Data &a);

    double getCoeficient() const override;
    void afisare(std::ostream &o) override;

};


#endif //ESSENSYS_ASISTENT_H
