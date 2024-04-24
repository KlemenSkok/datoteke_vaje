#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

//#include "utils.h"

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
    bool operator==(char*);
    void izpis();


};

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

void Projekti::izpis() {
    cout << izvajalec << nazivProjekta;
    cout << st_mesecev << " mesecev, " << placana_cena << " EUR\n\n";
}


float Projekti::avg_mesecna_cena() {
    return placana_cena / st_mesecev;
}

Projekti Projekti::operator+(int a) {
    Projekti x(*this);
    x.st_mesecev += a;
    x.placana_cena *= 0.95;

    return x;
}

bool Projekti::operator>(Projekti a) {
    return this->st_mesecev > a.st_mesecev;
}

struct Projekt Projekti::dump() {
    struct Projekt a;
    strcpy(a.izvajalec, izvajalec.c_str());
    strcpy(a.nazivProjekta, nazivProjekta.c_str());
    a.st_mesecev = this->st_mesecev;
    a.placana_cena = this->placana_cena;

    return a;
}

bool Projekti::operator==(char* s) {
    return !strcmp(s, izvajalec.c_str());
}


void napolni_objekte(vector<Projekti> &v) {
    ifstream in("Projekti.bin", ios::binary);
    if(!in.is_open()) {
        cout << "Napaka pri odpiranju dat\n";
        return;
    }

    struct Projekt a;
    while(in.read((char*) &a, sizeof(struct Projekt))) {
        Projekti p(a);
        v.push_back(p);
    }
    in.close();
}

int najvec_mesecev(vector<Projekti> &v) {
    int max = 0;
    for(int i = 1; i < v.size(); i++) {
        if(v[i] > v[max])
            max = i;
    }
    return max; // index
}

/* void zapisi_v_dat(int index, struct Projekt a) {
    ofstream out("Projekti.bin", ios::binary);
    out.clear();
    out.seekp(index * sizeof(struct Projekt), ios::beg);
    out.write((char*) &a, sizeof(struct Projekt));
    out.close();
} */

void zapisi_v_dat(int index, struct Projekt a) {
    fstream f("Projekti.bin", ios::binary | ios::in | ios::out);
    if(!f.is_open())
        return;

    f.clear();
    f.seekp(index * sizeof(struct Projekt), ios::beg);
    f.write((char*) &a, sizeof(struct Projekt));

    f.close();

    
}



void izpis_projekt(const struct Projekt &a) {
    cout << a.izvajalec << a.nazivProjekta;
    cout << a.st_mesecev << " mesecev, " << a.placana_cena << " EUR\n\n";
}

void izpis_bin() {
    ifstream in("Projekti.bin", ios::binary);
    if(!in.is_open()) {
        return;
    }

    struct Projekt a;
    while(in.read((char*) &a, sizeof(a))) {
        izpis_projekt(a);
    }
    in.close();

}



int main() {

    vector<Projekti> objekti;
    napolni_objekte(objekti);

    int max_mesecev = najvec_mesecev(objekti);
    int plus;
    cout << "Za koliko zelite povecati objekt? ";
    cin >> plus;
    objekti[max_mesecev] = objekti[max_mesecev] + plus;

    zapisi_v_dat(max_mesecev, objekti[max_mesecev].dump());

    izpis_bin();

    char izvajalec[21];
    cin.ignore();
    cout << "Vnesite izvajalca: ";
    fgets(izvajalec, 21, stdin);

    for(int i = 0; i < objekti.size(); i++) {
        if(objekti[i] == izvajalec) {
            objekti[i].izpis();
        }
    }



    return 0;
}