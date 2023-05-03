//
// Created by Daria on 3/24/2021.
//

#include <iostream>
#include "Angajat.h"

Angajat::Angajat(std::string nume, std::string prenume, Data d, Data a) {
    ID = increment++;
    if (!nume.empty() and nume.size() <= 30) {
        Nume = nume;
    } else if (nume.size() > 30) {
        std::cout << "Invalid last name, more than 30 characters.";
    } else if (nume.empty()) {
        std::cout << "Invalid last name, it cannot be null.";
    }
    if (!prenume.empty() and prenume.size() <= 30) {
        Prenume = prenume;
    } else if (prenume.size() > 30){
        std::cout << "Invalid first name, more than 30 characters.";
    } else if (prenume.empty()) {
        std::cout << "Invalid first name, it cannot be null.";
    }
    data_nasterii = d;
    data_angajarii = a;
    standard_counter = 0;
    masina_mare = false;
    total_masini = 0;
    cereri_speciale = 0;
}


const std::string &Angajat::getNume() const {
    return Nume;
}

const std::string &Angajat::getPrenume() const {
    return Prenume;
}

int Angajat::getId() const {
    return ID;
}

void Angajat::setPrenume(const std::string &prenume) {
    Prenume = prenume;
}

void Angajat::setNume(const std::string &nume) {
    Nume = nume;
}

void Angajat::citire(std::istream &i) {
    i >> Nume >> Prenume;
}

std::istream& operator>>(std::istream &i, Angajat &a) {
    a.citire(i);
    return i;
}

void Angajat::afisare(std::ostream &o) {
    o << "Emplyoyee ID:" << ID << '\n' << "\tLast name: " << Nume << "\n\tFirst name: " << Prenume << "\n\tBirthday: " << data_nasterii << "\n\tHire date: " << data_angajarii;
}

std::ostream &operator<<(std::ostream &o, Angajat &a) {
    a.afisare(o);
    return o;
}

const Data &Angajat::getDataNasterii() const {
    return this->data_nasterii;
}

void Angajat::setDataNasterii(const Data &dataNasterii) {
    data_nasterii = dataNasterii;
}

const Data &Angajat::getDataAngajarii() const {
    return data_angajarii;
}

void Angajat::setDataAngajarii(const Data &dataAngajarii) {
    data_angajarii = dataAngajarii;
}

int Angajat::ani_vechime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int an = data_angajarii.getAnul();
    int luna = data_angajarii.getLuna();
    int zi = data_angajarii.getZiua();
    int vechime = 0;

    if (1900 + ltm->tm_year == an) {
        return 1;
    }
    else {

        return 1900 + ltm->tm_year - an;
    }
}

int Angajat::getStandardCounter() const {
    return standard_counter;
}

bool Angajat::isMasinaMare() const {
    return masina_mare;
}

void Angajat::setMasinaMare(bool masinaMare) {
    masina_mare = masinaMare;
}

void Angajat::setStandardCounter(int standardCounter) {
    standard_counter = standardCounter;
}

int Angajat::getIncrement() {
    return increment;
}

int Angajat::getTotalMasini() const {
    return total_masini;
}

void Angajat::setTotalMasini(int totalMasini) {
    total_masini = totalMasini;
}

int Angajat::getCereriSpeciale() const {
    return cereri_speciale;
}

void Angajat::setCereriSpeciale(int cereriSpeciale) {
    cereri_speciale = cereriSpeciale;
}

bool Angajat::at_hire() {
    auto hire = data_angajarii;
    auto birth = data_nasterii;

    if (hire.getAnul() - birth.getAnul() > 18) {
        return true;
    }
    if (hire.getAnul() - birth.getAnul() == 18) {
        if (hire.getLuna() - birth.getLuna() > 0 )
            return true;
        if (hire.getLuna() - birth.getLuna() == 0 ) {
            if (hire.getZiua() - birth.getZiua() >= 0 )
                return true;
        }
    }
    return false;

}
