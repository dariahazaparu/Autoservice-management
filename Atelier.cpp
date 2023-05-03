//
// Created by Daria on 3/25/2021.
//

#include <iostream>
#include <unistd.h>
#include "Atelier.h"
#include "Standard.h"
#include "Autobuz.h"
#include "Camion.h"
#include "Angajat.h"
#include "Gestionare_angajati.h"

Atelier::Atelier() {
    std :: cout << "AUTO SERVICE - OPEN\n\n";
    sleep(1);
    std :: cout << "Here, we work with units of time. Every unit of time, a new costumer comes or the unit of time can pass unused.\n";
    std :: cout << "We don't book ahead, so every employee is free at first unit of time.\n";
    std :: cout << "To welcome a new costumer, write 'new'. If nobody is coming, write 'pass'.\n";
    std :: cout << "When a car arrives, the employee gives you an estimated time. You can choose to leave if it is too much for you to wait.\n";
    std :: cout << "The customer has the option to choose a specific employee, identified by id.\n";
    std :: cout << "Employees can be full, they will try to squeeze costumers when one is available.\n";
    sleep(20);
    Gestionare_angajati *g = Gestionare_angajati::getInstance();
    int s = g->getAngajati().size();
    reparatii.resize(s + 1);
    asteptare_ang_mare.resize(s + 1);
    asteptare_ang_standard.resize(s + 1);
}

Atelier *Atelier::getInstance() {
    if (!instanceFlag) {
        single = new Atelier();
        instanceFlag = true;
        return single;
    } else {
        return single;
    }
}

Angajat *Atelier::find(int id) {
    Gestionare_angajati *g = Gestionare_angajati::getInstance();
    for (auto i : g->getAngajati()) {
        if (i->getId() == id) {
            return i;
        }
    }
    return nullptr;
}

void Atelier::masina_noua(int units) {

    std::cout << "Car details\n";

    bool ok = false;
    std::string type;
    while (!ok) {
        std::cout << "Type ('standard', 'bus' or 'truck'): ";
        std::cin >> type;

        if (type == "standard" or type == "bus" or type == "truck") {
            ok = true;
        } else {
            std::cout << "I don't work with this type of car, please try again.\n";
        }
    }
    ok = false;
    std::cout << "Kilometers on board: ";
    int nr;
    while(!ok)  {
        std::cout << "Kilometers on board: ";
        std::cin >> nr;
        if (nr <= 0) {
            std :: cout << "It can't be that new, insert a valid number please.\n";
        } else {
            ok = true;
        }
    }

    ok = false;
    int year;
    while (!ok) {
        std::cout << "Year of fabrication: ";
        std::cin >> year;
        if( year > 2021) {
            std :: cout << "You cannot place a year from the future, please try again.\n";
        } else if (year < 1900) {
            std :: cout << "It can't be that old, insert a valid year please.\n";
        } else
            ok = true;
    }

    std::cout << "Is it diesel? (y/n) ";
    char ch;
    std::cin >> ch;
    bool ddiesel = ch == 'y';

    if (type == "standard") {
        std::cout << "Is it manual? (y/n) ";
        char chh;
        std::cin >> chh;
        bool mmanual = chh == 'y';

        Standard s(nr, year, ddiesel, mmanual);
        std::cout << "Car registered.\n";
        procesare(s, units);
    } else if (type == "bus") {
        std::cout << "Number of sits: ";
        int loc;
        std::cin >> loc;

        Autobuz a(nr, year, ddiesel, loc);
        std::cout << "Car registered.\n";
        procesare(a, units);
    } else if (type == "truck") {
        std::cout << "Tons: ";
        int ton;
        std::cin >> ton;

        Camion c(nr, year, ddiesel, ton);
        std::cout << "Car registered.\n";
        procesare(c, units);
    }
}

