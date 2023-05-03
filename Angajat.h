//
// Created by Daria on 3/24/2021.
//

#ifndef ESSENSYS_ANGAJAT_H
#define ESSENSYS_ANGAJAT_H

#include <string>
#include "Data.h"

class Angajat {
protected:
    static int increment;
public:
    static int getIncrement();

protected:
    int ID;
    std::string Nume;
    std::string Prenume;
    double coeficient;
    Data data_nasterii;
    Data data_angajarii;

    int standard_counter;
    int total_masini;
    bool masina_mare;
    int cereri_speciale;

public:

    Angajat(){};

    Angajat(std::string nume, std::string prenume, Data d, Data a);

    const std::string &getNume() const;

    void setNume(const std::string &nume);

    const std::string &getPrenume() const;

    void setPrenume(const std::string &prenume);

    int getId() const;

    virtual double getCoeficient() const {return 0;};

    const Data &getDataNasterii() const;

    void setDataNasterii(const Data &dataNasterii);

    virtual ~Angajat() = default;

    virtual void citire(std::istream &i);

    friend std::istream &operator>>(std::istream &i, Angajat &a);

    virtual void afisare(std::ostream &o);

    friend std::ostream &operator<<(std::ostream &o, Angajat &a);

    const Data &getDataAngajarii() const;

    void setDataAngajarii(const Data &dataAngajarii);

    int ani_vechime();

    bool isMasinaMare() const;

    void setMasinaMare(bool masinaMare);

    int getStandardCounter() const;

    void setStandardCounter(int standardCounter);

    int getTotalMasini() const;

    void setTotalMasini(int totalMasini);

    int getCereriSpeciale() const;

    void setCereriSpeciale(int cereriSpeciale);

    bool at_hire();
};


#endif //ESSENSYS_ANGAJAT_H
