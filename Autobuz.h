//
// Created by Daria on 3/25/2021.
//

#ifndef ESSENSYS_AUTOBUZ_H
#define ESSENSYS_AUTOBUZ_H


#include "Masina.h"

class Autobuz : public Masina {
private:
    int nr_loc;
public:
    Autobuz(int NrKm, int Fabricatie, bool Diesel, int NrLoc);
    double asigurare(bool discount = false) override;
//    int discount_asigurare() override;
};


#endif //ESSENSYS_AUTOBUZ_H
