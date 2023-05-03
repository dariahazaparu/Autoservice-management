//
// Created by Daria on 3/25/2021.
//

#ifndef ESSENSYS_STANDARD_H
#define ESSENSYS_STANDARD_H


#include "Masina.h"

class Standard : public Masina  {
private:
    bool manual;
public:
    Standard(int NrKm, int Fabricatie, bool Diesel, bool Manual);
    double asigurare(bool discount = false) override;
//    int discount_asigurare() override ;

};


#endif //ESSENSYS_STANDARD_H
