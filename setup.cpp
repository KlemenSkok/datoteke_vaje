#include <iostream>
#include <fstream>
#include <cstring>
#include "utils.h"

using namespace std;


void vpisi_sortirano(struct Projekt a) {
    ifstream in("Projekti.bin", ios::binary);
    
    if(!in.is_open()) {
        // nardi nov file
        ofstream out("Projekti.bin", ios::binary);
        out.write((char*) &a, sizeof(struct Projekt));
        out.close();
    }
    else {
        ofstream out("ptmp.bin", ios::binary);
        bool je_vpisan = false;
        struct Projekt b;
        while(in.read((char*) &b, sizeof(struct Projekt))) {
            if(!je_vpisan && strcmp(a.izvajalec, b.izvajalec) < 0) {
                je_vpisan = true;
                out.write((char*) &a, sizeof(struct Projekt));
            }
            out.write((char*) &b, sizeof(struct Projekt));
        }
        if(!je_vpisan)
            out.write((char*) &a, sizeof(struct Projekt));
            
        in.close();
        out.close();
        remove("Projekti.bin");
        rename("ptmp.bin", "Projekti.bin");
    }
}

void vpisi_txt(string izv) {
    ofstream out("Izvajalec.txt", ios::app);
    out << izv;
}

void napolni_projekt(struct Projekt &a) {
    //cin.ignore();
    fgets(a.izvajalec, 21, stdin);
    fgets(a.nazivProjekta, 21, stdin);
    cin >> a.st_mesecev;
    cin >> a.placana_cena;
    cin.ignore();
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

    for(int i = 0; i < 5; i++) {
        struct Projekt a;
        napolni_projekt(a);
        vpisi_sortirano(a);
        vpisi_txt(a.izvajalec);
    } 

    izpis_bin();


    return 0;
}