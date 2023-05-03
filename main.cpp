#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Angajat.h"
#include "Gestionare_angajati.h"
#include "Director.h"
#include "Asistent.h"
#include "Mecanic.h"
#include "Data.h"
#include "Masina.h"
#include "Standard.h"
#include "Autobuz.h"
#include "Camion.h"
#include "Atelier.h"

bool Gestionare_angajati::instanceFlag = false;
Gestionare_angajati *Gestionare_angajati::single = nullptr;

bool Atelier::instanceFlag = false;
Atelier *Atelier::single = nullptr;

int Angajat::increment = 1;
int Masina::increment = 1;

int main() {
//    time_t now = time(0);
//    tm *ltm = localtime(&now);
//    std :: cout << "The current local date and time is: " << 1900 + ltm->tm_year << std ::endl;
//    std :: cout << "The current local date and time is: " << 1 + ltm->tm_mon << std ::endl;
//    std :: cout << "The current local date and time is: " << ltm->tm_mday << std ::endl;
//
    std :: cout << "Welcome to my auto car service!\n";
    sleep(2);
    std :: cout << "My name is Daria, I am here to help and guide you.\n";
    sleep(2);
    std :: cout << "Important! when you want to end this session, write 'exit' and I leave.\n";
    sleep(5);
    std :: cout << "Let's make the introduction. :)\n";
    sleep(1);

    Gestionare_angajati *g = Gestionare_angajati::getInstance();
    Angajat *a1 = new Director("King", "Steven", Data(21, 6, 1995), Data(20, 12, 2017));
    Angajat *a2 = new Asistent("Smith", "Robert", Data(12, 3, 1999), Data(20, 12, 2019));
    Angajat *a3 = new Mecanic("Park", "John", Data(7, 8, 1990), Data(20, 12, 2012));
    Angajat *a4 = new Mecanic("Walter", "George", Data(4, 12, 1991), Data(20, 12, 2015));

    g->adauga(a1);
    g->adauga(a2);
    g->adauga(a3);
    g->adauga(a4);

//    g->afisare();
    std :: cout << "We will manage my auto service together. There is a list of employees already in the system and I assure you they are all in correct form.\n";
    sleep(5);
    std::cout << "Write 'help' for instructions.\n";

    std::string flag;
    std::cout << "Command:";
    std::cin >> flag;

    while (flag != "exit") {
        if (flag != "help" && flag != "showemployees" && flag != "editemployee" && flag != "deleteemployee" &&
            flag != "addemployee" && flag != "salaryemployee" && flag != "open" && flag != "bestemployee" && flag != "busiestemployee") {
            std::cout << "I don't know this command, please try again.\n";
        }
        if (flag == "help") {
            std::cout << "Help is here :D\n";
            std::cout << "\tWrite 'showemployees' to see all employees.\n";
            std::cout << "\tWrite 'addemployee' to hire a new employee.\n";
            std::cout << "\tWrite 'editemployee' to edit an employee.\n";
            std::cout << "\tWrite 'salaryemployee' to view someone's salary.\n";
            std::cout << "\tWrite 'deleteemployee' to fire an employee.\n";
            std::cout << "\tWrite 'bestmployee' to know which employee has the most cars repaired.\n";
            std::cout << "\tWrite 'busiestemployee' to know which employee was requested the most.\n";
            std::cout << "\tWrite 'open' to open the service (you cannot edit employees when you are here).\n";
            std::cout << "\tWrite 'exit' to end the session.\n";
        }
        else if (flag == "showemployees") {
            g->afisare();
        }
        else if (flag == "editemployee") {
            std::cout << "ID employee to edit: ";
            int id_edit;
            std::cin >> id_edit;
            g->editare(id_edit);
        }
        else if (flag == "deleteemployee") {
            std::cout << "ID employee to delete: ";
            int id_delete;
            std::cin >> id_delete;
            g->sterge(id_delete);
        }
        else if (flag == "addemployee") {
            std::cout << "New employee!\n";
            bool ok = false;

            std::string lname;
            while (!ok) {
                std::cout << "Last name: ";
                std::cin >> lname;
                if (lname.empty()) {
                    std::cout << "Invalid name, it cannot be null, please try again.\n";
                } else if (lname.size() > 30) {
                    std::cout << "Invalid name, it cannot have more than 30 characters, please try again.\n";
                } else {
                    ok = true;
                }
            }

            ok = false;

            std::string fname;
            while (!ok) {
                std::cout << "First name: ";
                std::cin >> fname;
                if (fname.empty()) {
                    std::cout << "Invalid name, it cannot be null, please try again.\n";
                } else if (fname.size() > 30) {
                    std::cout << "Invalid name, it cannot have more than 30 characters, please try again.\n";
                } else {
                    ok = true;
                }
            }

            std::cout << "Birth date:\n";
            Data d;
            std::cin >> d;
            if (!d.over_18()) {
                std::cout << "Not old enough to work here.\n";
                std::cout << "Command:";
                std::cin >> flag;
                continue;
            }

            ok = false;
            std::cout << "Hire date:\n";
            Data a;
            std::cin >> a;
            while (!ok) {
                if (a.not_future()) {
                    std::cout << "You can't insert a future date, please try again.\n";
                    std::cin >> a;
                } else {
                    ok = true;
                }
            }

            std::cout << "'director', 'assistant' or 'mechanic': ";
            std::string pos;
            std::cin >> pos;

            bool next = false;

            while (!next) {
                if (pos == "director") {
                    Angajat *ang = new Director(lname, fname, d, a);
                    if (ang->at_hire()) {
                        g->adauga(ang);
                    } else {
                        std :: cout << "Employee wasn't old enough to be working here.\n";
                    }
                    break;
                } else if (pos == "assistant") {
                    Angajat *ang = new Asistent(lname, fname, d, a);
                    if (ang->at_hire()) {
                        g->adauga(ang);
                    } else {
                        std :: cout << "Employee wasn't old enough to be working here.\n";
                    }
                    break;
                } else if (pos == "mechanic") {
                    Angajat *ang = new Mecanic(lname, fname, d, a);
                    if (ang->at_hire()) {
                        g->adauga(ang);
                    } else {
                        std :: cout << "Employee wasn't old enough to be working here.\n";
                    }
                    break;
                } else {
                    std::cout << "I don't know this command, please try again.\n";
                    next = false;
                    std::cout << "'director', 'assistant' or 'mechanic': ";
                    std::cin >> pos;
                }
            }
        }
        else if (flag == "salaryemployee") {
            std::cout << "ID employee for salary: ";
            int id_sal;
            std::cin >> id_sal;
            std::cout << "Salary for employee " << id_sal << " is " << g->salariu(id_sal) << ".\n";
        }
        else if (flag == "cars") {
            Standard s1(2000, 2020, true, false);
            std::cout << s1.asigurare() << "\n";
            std::cout << s1.asigurare(true) << "\n";
            Standard s2(2000, 2019, true, false);
            std::cout << s2.asigurare() << "\n";
            Standard s3(200005, 2019, true, false);
            std::cout << s3.asigurare() << "\n";
            Standard s4(200005, 2019, false, false);
            std::cout << s4.asigurare() << "\n";
            Autobuz a1(20000, 2020, true, 100);
            std::cout << a1.asigurare() << "\n";
            std::cout << a1.asigurare(true) << "\n";
            Autobuz a2(5000000, 2020, false, 50);
            std::cout << a2.asigurare() << "\n";
            Autobuz a3(100050, 2019, false, 50);
            std::cout << a3.asigurare() << "\n";
            Camion c1(800050, 2020, false, 5);
            std::cout << c1.asigurare() << "\n";
        }
        else if (flag == "open") {
            if (!g->deschis()) {
                std::cout << "There are no employees today at the service :(\n";
                std::cout << "Hire at least one employee and we can open :D. \n";
                std::cout << "Command:";
                std::cin >> flag;
                continue;
            }

            std::cout << "Let's open my auto service!\n";
//            sleep(2);
            system("cls");
            Atelier *a = Atelier :: getInstance();

            int units = 0;
            std :: cout << "Current unit of time: " << units++ << '\n';
            a->afisare();

            std :: string cerere;
            std :: cout << "Request:";
            std :: cin >> cerere;
            while (cerere != "close") {
                if (cerere != "new" && cerere != "pass") {
                    std::cout << "I don't know this command, please try again.\n";
                    std :: cout << "Request:";
                    std :: cin >> cerere;
                } else {

                    std :: cout << "Current unit of time: " << units++ << '\n';

                    a->parcurgere(units);
                    if (cerere == "new") {
                        std :: cout << "New costumer :)\n";
                        a->masina_noua(units);
                    } else if (cerere == "pass") {
                        std :: cout << "No new costumer this unit. :(\n";
                    }

                    a->afisare();

                    std :: cout << "Request:";
                    std :: cin >> cerere;
                }
            }
        } else if (flag == "bestemployee") {
            auto aux = g->getAngajati();
            Angajat* best;
            int maxim = -1;
            for (auto i : aux) {
                if(maxim < i->getTotalMasini()){
                    maxim = i->getTotalMasini();
                    best = i;
                }
            }
            if (maxim > 0) {
                std :: cout << *best;
                std :: cout << "\n\tMost cars repaired: " << best->getTotalMasini() << '\n';
            } else {
                std :: cout << "The employees haven't worked yet.\n";
            }
        } else if (flag == "busiestemployee") {
            auto aux = g->getAngajati();
            Angajat* best ;
            int maxim = -1;
            for (auto i: aux) {
                if (maxim < i->getCereriSpeciale()){
                    maxim = i->getCereriSpeciale();
                    best = i;
                }
            }
            if (maxim > 0) {
                std :: cout << *best;
                std :: cout << "\n\tNumber of requests: " << best->getTotalMasini() << '\n';
            }
            else
                std :: cout << "The employees haven't worked yet.\n";
        }
        if (flag == "close") {
            std :: cout << "AUTO SERVICE - CLOSE\n\n";
            system("cls");
        }
        std::cout << "Command:";
        std::cin >> flag;
    }

    std::cout << "Nice work! See ya :)";
    return 0;
}