void Atelier::procesare(Standard s, int units) {
    std::cout << "It takes 5 to repair ypu car, do you want to continue? (y/n)";
    char c;
    std::cin >> c;
    bool cont = c == 'y';

    if (!cont) return;

    std::cout << "Do you want a specific employee to repair your car? (y/n)";
    char ch;
    std::cin >> ch;
    bool specific = ch == 'y';

    if (specific) /* cazurile 1-4*/ {
        int id;
        bool ok = false;
        while(!ok) {
            std::cout << "Choose an employee by id. Write a number from 1 to " << Angajat::getIncrement() - 1 << ":";
            std::cin >> id;
            if (id > Angajat::getIncrement() - 1 or id == 0) {
                std :: cout << "Invalid employee, please try again.\n";
            } else
                ok = true;
        }

        Angajat *ang = find(id);

        //cazul 1
        if (ang->getStandardCounter() < 3) {
            reparatii[id].push({{-(units + 5), s.getId()}, 1});
            ang->setTotalMasini(ang->getTotalMasini()+1);
            ang->setStandardCounter(ang->getStandardCounter() + 1);
            return;
        }

        std::cout << "The employee you chose is busy at the moment. You have 3 options:\n";
        std::cout << "\t1 - leave and come another time;\n";
        std::cout << "\t2 - wait for this employee to become available;\n";
        std::cout << "\t3 - wait to get assigned to the first employee available(next unit).\n";
        std::cout << "Choice:";
        int choice;
        std::cin >> choice;

        if (choice == 1) /* cazul 2*/ {
            return;
        } else if (choice == 2) /* cazul 3*/ {
            asteptare_ang_standard[id].push(s.getId());
            auto ang = find(id);
            ang->setCereriSpeciale(ang->getCereriSpeciale() +1 );
        } else if (choice == 3) /* cazul 4*/  {
            asteptare.push({5, s.getId()});
        }
    } else /* cazurile 5-7 */ {
        Gestionare_angajati *g = Gestionare_angajati::getInstance();

        bool ok = false;
        auto angajati = g->getAngajati();
        for (int i = 1; i < angajati.size(); ++i) {
            if (angajati[i]->getStandardCounter() < 3) /* cazul 5*/ {
                ok = true;
                reparatii[i].push({{-(units + 5), s.getId()}, 1});
                angajati[i]->setTotalMasini(angajati[i]->getTotalMasini()+1);
                angajati[i]->setStandardCounter(angajati[i]->getStandardCounter() + 1);
                break;
            }
        }
        if (!ok) {
            std::cout << "Everybody is busy. You have 2 options:\n";
            std::cout << "\t1 - leave and come another time;\n";
            std::cout << "\t2 - wait to get assigned to the first employee available(next unit).\n";
            std::cout << "Choice:";
            int choice;
            std::cin >> choice;

            if (choice == 1) /* cazul 6*/ {
                return;
            } else if (choice == 2) /*cazul 7*/ {
                asteptare.push({5, s.getId()});
            }
        }
    }

}

void Atelier::procesare(Autobuz a, int units) {

    std::cout << "It takes 7 to repair your bus, do you want to continue? (y/n)";
    char c;
    std::cin >> c;
    bool cont = c == 'y';

    if (!cont) return;

    std::cout << "Do you want a specific employee to repair your bus? (y/n)";
    char ch;
    std::cin >> ch;
    bool specific = ch == 'y';

    if (specific) /* cazurile 1-4*/ {
        std::cout << "Choose an employee by id. Write a number from 1 to " << Angajat::getIncrement() - 1 << ":";
        int id;
        std::cin >> id;
        Angajat *ang = find(id);
//        id--;

        //cazul 1 - angajatul are loc
        if (!ang->isMasinaMare()) {
            reparatii[id].push({{-(units + 7), a.getId()}, 2});
            ang->setTotalMasini(ang->getTotalMasini()+1);
            ang->setMasinaMare(true);
            return;
        }

        std::cout << "The employee you chose is busy at the moment. You have 3 options:\n";
        std::cout << "\t1 - leave and come another time;\n";
        std::cout << "\t2 - wait for this employee to become available;\n";
        std::cout << "\t3 - wait to get assigned to the first employee available(next unit).\n";
        std::cout << "Choice:";
        int choice;
        std::cin >> choice;

        if (choice == 1) /* cazul 2*/ {
            return;
        } else if (choice == 2) /* cazul 3*/ {
            asteptare_ang_mare[id].push({7, a.getId()});
            auto ang = find(id);
            ang->setCereriSpeciale(ang->getCereriSpeciale() +1 );
        } else if (choice == 3) /* cazul 4*/  {
            asteptare.push({7, a.getId()});
        }
    } else /* cazurile 5-7 */ {
        Gestionare_angajati *g = Gestionare_angajati::getInstance();

        bool ok = false;
        auto angajati = g->getAngajati();
        for (int i = 1; i < angajati.size(); ++i) {
            if (!angajati[i]->isMasinaMare()) /* cazul 5*/ {
                ok = true;
                reparatii[i].push({{-(units + 7), a.getId()}, 2});
                angajati[i]->setTotalMasini(angajati[i]->getTotalMasini()+1);
                angajati[i]->setMasinaMare(true);
                break;
            }
        }
        if (!ok) {
            std::cout << "Everybody is busy. You have 2 options:\n";
            std::cout << "\t1 - leave and come another time;\n";
            std::cout << "\t2 - wait to get assigned to the first employee available(next unit).\n";
            std::cout << "Choice:";
            int choice;
            std::cin >> choice;

            if (choice == 1) /* cazul 6*/ {
                return;
            } else if (choice == 2) /*cazul 7*/ {
                asteptare.push({7, a.getId()});
            }
        }
    }

}

