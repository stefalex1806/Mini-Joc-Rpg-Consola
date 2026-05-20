#pragma once
#include <iostream>
#include <string>

class Personaj {
protected:
    std::string nume;
    int viata;
    int damage;
    static int nr_personaje;

    virtual void afisare_impl(std::ostream& os) const = 0;

public:
    std::string get_nume() const { return nume; }
    virtual void castig() =0;
    virtual void pierdere()=0;
    int get_viata() const ;
    int get_damage() const ;
    virtual void set_nivel_arma(int nivel_arma) =0;
    virtual int get_nivel_arma() const =0 ;
    virtual void salvare(std::ostream& os) const = 0;
    Personaj(std::string nume, int viata, int damage);
    Personaj(const Personaj& other);
    virtual ~Personaj();

    friend void swap(Personaj& first, Personaj& second) noexcept;
    Personaj& operator=(const Personaj& other);

    // Interfața NVI
    void afisare(std::ostream& os) const { afisare_impl(os); }

    // Funcții High-Level (Pentru a evita viata si damage in clase externe)
    virtual int get_putere_baza() const { return viata + damage * 10; }
    virtual int get_id_clasa() const = 0; // 1=Mag, 2=Erou, 3=Goblin

    friend std::ostream& operator<<(std::ostream& os, const Personaj& p);

    static int get_nr_personaje() { return nr_personaje; }
};

class Mag : public Personaj {
    std::string bagheta;
    int nivel_arma;
    std::string abilitate="Freeze";
    void afisare_impl(std::ostream& os) const override;
public:
    void set_nivel_arma(int nivel_arma) override{this->nivel_arma = nivel_arma;};
    void salvare(std::ostream& os) const override;
    Mag(std::string nume = "Mag Anonim", int viata = 110, int damage = 12, std::string bagheta = "Bagheta Oarecare",int nivel_arma = 1);
    Mag(const Mag& other);
    friend void swap(Mag& first, Mag& second) noexcept;
    Mag& operator=(Mag other);
    void castig()  override;
    void pierdere()override;
    int get_nivel_arma() const override{ return nivel_arma; }
    int get_id_clasa() const override { return 1; }
};

class Erou : public Personaj {
    std::string sabie;
    int nivel_arma;
    std::string abilitate="Parry";
    void afisare_impl(std::ostream& os) const override;
public:
    void set_nivel_arma(int nivel_arma) override{this->nivel_arma = nivel_arma;};
    void salvare(std::ostream& os) const override;
    Erou(std::string nume = "Erou Anonim", int viata = 160, int damage = 8, std::string sabie = "Sabie Oarecare",int nivel_arma = 1);
    Erou(const Erou& other);
    friend void swap(Erou& first, Erou& second) noexcept;
    Erou& operator=(Erou other);
    void castig()  override;
    void pierdere()override;
    int get_nivel_arma() const override{ return nivel_arma; }
    int get_id_clasa() const override { return 2; }
};

class Goblin : public Personaj {
    std::string sulita;
    int nivel_arma;
    std::string abilitate="Disarm";
    void afisare_impl(std::ostream& os) const override;
public:
    void set_nivel_arma(int nivel_arma) override{this->nivel_arma = nivel_arma;};
    void salvare(std::ostream& os) const override;
    Goblin(std::string nume = "Goblin Anonim", int viata = 80, int damage = 18, std::string sulita = "Sulita Oarecare",int nivel_arma = 1);
    Goblin(const Goblin& other);
    friend void swap(Goblin& first, Goblin& second) noexcept;
    Goblin& operator=(Goblin other);
    void castig()  override;
    void pierdere()override;
    int get_nivel_arma() const override{ return nivel_arma; }
    int get_id_clasa() const override { return 3; }
};