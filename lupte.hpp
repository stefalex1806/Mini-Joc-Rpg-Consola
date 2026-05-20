#pragma once
#include "arene.hpp"
#include "personaje.hpp"
#include <windows.h>
#include <conio.h>
struct gestionare_lupta {
    int tura,mana1,mana2,id1,id2,abilitate_arena,nivel_arena,istoric[3];


    gestionare_lupta(int t,int m1,int m2,int d1,int d2,int na) {
        tura = t;
        mana1 = m1;
        mana2 = m2;
        id1 = d1;
        id2 = d2;
        nivel_arena=na;
        abilitate_arena=0;
        for (int i=0;i<3;i++) {
            istoric[i]=0;
        }

    }
};

class Lupta {
    Personaj *p1, *p2;
    Arena* locatie;

public:
    Lupta(Personaj *p1, Personaj *p2, Arena* locatie) : p1(p1), p2(p2), locatie(locatie) {}

    void simulare() {

        std::cout << "\n------Inceput De Lupta------\nLOCATIE: " << *locatie << "\n";
        std::cout << "\nPrimul Competitor: " << *p1;
        std::cout << "\nAl Doilea Competitor: " << *p2 << "\n\n";
        Sleep(1000);
        // Preia puterea direct prin functia High-Level
        int putere_p1 = p1->get_putere_baza();
        int putere_p2 = p2->get_putere_baza();
        
        int clasa_p1 = p1->get_id_clasa(); // 1=Mag, 2=Erou, 3=Goblin
        int clasa_p2 = p2->get_id_clasa();

        int avantaj = locatie->get_avantaj_total();

        // Downcast pentru a verifica tipul arenei
        if (dynamic_cast<ArenaMag*>(locatie)) {
            if (clasa_p1 == 1) { putere_p1 = (putere_p1 * (100 + avantaj)) / 100; std::cout << "P1(Mag) ia bonus arena!\n"; }
            else if (clasa_p1 == 2) { putere_p1 = (putere_p1 * (100 - avantaj)) / 100; std::cout << "P1(Erou) ia penalizare arena!\n"; }
            
            if (clasa_p2 == 1) { putere_p2 = (putere_p2 * (100 + avantaj)) / 100; std::cout << "P2(Mag) ia bonus arena!\n"; }
            else if (clasa_p2 == 2) { putere_p2 = (putere_p2 * (100 - avantaj)) / 100; std::cout << "P2(Erou) ia penalizare arena!\n"; }
        }
        else if (dynamic_cast<ArenaErou*>(locatie)) {
            if (clasa_p1 == 2) { putere_p1 = (putere_p1 * (100 + avantaj)) / 100; std::cout << "P1(Erou) ia bonus arena!\n"; }
            else if (clasa_p1 == 3) { putere_p1 = (putere_p1 * (100 - avantaj)) / 100; std::cout << "P1(Goblin) ia penalizare arena!\n"; }
            
            if (clasa_p2 == 2) { putere_p2 = (putere_p2 * (100 + avantaj)) / 100; std::cout << "P2(Erou) ia bonus arena!\n"; }
            else if (clasa_p2 == 3) { putere_p2 = (putere_p2 * (100 - avantaj)) / 100; std::cout << "P2(Goblin) ia penalizare arena!\n"; }
        }
        else if (dynamic_cast<ArenaGoblin*>(locatie)) {
            if (clasa_p1 == 3) { putere_p1 = (putere_p1 * (100 + avantaj)) / 100; std::cout << "P1(Goblin) ia bonus arena!\n"; }
            else if (clasa_p1 == 1) { putere_p1 = (putere_p1 * (100 - avantaj)) / 100; std::cout << "P1(Mag) ia penalizare arena!\n"; }
            
            if (clasa_p2 == 3) { putere_p2 = (putere_p2 * (100 + avantaj)) / 100; std::cout << "P2(Goblin) ia bonus arena!\n"; }
            else if (clasa_p2 == 1) { putere_p2 = (putere_p2 * (100 - avantaj)) / 100; std::cout << "P2(Mag) ia penalizare arena!\n"; }
        }
        Sleep(1000);

        // Avantaj de clasa: Mag(1) > Erou(2) > Goblin(3) > Mag(1)
        if ((clasa_p1 == 1 && clasa_p2 == 2) || (clasa_p1 == 2 && clasa_p2 == 3) || (clasa_p1 == 3 && clasa_p2 == 1)) {
            std::cout << "Primul Competitor are avantaj de clasa (+10%)!\n";
            putere_p1 = (putere_p1 * 110) / 100;

        }
        else if ((clasa_p2 == 1 && clasa_p1 == 2) || (clasa_p2 == 2 && clasa_p1 == 3) || (clasa_p2 == 3 && clasa_p1 == 1)) {
            std::cout << "Al Doilea Competitor are avantaj de clasa (+10%)!\n";
            putere_p2 = (putere_p2 * 110) / 100;

        }
        Sleep(1000);

        if (putere_p1 > putere_p2) {
            std::cout << ((putere_p1 - putere_p2 > 150) ? "Lupta usoara pentru primul!\n" : "Dupa o lupta crunta a castigat primul.\n");
            p1->castig();
            p2->pierdere();
            if (clasa_p1!=clasa_p2) {
                locatie->castig_gazda(p1);
                locatie->pierdere_gazda(p2);
            }


        } else if (putere_p2 > putere_p1) {
            std::cout << ((putere_p2 - putere_p1 > 150) ? "Lupta usoara pentru al doilea!\n" : "Dupa o lupta crunta a castigat al doilea.\n");
            p2->castig();
            p1->pierdere();
            if (clasa_p1!=clasa_p2) {
                 locatie->castig_gazda(p2);
                 locatie->pierdere_gazda(p1);
            }


        } else {
            std::cout << "EGALITATE!\n";
        }
    }
    void desfasurare() {
        std::cout << "\n------Inceput De Lupta------\nLOCATIE: " << *locatie << "\n";
        std::cout << "\nPrimul Competitor: " << *p1;
        std::cout << "\nAl Doilea Competitor: " << *p2 << "\n\n";
        Sleep(3000);
        int n1init=p1->get_nivel_arma();
        int n2init=p2->get_nivel_arma();
        std::string nume_1, nume_2;
        nume_1=p1->get_nume();
        nume_2=p2->get_nume();
        int viata_1,viata_2,damage_1,damage_2;
        viata_1=p1->get_viata();
        damage_1=p1->get_damage();
        viata_2=p2->get_viata();
        damage_2=p2->get_damage();
        int clasa_p1, clasa_p2;
        clasa_p1 = p1->get_id_clasa();
        clasa_p2 = p2->get_id_clasa();
        gestionare_lupta gestionare(1,5,5,p1->get_id_clasa(),p2->get_id_clasa(),locatie->get_avantaj());


        if (clasa_p1 != clasa_p2) {

            if ((clasa_p1 == 1 && clasa_p2 == 2) || (clasa_p1 == 2 && clasa_p2 == 3) || (clasa_p1 == 3 && clasa_p2 == 1)) {
                std::cout <<nume_1<< " are avantaj de clasa (+10% damage)!         Damage:"<<damage_1<<"--->"<<(damage_1 * 110) / 100<<"\n";
;
                damage_1 = (damage_1 * 110) / 100;

            }
            else if ((clasa_p2 == 1 && clasa_p1 == 2) || (clasa_p2 == 2 && clasa_p1 == 3) || (clasa_p2 == 3 && clasa_p1 == 1)) {
                std::cout << nume_2<< " are avantaj de clasa (+10% damage)!        Damage:"<<damage_2<<"--->"<<(damage_2 * 110) / 100<<"\n";
                damage_2 = (damage_2 * 110) / 100;

            }

            //Acordare de avantaje de arena si selectarea celui care incepe

            if (dynamic_cast<ArenaMag*>(locatie)) {
                if (clasa_p2 == 1) {
                    gestionare.tura=2;
                    std::cout<<nume_2<<" primeste avantaj de arena(+"<<5+locatie->get_nivel()<<"% Viata)!        Viata:"<<viata_2<<"--->"<<(viata_2*(100+5+locatie->get_nivel()))/100<<"\n";
                    Sleep(1000);
                    std::cout<<"Deoarece "<<nume_2<<" este pe arena sa, acesta va incepe primul.\n";
                    viata_2=(viata_2*(100+5+locatie->get_nivel()))/100;
                    Sleep(1000);
                    if (clasa_p1==2) {
                        gestionare.abilitate_arena=11;
                        std::cout<<nume_1<<" a fost vrajit usor de magician in arena sa (-"<<gestionare.nivel_arena*5<<"% Viata)!        Viata:"<<viata_1<<"--->"<<viata_1*(100-gestionare.nivel_arena*5)/100<<"\n";
                        viata_1=viata_1*(100-gestionare.nivel_arena*5)/100;
                    }
                }
                if (clasa_p1==1) {
                    std::cout<<nume_1<<" primeste avantaj de arena(+"<<5+locatie->get_nivel()<<"% Viata)!        Viata:"<<viata_1<<"--->"<<(viata_1*(100+5+locatie->get_nivel()))/100<<"\n";
                    viata_1=(viata_1*(100+5+locatie->get_nivel()))/100;
                    if (clasa_p2==2) {
                        gestionare.abilitate_arena=21;
                        std::cout<<nume_2<<" a fost vrajit usor de magician in arena sa (-"<<gestionare.nivel_arena*5<<"% Viata)!        Viata:"<<viata_2<<"--->"<<viata_2*(100-gestionare.nivel_arena*5)/100<<"\n";
                        viata_2=viata_2*(100-gestionare.nivel_arena*5)/100;
                    }
                }
            }
            else if (dynamic_cast<ArenaErou*>(locatie)) {
                if (clasa_p2 == 2) {
                    gestionare.tura=2;

                    std::cout<<nume_2<<" primeste avantaj de arena(+"<<5+locatie->get_nivel()<<"% Viata)!        Viata:"<<viata_2<<"--->"<<(viata_2*(100+5+locatie->get_nivel()))/100<<"\n";
                    Sleep(1000);
                    std::cout<<"Deoarece "<<nume_2<<" este pe arena sa, acesta va incepe primul.\n";
                    viata_2=(viata_2*(100+5+locatie->get_nivel()))/100;
                    if (clasa_p1==3) {
                        std::cout<<nume_1<<" sangereaza din cauza capcanelor puse de erou in arena sa (-"<<(gestionare.nivel_arena-1)*3+2<<"% Viata in fiecare runda)!\n";
                        gestionare.abilitate_arena=12;
                    }

                }
                if (clasa_p1==2) {
                    std::cout<<nume_1<<" primeste avantaj de arena(+"<<5+locatie->get_nivel()<<"% Viata)!        Viata:"<<viata_1<<"--->"<<(viata_1*(100+5+locatie->get_nivel()))/100<<"\n";
                    viata_1=(viata_1*(100+5+locatie->get_nivel()))/100;
                    if (clasa_p2==3) {
                        std::cout<<nume_2<<" sangereaza din cauza capcanelor puse de erou in arena sa (-"<<(gestionare.nivel_arena-1)*3+2<<"% Viata in fiecare runda)!\n";
                        gestionare.abilitate_arena=22;
                    }

                }
            }
            else if (dynamic_cast<ArenaGoblin*>(locatie)) {
                if (clasa_p2 == 3) {
                    gestionare.tura=2;
                    std::cout<<nume_2<<" primeste avantaj de arena(+"<<5+locatie->get_nivel()<<"% Viata)!        Viata:"<<viata_2<<"--->"<<(viata_2*(100+5+locatie->get_nivel()))/100<<"\n";
                    Sleep(1000);
                    std::cout<<"Deoarece "<<nume_2<<" este pe arena sa, acesta va incepe primul.\n";
                    viata_2=(viata_2*(100+5+locatie->get_nivel()))/100;
                    if (clasa_p1==1) {
                        std::cout<<nume_1<<" este sabotat de goblin la intrarea in arena(-"<<gestionare.nivel_arena<<" nivele arma)!        Nivel Arma:"<<p1->get_nivel_arma()<<"--->";
                        if (p1->get_nivel_arma()<=gestionare.nivel_arena) {
                            p1->set_nivel_arma(1);
                        }else p1->set_nivel_arma(p1->get_nivel_arma()-gestionare.nivel_arena);
                        std::cout<<p1->get_nivel_arma()<<"\n";
                        gestionare.abilitate_arena=13;

                    }
                }
                if (clasa_p1==3) {
                    std::cout<<nume_1<<" primeste avantaj de arena(+"<<5+locatie->get_nivel()<<"% Viata)!        Viata:"<<viata_1<<"--->"<<(viata_1*(100+5+locatie->get_nivel()))/100<<"\n";
                    viata_1=(viata_1*(100+5+locatie->get_nivel()))/100;
                }
                if (clasa_p2==1) {
                    std::cout<<nume_2<<" este sabotat de goblin la intrarea in arena(-"<<gestionare.nivel_arena<<" nivele arma)!        Nivel Arma:"<<p2->get_nivel_arma()<<"--->";
                    if (p2->get_nivel_arma()<=gestionare.nivel_arena) {
                        p2->set_nivel_arma(1);
                    }else p2->set_nivel_arma(p2->get_nivel_arma()-gestionare.nivel_arena);
                    std::cout<<p2->get_nivel_arma()<<"\n";
                    gestionare.abilitate_arena=23;

                }
            }

        }
        int cost_abilitate1, cost_abilitate2;
        cost_abilitate1 = 9-p1->get_nivel_arma();
        cost_abilitate2 = 9-p2->get_nivel_arma();
        Sleep(4000);
        if (gestionare.tura==1) {
            std::cout<<"Va incepe "<<nume_1;
        }
        Sleep(3000);


        while (viata_1>0 && viata_2>0) {


            system("cls");
            if (gestionare.tura==1) {
                std::cout<<"Tura lui: "<<nume_1<<"\n";
                std::cout<<"\n"<<nume_1<<", Viata:"<<viata_1<<", Damage:"<<damage_1<<" , Mana:"<<gestionare.mana1<<" ------------------> "<<nume_2<<", Viata:"<<viata_2<<", Damage:"<<damage_2<<" , Mana:"<<gestionare.mana2<<"\n";
            }else {
                std::cout<<"Tura lui: "<<nume_2<<"\n";
                std::cout<<"\n"<<nume_2<<", Viata:"<<viata_2<<", Damage:"<<damage_2<<" , Mana:"<<gestionare.mana2<<" ------------------> "<<nume_1<<", Viata:"<<viata_1<<", Damage:"<<damage_1<<" , Mana:"<<gestionare.mana1<<"\n";
            }
            if (gestionare.istoric[0]!=0 && gestionare.istoric[0]!=2) {

                std::cout<<"Esti inghetat!";
                Sleep(3000);
                gestionare=schimba_tura(gestionare);
                gestionare.istoric[0]--;
                continue;

            }else if (gestionare.istoric[0]==2) {
                gestionare.istoric[0]--;
            }
            std::cout<<"\nCe alegi?\n1.Loveste      2.Foloseste abilitate(-";
            if (gestionare.tura==1)std::cout<<cost_abilitate1;
            else std::cout<<cost_abilitate2;
            std::cout<<" Mana)       0.Renunta";

            int c=-1;
            while (c!=1 && c!=2 && c!=0) {
                char t=_getch();
                c=t-'0';
                if (gestionare.tura==1 && cost_abilitate1>gestionare.mana1 && c==2) {
                    system("cls");
                    std::cout<<"NU AI DESTULA MANA!";
                    Sleep(3000);
                    c=-1;
                    break;
                }
                if (gestionare.tura==2 && cost_abilitate2>gestionare.mana2 && c==2) {
                    system("cls");
                    std::cout<<"NU AI DESTULA MANA!";
                    Sleep(3000);
                    c=-1;
                    break;
                }
            }
            if (c==-1) {
                continue;
            }
            if (c==1) {
                system("cls");
                if (gestionare.tura==1) {
                    loveste(1,2,nume_1,nume_2,damage_1,viata_2 ,gestionare);
                    Sleep(2000);
                }
                else {
                    loveste(2,1,nume_2,nume_1,damage_2,viata_1 ,gestionare);
                    Sleep(2000);
                }

            }
            else if (c==2) {
               if (gestionare.tura==1) {
                  Foloseste_abilitate(gestionare,cost_abilitate1,1);


               }else {
                   Foloseste_abilitate(gestionare,cost_abilitate2,2);
               }


                Sleep(2000);

            }else {
                system("cls");
                std::cout<<"Sigur vrei sa renunti?\n1.Da     2.Nu";
                int r=-1;
                while (r!=1 && r!=2) {
                    char t=_getch();
                    r=t-'0';
                }
                if (r==1) {
                    system("cls");
                    if (gestionare.tura==2) {
                        p1->castig();
                        p2->pierdere();
                        if (clasa_p1!=clasa_p2) {
                            locatie->castig_gazda(p1);
                            locatie->pierdere_gazda(p2);
                        }
                        std::cout<<nume_2<<" se da batut...\n";
                        Sleep(2000);
                        std::cout<<nume_1<<" CASTIGA!!!!";
                        return;
                    }
                    else {


                        p2->castig();
                        p1->pierdere();
                        if (clasa_p1!=clasa_p2) {
                            locatie->castig_gazda(p2);
                            locatie->pierdere_gazda(p1);
                            std::cout<<nume_1<<" se da batut...\n";
                            Sleep(2000);
                            std::cout<<nume_2<<" CASTIGA!!!!";
                            return;
                        }
                    }
                }else {
                    continue;
                }

            }
            if (gestionare.abilitate_arena%10==2) {
                if (gestionare.abilitate_arena/10==1) {
                    std::cout<<"\n"<<nume_1<<" -"<<(viata_1*((gestionare.nivel_arena-1)*3+2))/100<<" viata din cauza sangerarii";
                    viata_1=(viata_1*(100-((gestionare.nivel_arena-1)*3+2)))/100;

                }
                if (gestionare.abilitate_arena/10==2) {
                    std::cout<<"\n"<<nume_2<<" -"<<(viata_2*((gestionare.nivel_arena-1)*3+2))/100<<" viata din cauza sangerarii";
                    viata_2=(viata_2*(100-((gestionare.nivel_arena-1)*3+2)))/100;

                }

            }
            Sleep(5000);
            gestionare=schimba_tura(gestionare);
        }
        system("cls");
        p1->set_nivel_arma(n1init);
        p2->set_nivel_arma(n2init);
        if (viata_1>0) {
            std::cout<<nume_1<<" CASTIGA!!!!";
            p1->castig();
            p2->pierdere();
            if (clasa_p1!=clasa_p2) {
                locatie->castig_gazda(p1);
                locatie->pierdere_gazda(p2);
            }
        }
        if (viata_2>0) {
            std::cout<<nume_2<<" CASTIGA!!!!";
            p2->castig();
            p1->pierdere();
            if (clasa_p1!=clasa_p2) {
                locatie->castig_gazda(p2);
                locatie->pierdere_gazda(p1);
            }


        }
    }