void Atelier::procesare(Camion cc, int units) {

    std::cout << "It takes 7 to repair your truck, do you want to continue? (y/n)";
    char c;
    std::cin >> c;
    bool cont = c == 'y';

    if (!cont) return;

    std::cout << "Do you want a specific employee to repair your truck? (y/n)";
    char ch;
    std::cin >> ch;
    bool specific = ch == 'y';

    if (specific) /* cazurile 1-4*/ {
        std::cout << "Choose an employee by id. Write a number from 1 to " << Angajat::getIncrement() - 1 << ":";
        int id;
        std::cin >> id;
        Angajat *ang = find(id);
//        id--;

        //cazul 1 - angajatul are loc
        if (!ang->isMasinaMare()) {
            reparatii[id].push({{-(units + 7), cc.getId()}, 2});
            ang->setTotalMasini(ang->getTotalMasini()+1);
            ang->setMasinaMare(true);
            return;
        }

        std::cout << "The employee you chose is busy at the moment. You have 3 options:\n";
        std::cout << "\t1 - leave and come another time;\n";
        std::cout << "\t2 - wait for this employee to become available;\n";
        std::cout << "\t3 - wait to get assigned to the first employee available(next unit).\n";
        std::cout << "Choice:";
        int choice;
        std::cin >> choice;

        if (choice == 1) /* cazul 2*/ {
            return;
        } else if (choice == 2) /* cazul 3*/ {
            asteptare_ang_mare[id].push({7, cc.getId()});
            auto ang = find(id);
            ang->setCereriSpeciale(ang->getCereriSpeciale() +1 );
        } else if (choice == 3) /* cazul 4*/  {
            asteptare.push({7, cc.getId()});
        }
    } else /* cazurile 5-7 */ {
        Gestionare_angajati *g = Gestionare_angajati::getInstance();

        bool ok = false;
        auto angajati = g->getAngajati();
        for (int i = 1; i < angajati.size(); ++i) {
            if (!angajati[i]->isMasinaMare()) /* cazul 5*/ {
                ok = true;
                reparatii[i].push({{-(units + 7), cc.getId()}, 2});
                angajati[i]->setTotalMasini(angajati[i]->getTotalMasini()+1);
                angajati[i]->setMasinaMare(true);
                break;
            }
        }
        if (!ok) {
            std::cout << "Everybody is busy. You have 2 options:\n";
            std::cout << "\t1 - leave and come another time;\n";
            std::cout << "\t2 - wait to get assigned to the first employee available(next unit).\n";
            std::cout << "Choice:";
            int choice;
            std::cin >> choice;

            if (choice == 1) /* cazul 6*/ {
                return;
            } else if (choice == 2) /*cazul 7*/ {
                asteptare.push({7, cc.getId()});
            }
        }
    }

}

