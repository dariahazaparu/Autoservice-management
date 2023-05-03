//
// Created by Daria on 3/25/2021.
//

#include <ctime>
#include <iostream>
#include "Standard.h"

Standard::Standard(int NrKm, int Fabricatie, bool Diesel, bool Manual) :
        Masina(NrKm, Fabricatie, Diesel), manual(Manual) {}

double Standard::asigurare(bool discount) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int vechime = 1900 + ltm->tm_year - fabricatie;
    double de_platit = vechime * 100;

    if (nr_km > 200000)
        de_platit += 500;

    if(diesel)
        de_platit += 500;

    if(discount) {
        de_platit *= 0.95;
    }
    return de_platit;
}


