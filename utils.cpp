
#include <cstring>

#include "utils.h"


Projekti::Projekti(const struct Projekt &a) {
    this->izvajalec = a.izvajalec;
    this->nazivProjekta = a.nazivProjekta;
    this->st_mesecev = a.st_mesecev;
    this->placana_cena = a.placana_cena;
}

Projekti::Projekti(const Projekti &a) {
    this->izvajalec = a.izvajalec;
    this->nazivProjekta = a.nazivProjekta;
    this->st_mesecev = a.st_mesecev;
    this->placana_cena = a.placana_cena;
}


float Projekti::avg_mesecna_cena() {
    return placana_cena / st_mesecev;
}

Projekti Projekti::operator+(int a) {
    Projekti x(*this);
    x.st_mesecev += a;
    x.placana_cena *= 0.95;
}

bool Projekti::operator>(Projekti a) {
    return this->st_mesecev > a.st_mesecev;
}

struct Projekt Projekti::dump() {
    struct Projekt a;
    strcmp(a.izvajalec, izvajalec.c_str());
    strcmp(a.nazivProjekta, nazivProjekta.c_str());
    a.st_mesecev = this->st_mesecev;
    a.placana_cena = this->placana_cena;

    return a;
}