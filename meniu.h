#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <conio.h>
#include "personaje.hpp"
#include <windows.h>
#include "arene.hpp"
#include "lupte.hpp"
#include <fstream>
#include "exceptii.hpp"
using namespace std;

template <typename T>
class Storage {
    vector<T*> elemente;

    Storage()=default;

public:
    void salveaza(const string& nume_fisier) const {
        ofstream f(nume_fisier);
        if (!f.is_open()) {return;}
        for (auto* elem:elemente) {
            elem->salvare(f);
        }
        f.close();
    }
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

    static Storage<T>& getInstance() {
        static Storage<T> instance;
        return instance;
    }

    ~Storage() {
        for (auto* elem:elemente) {
            delete elem;
        }
    }

    void adauga(T* element) {
        elemente.push_back(element);

    }
    void sterge(size_t index) {
        if (index < elemente.size()) {
            delete elemente[index];
            elemente.erase(elemente.begin()+index);
        }
    }


    const vector<T*>& getElemente() const {
        return elemente;
    }



};

template <typename T>
bool printeaza_lista(const vector<T*>& lista) {
    if (lista.empty()) {
        return false;
    }
    int i = 1;
    for (T* elem : lista) {
        cout << i << "." << *elem << "\n";
        i++;
    }
    return true;
}

class PersonajFactory {
public:
    static Personaj* creazaPersonaj(int tip, string nume, int viata, int damage, string arma) {
        switch (tip) {
            case 1: return new Mag(nume, viata, damage, arma);
            case 2: return new Erou(nume, viata, damage, arma);
            case 3: return new Goblin(nume, viata, damage, arma);
            default: throw EroareCrearePersonaj("Tip personaj necunoscut în Factory!");
        }
    }
};

class ArenaFactory {
public:
    static Arena* creazaArena(int tip, string nume, int nivel, int avantaj) {
        switch (tip) {
            case 1: return new ArenaMag(nume, nivel, avantaj);
            case 2: return new ArenaErou(nume, nivel, avantaj);
            case 3: return new ArenaGoblin(nume, nivel, avantaj);
            default: throw EroareArena("Tip arena necunoscut în Factory!");
        }
    }
};

class Comanda {
public:
    virtual ~Comanda() {}
    virtual void Execute() const = 0;
};


class CrearePersonaj : public Comanda {
    bool isRunning;


    public:
    CrearePersonaj():isRunning(true) {}
    void Execute() const override {
        while (isRunning) {

            system("cls");
            cout<<"CREARE PERSONAJ\nCLASA:\n1.MAG    2.EROU     3.GOBLIN\n\n\n        0.RETURN";
            char tasta=_getch();
            int tip=tasta-'0';
            if (tip>3 || tip<0) {
                system("cls");
                cout<<"Comanda invalida";
                Sleep(2000);

                continue;
            }
            if (tip==0) {
            return;
            }
            string nume,arma;
            int viata,damage;
            system("cls");
            cout<<"Nume:";
            getline(cin>>ws,nume);
            Sleep(1000);
            system("cls");
            cout<<"Viata:";
            cin>>viata;
            Sleep(1000);
            system("cls");
            cout<<"Damage:";
            cin>>damage;
            Sleep(1000);
            system("cls");
            cout<<"Arma:";
            getline(cin>>ws,arma);
            Sleep(1000);
            system("cls");
            Personaj* p=nullptr;
            try {

                    p = PersonajFactory::creazaPersonaj(tip, nume, viata, damage, arma);

                    Storage<Personaj>::getInstance().adauga(p);
                    cout<<"Am creat personajul:\n"<<*p;

                    Sleep(3000);

            }catch(exception& e) {
                cout<<"Eroare: "<<e.what()<<endl;
                Sleep(3000);
            }

        }



    }


};




class CreareArena : public Comanda {
    bool isRunning;


public:
    CreareArena():isRunning(true) {}
    void Execute() const override {
        while (isRunning) {

            system("cls");
            cout<<"CREARE ARENA\nCLASA:\n1.MAG    2.EROU     3.GOBLIN\n\n\n        0.RETURN";
            char tasta=_getch();
            int tip=tasta-'0';
            if (tip>3 || tip<0) {
                system("cls");
                cout<<"Comanda invalida";
                Sleep(2000);

                continue;
            }
            if (tip==0) {
                return;
            }
            string nume;
            int nivel,avantaj;
            system("cls");
            cout<<"Nume:";
            getline(cin>>ws,nume);
            Sleep(1000);
            system("cls");
            cout<<"Nivel:";
            cin>>nivel;
            Sleep(1000);
            system("cls");
            cout<<"Avantaj:";
            cin>>avantaj;
            Sleep(1000);
            system("cls");
            Arena* p=nullptr;
            try {
                p = ArenaFactory::creazaArena(tip, nume, nivel, avantaj);

                Storage<Arena>::getInstance().adauga(p);
                cout<<"Am creat arena:\n"<<*p;

                Sleep(3000);
            }catch(exception& e) {
                cout<<"Eroare: "<<e.what()<<endl;
                Sleep(3000);
            }

        }



    }

};