void Atelier::afisare() {
    std::cout << "Currently repairing:\n";

    for (int i = 1; i < reparatii.size(); ++i) {
        std::cout << "Employee " << i  << ": ";
        auto aux = reparatii[i];
        while(!aux.empty()) {
            std::cout << aux.top().first.second << " ";
            aux.pop();
        }
        std::cout << '\n';
    }

    std::cout << "\nCurrently waiting:\n";
    if (!asteptare.empty()) {
        auto aux = asteptare;
        while (!aux.empty()) {
            std::cout << aux.front().second << " ";
            aux.pop();
        }
    }

    std::cout << '\n';
    std::cout << "Specific waiting for standard cars:\n";
    for (int i = 1; i < asteptare_ang_standard.size(); ++i) {
        std::cout << "Emlpoyee " << i << ": ";
        if (!asteptare_ang_standard[i].empty()) {
            auto aux = asteptare_ang_standard[i];
            while (!aux.empty()) {
                std::cout << aux.front() << " ";
                aux.pop();
            }
        }
        std::cout << '\n';
    }
    std::cout << "\nSpecific waiting for big cars:\n";
    for (int i = 1; i < asteptare_ang_mare.size(); ++i) {
        std::cout << "Emlpoyee " << i << ": ";
        if (!asteptare_ang_mare[i].empty()) {
            auto aux = asteptare_ang_mare[i];
            while (!aux.empty()) {
                std::cout << aux.front().second << " ";
                aux.pop();
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';


}

void Atelier::parcurgere(int units) {

    int x = reparatii.size();
    for (int i = 1; i < x; ++i) {
        if (reparatii[i].empty())
            continue;
        auto *angajat = find(i);
        while (-reparatii[i].top().first.first == units and !reparatii[i].empty()) {
            auto p = reparatii[i].top();
            reparatii[i].pop();
            if(p.second == 1) {
                angajat->setStandardCounter((angajat->getStandardCounter() - 1));
            } else {
                angajat->setMasinaMare(false);
            }
        }
    }

    bool ok_std = false, ok_bus = false;

    Gestionare_angajati *g = Gestionare_angajati::getInstance();
    auto angajati = g->getAngajati();
    bool ok = false;
    if (!asteptare.empty()) {
        while (!ok) {
            x = asteptare.size();
            auto next = asteptare.front();
            for (auto i : angajati) {
                if (next.first == 5) {
                    if (i->getStandardCounter() < 3) {
                        ok_std = true;
                        reparatii[i->getId()].push({{-(units + next.first), next.second}, 1});
                        i->setTotalMasini(i->getTotalMasini()+1);
                        i->setStandardCounter((i->getStandardCounter() + 1));
                        asteptare.pop();
                        break;
                    }
                } else if (next.first == 7 /*or next.first ==6 */) {
                    std :: cout << next.second << " ";
                    if (!i->isMasinaMare()) {
                        ok_bus = true;
                        reparatii[i->getId()].push({{-(units + next.first), next.second}, 2});
                        i->setTotalMasini(i->getTotalMasini()+1);
                        i->setMasinaMare(true);
                        asteptare.pop();
                        break;
                    }
                }
            }
            if (!ok_std)
                ok = true; // nu e niciun angajat liber pentru o masina standard
            if (!ok_bus)
                ok = true; // nu e niciun angajat liber pentru o masina mare
        }
    }

    for (int i = 1; i < x; ++i) {
        if (!asteptare_ang_standard[i].empty()) {
            auto angajat = find(i);
            while (angajat->getStandardCounter() < 3 and !asteptare_ang_standard[i].empty()) {
                reparatii[i].push({{-(units + 5), asteptare_ang_standard[i].front()}, 1});
                angajat->setTotalMasini(angajat->getTotalMasini()+1);
                angajat->setStandardCounter(angajat->getStandardCounter() + 1);
                asteptare_ang_standard[i].pop();
            }
        }
    }

    for (int i = 1; i < x; ++i) {
        if (!asteptare_ang_mare[i].empty()) {
            auto angajat = find(i);
            while (!angajat->isMasinaMare() and !asteptare_ang_mare[i].empty()) {
                reparatii[i].push({{-(units + 7), asteptare_ang_mare[i].front().second}, 2});
                angajat->setTotalMasini(angajat->getTotalMasini()+1);
                angajat->setMasinaMare(true);
                asteptare_ang_mare[i].pop();
            }
        }
    }
}