    void Foloseste_abilitate(gestionare_lupta &gestionare,int cost,int i) {
        std::cout<<std::endl;
        for (int j=0;j<3;j++) {

            if (j==1 && gestionare.istoric[1]==1 ) {

                gestionare.istoric[j]=0;
                std::cout<<"Oponentul a blocat abilitatea";
                if (i==1) {
                    gestionare.mana1-=(cost+1);
                }else gestionare.mana2-=(cost+1);
                return;
            } gestionare.istoric[j]=0;

        }
        if (i==1) {

                if (gestionare.id1==1) {
                    std::cout<<"Foloseste Freeze!";
                    gestionare.istoric[0]=3;

                }else if (gestionare.id1==2) {
                    std::cout<<"Foloseste Parry!";
                    gestionare.istoric[1]=1;
                }else {
                    std::cout<<"Foloseste Disarm!";
                    gestionare.mana2=-1;
                    gestionare.istoric[2]=1;
                }
                gestionare.mana1-=(cost+1);

        }
        else {

                if (gestionare.id2==1) {
                    std::cout<<"Foloseste Freeze!";
                    gestionare.istoric[0]=3;
                }else if (gestionare.id2==2) {
                    std::cout<<"Foloseste Parry!";
                    gestionare.istoric[1]=1;
                }else {
                    std::cout<<"Foloseste Disarm!";
                    gestionare.istoric[2]=1;
                    gestionare.mana1=-1;
                }
                gestionare.mana2-=(cost+1);

        }

    }



    gestionare_lupta schimba_tura(gestionare_lupta gestionare) {
        if (gestionare.tura==1) {
            gestionare.tura=2;
        }
        else gestionare.tura=1;
        gestionare.mana1++;
        gestionare.mana2++;

        return gestionare;


    }

    void loveste(int p1 , int p2,std::string nume_1,std::string nume_2,int damage_1,int &viata_2, gestionare_lupta &gestionare) {
        if ( gestionare.istoric[1]==1) {
            std::cout<<"\n"<<nume_2<<" a blocat atacul";
            gestionare.istoric[1]=0;
            return;
        }else if (gestionare.istoric[2]==1) {
                std::cout<<nume_1<<" l-a lovit pe "<<nume_2<<" si a dat "<<damage_1/3<<" damage deoarece era dezarmat( Viata "<<nume_2<<" -"<<damage_1/3<<")!\n";
                viata_2=viata_2-damage_1/3;
                gestionare.istoric[2]=0;
                return;
            }
        std::cout<<nume_1<<" l-a lovit pe "<<nume_2<<" si a dat "<<damage_1<<" damage( Viata "<<nume_2<<" -"<<damage_1<<")!\n";
        viata_2=viata_2-damage_1;
    }

};