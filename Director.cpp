//
// Created by Daria on 3/24/2021.
//

#include "Director.h"
#include <iostream>

void Director::afisare(std::ostream &o) {
    Angajat::afisare(o);
    o << "\n\tRole: Director";
}

double Director::getCoeficient() const {
    return coeficient;
}

Director::Director(const std::string &nume, const std::string &prenume, const Data &d, const Data &a) : Angajat(nume,
                                                                                                                prenume,
                                                                                                                d, a) {
    coeficient = 2;
}
