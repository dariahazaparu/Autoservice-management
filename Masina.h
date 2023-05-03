//
// Created by Daria on 3/25/2021.
//

#ifndef ESSENSYS_MASINA_H
#define ESSENSYS_MASINA_H


class Masina {
protected:
    int ID;
    int nr_km;
    int fabricatie;
    bool diesel;

    static int increment;

public:
    int getId() const;

    Masina(int NrKm, int Fabricatie, bool Diesel);

    int getNrKm() const;

    void setNrKm(int nrKm);

    virtual ~Masina();

    int getFabricatie() const;

    void setFabricatie(int fabricatie);

    bool isDiesel() const;

    void setDiesel(bool diesel);

    virtual double asigurare(bool discount = false) = 0;

//    virtual int discount_asigurare() = 0;

};


#endif //ESSENSYS_MASINA_H
