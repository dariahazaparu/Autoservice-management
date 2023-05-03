//
// Created by Daria on 3/24/2021.
//

#include <iostream>
#include "Gestionare_angajati.h"

Gestionare_angajati::Gestionare_angajati() = default;

Gestionare_angajati *Gestionare_angajati::getInstance() {
    if (!instanceFlag) {
        single = new Gestionare_angajati();
        instanceFlag = true;
        return single;
    } else {
        return single;
    }
}

void Gestionare_angajati::adauga(Angajat *angajat) {

    angajati.push_back(angajat);
    std :: cout << "Successfully added employee " << angajat->getNume() << " " << angajat->getPrenume() << ".\n";
}

void Gestionare_angajati::sterge(int id) {

    int counter = 0;
    auto* to_delete = new Angajat();
    for (auto ang : angajati) {
        counter++;
        if (ang->getId() == id) {
            to_delete = ang;
            break;
        }
    }
    delete to_delete;
    angajati.erase(angajati.begin() + counter - 1);
    std::cout << "Successfully deleted.\n";
}

void Gestionare_angajati::afisare() {

    std::cout << "List with all employees by id, last name and first name:\n";
    for (auto ang: angajati) {
        std::cout << *ang << "\n";
    }
}

void Gestionare_angajati::editare(int id) {
    auto *angajat = new Angajat();
    for (auto ang : angajati) {
        if (ang->getId() == id) {
            angajat = ang;
        }
    }
    std::cout << "Edit employee " << angajat->getNume() << " " << angajat->getPrenume() << ".\n";

    std::cout << "Choose to edit: 'lname' for last name, 'fname' for first name, 'birth' for birth date or 'hire' for hire date.\n";
    std::cout << "You can edit multiple data, so when you are done, please write 'exitedit'.\n";

    std::string flag;
    std::cin >> flag;

    while (flag != "exitedit") {
        if (flag == "lname") {
            std::cout << "Old last name: " << angajat->getNume() << "\n";

            std::cout << "New last name: ";
            std::string nume_nou;
            std::cin >> nume_nou;
            angajat->setNume(nume_nou);

        } else if (flag == "fname") {
            std::cout << "Old first name: " << angajat->getPrenume() << '\n';

            std::cout << "New first name: ";
            std::string prenume_nou;
            std::cin >> prenume_nou;
            angajat->setPrenume(prenume_nou);
        } else if (flag == "birth") {
            Data n = angajat->getDataNasterii();
            std :: cout << "Old birth date: " << n << '\n';

            bool ok = false;
            while(!ok) {
                std :: cout << "New birth date:\n";

                std :: cout << "Year:";
                int y;
                std :: cin >> y;

                std :: cout << "Month:";
                int m;
                std :: cin >> m;

                std :: cout << "Day:";
                int d;
                std :: cin >> d;

                Data new_d(d, m, y);
                if (new_d.over_18()) {
                    ok = true;
                    angajat->setDataNasterii(new_d);
                } else {
                    std :: cout << "Not old enough to work here. Continue editing ('edit') or quit ('quit')?\n";
                    std :: string cont;
                    std :: cin >> cont;
                    if (cont == "quit"){
                        break;
                    }
                }
            }

        } else if (flag == "hire") {
            Data n = angajat->getDataAngajarii();
            std :: cout << "Old hire date: " << n << '\n';

            bool ok = false;
            while(!ok) {
                std :: cout << "New hire date:\n";

                std :: cout << "Year:";
                int y;
                std :: cin >> y;

                std :: cout << "Month:";
                int m;
                std :: cin >> m;

                std :: cout << "Day:";
                int d;
                std :: cin >> d;

                Data new_d(d, m, y);
                if (new_d.not_future()) {
                    ok = true;
                    angajat->setDataAngajarii(new_d);
                } else {
                    std :: cout << "It cannot be a future date. Continue editing ('edit') or quit ('quit')?\n";
                    std :: string cont;
                    std :: cin >> cont;
                    if (cont == "quit"){
                        break;
                    }
                }
            }

        }

        std::cout
                << "Successfully edited, would you like to continue? Choose from 'lname', 'fname', 'birth' or 'hire', or 'exitedit' if you are done.\n";
        std::cout << "Edit command: ";
        std::cin >> flag;
    }


}

double Gestionare_angajati::salariu(int id) {
    auto* to_calc = new Angajat();
    for (auto ang : angajati) {
        if (ang->getId() == id) {
            to_calc = ang;
            break;
        }
    }
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return to_calc->ani_vechime() * to_calc->getCoeficient() * 1000;
}

bool Gestionare_angajati::deschis() {
    if (angajati.empty())
        return false;
    return true;
}

const std::vector<Angajat *> &Gestionare_angajati::getAngajati() const {
    return angajati;
}
