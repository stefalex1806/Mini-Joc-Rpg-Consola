#pragma once
#include <fstream>
#include <string>
#include "personaje.hpp"
#include "arene.hpp"
using namespace std;

inline void incarca_personaje() {
    ifstream f("personaje.txt");
    if (!f.is_open()) return;
    int tip;
    while (f>>tip) {
        f.ignore();
        string nume,arma;
        int viata,damage,nivel_arma;
        getline(f,nume);
        f>>viata>>damage;
        f.ignore();
        getline(f,arma);
        f>>nivel_arma;
        Personaj* p=nullptr;
        if (tip == 1) p = new Mag(nume, viata, damage, arma,nivel_arma);
        else if (tip == 2) p = new Erou(nume, viata, damage, arma,nivel_arma);
        else if (tip == 3) p = new Goblin(nume, viata, damage, arma,nivel_arma);
        if (p) Storage<Personaj>::getInstance().adauga(p);
    }
    f.close();



}

inline void incarca_arene() {
    ifstream f("arene.txt");
    if (!f.is_open()) return;
    int tip;
    while (f>>tip) {
        f.ignore();
        string nume;
        int nivel,avantaj;
        getline(f,nume);
        f>>nivel>>avantaj;

        Arena* a = nullptr;
        if (tip == 1) a = new ArenaMag(nume, nivel, avantaj);
        else if (tip == 2) a = new ArenaErou(nume, nivel, avantaj);
        else if (tip == 3) a = new ArenaGoblin(nume, nivel, avantaj);

        if (a) Storage<Arena>::getInstance().adauga(a);
    }
    f.close();

}