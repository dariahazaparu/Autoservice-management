cmake_minimum_required(VERSION 3.15)
project(essensys)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(essensys main.cpp Angajat.cpp Angajat.h Gestionare_angajati.cpp Gestionare_angajati.h Director.cpp Director.h Mecanic.cpp Mecanic.h Asistent.cpp Asistent.h Data.cpp Data.h Masina.cpp Masina.h Standard.cpp Standard.h Autobuz.cpp Autobuz.h Camion.cpp Camion.h Atelier.cpp Atelier.h)