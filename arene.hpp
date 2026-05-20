#pragma once
#include <iostream>
#include <string>
#include "personaje.hpp"

class Arena {
protected:
    std::string nume;
    int nivel;
    static int nr_arene;

    // Functie virtuala pura pentru NVI (Non-Virtual Interface)
    virtual void afisare_impl(std::ostream& os) const = 0; 

public:
    virtual void castig_gazda(Personaj* p)=0;
    virtual void pierdere_gazda(Personaj* p)=0;
    virtual void salvare(std::ostream& os) const = 0;
    Arena(std::string nume = "Arena Neutra", int nivel = 1);
    Arena(const Arena& other);
    virtual ~Arena();
    virtual int get_avantaj() const = 0;

    friend void swap(Arena& first, Arena& second) noexcept;
    Arena& operator=(const Arena& other);

    // Interfața NVI
    void afisare(std::ostream& os) const { afisare_impl(os); }
    
    // Functie virtuala pura (face clasa abstracta)
    virtual int get_avantaj_total() const = 0;
    int get_nivel() const { return nivel; }
    // Operator supraincarcat <<
    friend std::ostream& operator<<(std::ostream& os, const Arena& a);

    static int get_nr_arene() { return nr_arene; }
};

class ArenaMag : public Arena {
    int avantaj;
    void afisare_impl(std::ostream& os) const override;
public:
    void castig_gazda(Personaj* p) override;
    void pierdere_gazda(Personaj* p) override;
    void salvare(std::ostream& os) const override;
    ArenaMag(std::string nume = "Arena Mag Oarecare", int nivel = 1, int avantaj = 1);
    ArenaMag(const ArenaMag& other);
    friend void swap(ArenaMag& first, ArenaMag& second) noexcept;
    ArenaMag& operator=(ArenaMag other);
    int get_avantaj() const override{return avantaj;}
    int get_avantaj_total() const override;
};

class ArenaErou : public Arena {
    int avantaj;
    void afisare_impl(std::ostream& os) const override;
public:
    void castig_gazda(Personaj* p) override;
    void pierdere_gazda(Personaj* p) override;
    void salvare(std::ostream& os) const override;
    ArenaErou(std::string nume = "Arena Eroilor Standard", int nivel = 1, int avantaj = 1);
    ArenaErou(const ArenaErou& other);
    friend void swap(ArenaErou& first, ArenaErou& second) noexcept;
    ArenaErou& operator=(ArenaErou other);
    int get_avantaj() const override{return avantaj;}
    int get_avantaj_total() const override;
};

class ArenaGoblin : public Arena {
    int avantaj;
    void afisare_impl(std::ostream& os) const override;
public:
    void castig_gazda(Personaj* p) override;
    void pierdere_gazda(Personaj* p) override;
    void salvare(std::ostream& os) const override;
    ArenaGoblin(std::string nume = "Barlogul Goblinilor", int nivel = 1, int avantaj = 1);
    ArenaGoblin(const ArenaGoblin& other);
    friend void swap(ArenaGoblin& first, ArenaGoblin& second) noexcept;
    ArenaGoblin& operator=(ArenaGoblin other);
    int get_avantaj() const override{return avantaj;}
    int get_avantaj_total() const override;
};
