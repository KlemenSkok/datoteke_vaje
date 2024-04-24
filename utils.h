
#pragma once

#include <iostream>

using namespace std;


struct Projekt {
    char izvajalec[21];
    char nazivProjekta[21];
    int st_mesecev;
    float placana_cena;
};


class Projekti {

    string izvajalec, nazivProjekta;
    int st_mesecev;
    float placana_cena;

public:

    Projekti();
    Projekti(const Projekti&);
    Projekti(const struct Projekt&);
    float avg_mesecna_cena();

    Projekti operator+(int);
    bool operator>(Projekti);
    struct Projekt dump();


};