class AranjareLupta : public Comanda {
bool isRunning;

public:
    AranjareLupta():isRunning(true) {}

    void Execute() const override {
        system("cls");
        if (Storage<Personaj>::getInstance().getElemente().size()<2) {
            if (Storage<Arena>::getInstance().getElemente().size()<1) {
                cout<<"Nu ai creat destule personaje si arene!";
                Sleep(2500);
                return;
            }
            cout<<"Nu ai creat destule personaje!";
            Sleep(2500);
            return;
        }
        if (Storage<Arena>::getInstance().getElemente().size()<1) {
            cout<<"Nu ai creat nicio arena!";
            Sleep(2500);
            return;
        }


        while (isRunning) {
            system("cls");
            cout<<"Alege Personaje:\n";
            const vector<Personaj*>& personaje=afisare_personaje();
            cout<<"0.Cancel\n";
            int p=-1;
            while (p>personaje.size() || p<-1) {
                cin>>p;
            }
            if (p==0)return;
            Personaj* p1=personaje[p-1];
            cout<<"Personaj 1:"<<*p1<<endl;
            while (p<-1|| p>personaje.size() || personaje[p-1]==p1 ) {
                cin>>p;
                if (p==0)return;
            }

            Personaj* p2=personaje[p-1];
            cout<<"Personaj 2:"<<*p2<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Alege arena:\n";
            const vector<Arena*>& arene=afisare_arene();
            cout<<"0.Cancel\n";
            p=-1;
            while (p>arene.size() || p<-1) {
                cin>>p;
            }
            if (p==0)return;
            Arena* a=arene[p-1];
            cout<<"Arena aleasa:"<<*a;
            Sleep(1000);
            system("cls");
            Lupta l(p1,p2,a);
            cout<<"1.Joc         2.Simulare";
            p=0;
            while (p!=1 && p!=2) {
               char t=_getch();
                p=t-'0';
            }
            system("cls");
            if (p==1) {
                l.desfasurare();
            }
            if (p==2) {
                l.simulare();
            }

            Sleep(5000);

            while (true) {
                system("cls");
                cout<<"Vrei sa mai faci o lupta?\n1.DA     2.NU\n";
                char t=_getch();
                p=t-'0';

                if (p==1) {
                    break;
                }
                if (p==2) {
                    return;
                }
            }


        }
    }
     const vector<Personaj*>& afisare_personaje() const{

        const vector<Personaj*>& personaje=Storage<Personaj>::getInstance().getElemente();
        printeaza_lista(personaje);
        return personaje;
    }

    const vector<Arena*>& afisare_arene() const {

        const vector<Arena*>& arene=Storage<Arena>::getInstance().getElemente();
        printeaza_lista(arene);
        return arene;
    }
    ~AranjareLupta(){isRunning=false;}
};
class StergerePersonaj: public Comanda {
    public:
    void Execute() const override {
        while (true){
            system("cls");
            cout<<"STERGERE PERSONAJ\n\n";
            const vector<Personaj*>& personaje=Storage<Personaj>::getInstance().getElemente();
            if (!printeaza_lista(personaje)) {
                cout<<"Nu exista personaje";
                Sleep(1000);
                return;
            }
            cout<<"\n0.Cancel\nAlege personajul de sters:";
            int alegere;
            cin>>alegere;
            if (alegere==0)return;
            if (alegere>0 &&alegere<=personaje.size()) {
                Storage<Personaj>::getInstance().sterge(alegere-1);
                cout<<"Personaj Sters Cu Succes!\n";
                Sleep(1500);
            }else {
                cout<<"Alegere Invalida\n";
                Sleep(1000);

            }

        }
    }
};

