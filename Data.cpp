//
// Created by Daria on 3/25/2021.
//

#include "Data.h"
#include "Angajat.h"

Data::Data(int Ziua, int Luna, int Anul) {
    ziua = Ziua;
    luna = Luna;
    anul = Anul;
}

Data::~Data() {

}

int Data::getZiua() const {
    return ziua;
}

int Data::getLuna() const {
    return luna;
}

int Data::getAnul() const {
    return anul;
}

void Data::setAnul(int anul) {
    Data::anul = anul;
}

void Data::setLuna(int luna) {
    Data::luna = luna;
}

void Data::setZiua(int ziua) {
    Data::ziua = ziua;
}

bool Data::over_18() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int ani_dif = 1900 + ltm->tm_year - anul;
    if (ani_dif > 18)
        return true;

    if (ani_dif == 18) {
        int luni_dif = 1 + ltm->tm_mon - luna;
        if (luni_dif > 0)
            return true;

        if (luni_dif == 0) {
            int zile_dif = ltm->tm_mday - ziua;
            return zile_dif >= 0;
        }
        return false;
    }
    return false;
}

std::ostream &operator<<(std::ostream &o, Data &a) {
    a.afisare(o);
    return o;
}

void Data::afisare(std::ostream &o) {
    o << ziua << "/" << luna << "/" << anul;
}

void Data::citire(std::istream &i) {
    std::cout << "Year: ";
    i >> anul;
    std::cout << "Month: ";
    i >> luna;
    std::cout << "Day: ";
    i >> ziua;
}

std::istream &operator>>(std::istream &i, Data &a) {
    a.citire(i);
    return i;
}

bool Data::not_future() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (1900 + ltm->tm_year < anul) {
        return false;
    } else if (1 + ltm->tm_mon < luna) {
        return false;
    }
    return ltm->tm_mday >= ziua;

}

