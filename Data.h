//
// Created by Daria on 3/25/2021.
//

#ifndef ESSENSYS_DATA_H
#define ESSENSYS_DATA_H


#include <ctime>
#include<iostream>

class Data {

private:
    int ziua;
    int luna;
    int anul;
public:
    Data(){};
    Data(int Ziua, int Luna, int Anul);

    virtual ~Data();

    int getZiua() const;

    void setZiua(int ziua);

    int getLuna() const;

    void setLuna(int luna);

    int getAnul() const;

    void setAnul(int anul);

    bool over_18();

    bool not_future();

    void citire(std::istream &i);

    friend std::istream &operator>>(std::istream &i, Data &a);

    void afisare(std::ostream &o);

    friend std::ostream &operator<<(std::ostream &o, Data &a);
};


#endif //ESSENSYS_DATA_H
