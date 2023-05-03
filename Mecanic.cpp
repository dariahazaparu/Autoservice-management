//
// Created by Daria on 3/24/2021.
//

#include "Mecanic.h"


double Mecanic::getCoeficient() const {
    return coeficient;
}

Mecanic::Mecanic(const std::string &nume, const std::string &prenume, const Data &d, const Data &a) : Angajat(nume,
                                                                                                              prenume,
                                                                                                              d, a) {
    coeficient = 1.5;
}

void Mecanic::afisare(std::ostream &o) {
    Angajat::afisare(o);
    o << "\n\tRole: Mechanic";
}
