//
// Created by Daria on 3/25/2021.
//

#include <ctime>
#include "Autobuz.h"

Autobuz::Autobuz(int NrKm, int Fabricatie, bool Diesel, int NrLoc) :
    Masina(NrKm, Fabricatie, Diesel), nr_loc(NrLoc) {}

double Autobuz::asigurare(bool discount) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int an_curent = 1900 + ltm->tm_year;
    int vechime = an_curent - fabricatie;
    double de_platit = vechime * 200;

    if (nr_km > 200000)
        de_platit += 1000;
    else if (nr_km > 100000)
        de_platit += 500;

    if(diesel)
        de_platit += 1000;

    if(discount)
        de_platit *= 0.9;
    return de_platit;
}
//
//int Autobuz::discount_asigurare() {
//    return 0;
//}