class StergereArena: public Comanda {
public:
    void Execute() const override {
        while (true){
            system("cls");
            cout<<"STERGERE ARENA\n\n";
            const vector<Arena*>& arene=Storage<Arena>::getInstance().getElemente();
            if (!printeaza_lista(arene)) {
                cout<<"Nu exista arene";
                Sleep(1000);
                return;
            }
            cout<<"\n0.Cancel\nAlege arena de sters:";
            int alegere;
            cin>>alegere;
            if (alegere==0)return;
            if (alegere>0 &&alegere<=arene.size()) {
                Storage<Arena>::getInstance().sterge(alegere-1);
                cout<<"Arena Stearsa Cu Succes!\n";
                Sleep(1500);
            }else {
                cout<<"Alegere Invalida\n";
                Sleep(1000);

            }

        }
    }
};
#include "salvare.h"

class Meniu {
    bool isRunning;
    Comanda* comenzi[6];

    Meniu():isRunning(true) {
        incarca_arene();
        incarca_personaje();
        comenzi[1]=new CrearePersonaj();
        comenzi[2]=new StergerePersonaj();

        comenzi[3]=new CreareArena();
        comenzi[4]=new StergereArena();
        comenzi[5]=new AranjareLupta();

    }



     public:
    Meniu(const Meniu& )=delete;
    Meniu operator=(const Meniu& )=delete;

    static Meniu& getInstance() {
        static Meniu instance;
        return instance;
    }

    void run() {
        while (isRunning) {
            system("cls");
            cout<<"MENIU PRINCIPAL\n\n1.Creare Personaj\n2.Stergere Personaj\n3.Creare Arena\n4.Stergere Arena\n5.Aranjare Lupta\n6.Tutorial\n0.Nu Mai vreau sa joc...";
            char tasta=_getch();
            int comanda=tasta-'0';
            if (comanda>6 || comanda<0) {
                system("cls");
                cout<<"Comanda Invalida"<<endl;
                Sleep(2000);
                continue;
            }
            if (comanda==0) {
                system("cls");
                cout<<"Sigur vrei sa inchizi programul?\n1.DA     2.NU";
                char t=_getch();
                int c=t-'0';
                if (c==1) {
                    system("cls");
                    cout<<"Se salveaza datele...";
                    Storage<Personaj>::getInstance().salveaza("personaje.txt");
                    Storage<Arena>::getInstance().salveaza("arene.txt");
                    Sleep(500);
                    isRunning=false;
                    break;
                }else if (c==2) {
                    continue;
                }else {
                    system("cls");
                    cout<<"Comanda Invalida";
                    Sleep(1000);
                    continue;
                }



            }
            if (comanda==6) {
                system("cls");
                cout << "===============================================================\n";
                cout << "                 TUTORIAL SI REGULI DE LUPTA                   \n";
                cout << "===============================================================\n\n";

                cout << "1. AVANTAJUL DE CLASA (Piatra-Hartie-Foarfeca)\n";
                cout << "   - Magul are avantaj pe Erou.\n";
                cout << "   - Eroul are avantaj pe Goblin.\n";
                cout << "   - Goblinul are avantaj pe Mag.\n";
                cout << "   * Avantajul ofera +10% Damage in lupta.\n\n";

                cout << "2. SISTEMUL DE MANA SI PROGRESIE\n";
                cout << "   - Incepi lupta cu 5 Mana. Câștigi 1 Mana pe tura.\n";
                cout << "   - Costul abilitatilor scade pe masura ce arma creste in nivel:\n";
                cout << "     (Nvl 1: 8 Mana | Nvl 2: 7 | Nvl 3: 6 | Nvl 4: 5 | Nvl 5: 4 Mana).\n";
                cout << "   - Nivelul armei creste la victorie si scade la infrangere[cite: 13].\n\n";

                cout << "3. ABILITATI PERSONAJE\n";
                cout << "   - Erou (Parry): Blocheaza complet atacul oponentului si efectul arenei pentru o runda.\n";
                cout << "   - Mag (Freeze): Ingheata oponentul timp de 2 runde (nu poate actiona).\n";
                cout << "   - Goblin (Dezarmare): Oponentul isi pierde toata mana si da doar damage/3 o runda.\n\n";

                cout << "4. ABILITATI ARENA (Avantaj pentru gazda)\n";
                cout << "   - Arena Erou: Capcane care aplica sangerare (scade 3-5-7% din viata/runda).\n";
                cout << "   - Arena Mag: Vraja care scade instant 10-15-20% din viata oponentului la inceput.\n";
                cout << "   - Arena Goblin: Sabotaj la intrare care scade 1-2-3 nivele ale armei oponentului.\n\n";

                cout << "===============================================================\n";
                cout << "Apasa orice tasta pentru a te intoarce in Meniu...";

                _getch();
                continue;
            }
            comenzi[comanda]->Execute();



        }
        system("cls");
        cout<<"Iesire program";
        Sleep(3000);
        system("cls");
        return;



    }






};