//
// Created by Daria on 3/25/2021.
//

#ifndef ESSENSYS_CAMION_H
#define ESSENSYS_CAMION_H


#include "Masina.h"

class Camion : public Masina {
private:
    int tonaj;
public:
    Camion(int NrKm, int Fabricatie, bool Diesel, int Tonaj);
    double asigurare(bool discount = false) override;
//    int discount_asigurare() override;
};


#endif //ESSENSYS_CAMION_H
