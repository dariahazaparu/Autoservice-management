//
// Created by Daria on 3/24/2021.
//

#include "Asistent.h"

double Asistent::getCoeficient() const {
    return coeficient;
}

Asistent::Asistent(const std::string &nume, const std::string &prenume, const Data &d, const Data &a) : Angajat(nume,
                                                                                                                prenume,
                                                                                                                d, a) {
    coeficient = 1;

}

void Asistent::afisare(std::ostream &o) {
    Angajat::afisare(o);
    o << "\n\tRole: Assistant";
}
