//
// Created by Daria on 3/25/2021.
//

#include <ctime>
#include "Camion.h"

Camion::Camion(int NrKm, int Fabricatie, bool Diesel, int Tonaj) :
    Masina(NrKm, Fabricatie, Diesel), tonaj(Tonaj) {}

double Camion::asigurare(bool discount) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int an_curent = 1900 + ltm->tm_year;
    int vechime = an_curent - fabricatie;
    double de_platit = vechime * 300;

    if (nr_km > 800000)
        de_platit += 700;

    if(discount)
        de_platit *= 0.85;
    return de_platit;
}

//int Camion::discount_asigurare() {
//    return 0;
//}
