//
// Created by Daria on 3/25/2021.
//

#include "Masina.h"


Masina::Masina(int NrKm, int Fabricatie, bool Diesel) {
    ID = increment++;
    nr_km = NrKm;
    fabricatie = Fabricatie;
    diesel = Diesel;
}

int Masina::getNrKm() const {
    return nr_km;
}

int Masina::getFabricatie() const {
    return fabricatie;
}

bool Masina::isDiesel() const {
    return diesel;
}

void Masina::setDiesel(bool Diesel) {
    diesel = Diesel;
}

void Masina::setFabricatie(int Fabricatie) {
    fabricatie = Fabricatie;
}

void Masina::setNrKm(int nrKm) {
    nr_km = nrKm;
}

int Masina::getId() const {
    return ID;
}

Masina::~Masina() = default;
