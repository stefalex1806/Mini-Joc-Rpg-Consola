#include "personaje.hpp"
#include "exceptii.hpp"

int Personaj::nr_personaje = 0;

Personaj::Personaj(std::string n, int v, int d) : nume(n), viata(v), damage(d) {
    if (v <= 0) throw EroareCrearePersonaj("Viata nu poate fi zero sau negativa!");
    if (d < 0) throw EroareCrearePersonaj("Damage-ul nu poate fi negativ!");
    if (n == "") throw EroareCrearePersonaj("Personajul trebuie sa aiba un nume!");
    nr_personaje++;
}

Personaj::Personaj(const Personaj& other) : nume(other.nume), viata(other.viata), damage(other.damage) {
    nr_personaje++;
}

int Personaj::get_damage() const {
    return damage;
}
int Personaj::get_viata() const {
    return viata;
}

Personaj::~Personaj() { nr_personaje--; }

void swap(Personaj& first, Personaj& second) noexcept {
    std::swap(first.nume, second.nume);
    std::swap(first.viata, second.viata);
    std::swap(first.damage, second.damage);
}

Personaj& Personaj::operator=(const Personaj& other) {
    if (this != &other) {
        nume = other.nume;
        viata = other.viata;
        damage = other.damage;
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Personaj& p) {
    p.afisare(os);
    return os;
}

// === MAG ===
Mag::Mag(std::string n, int v, int d, std::string b,int a) : Personaj(n, v, d), bagheta(b) ,nivel_arma(a) {
}
Mag::Mag(const Mag& other) : Personaj(other), bagheta(other.bagheta) {}
void swap(Mag& first, Mag& second) noexcept {
    swap(static_cast<Personaj&>(first), static_cast<Personaj&>(second));
    std::swap(first.bagheta, second.bagheta);
}
Mag& Mag::operator=(Mag other) { swap(*this, other); return *this; }
void Mag::afisare_impl(std::ostream& os) const {
    os << "[Mag] " << nume << " | Viata: " << viata << " | DMG: " << damage << " | Arma: " << bagheta<<" , De nivel: "<<nivel_arma;
}

void Mag::castig() {
    if (nivel_arma<5) {
        nivel_arma++;
    }
}

void Mag::pierdere() {
    if (nivel_arma>1) {
        nivel_arma--;
    }
}

// === EROU ===
Erou::Erou(std::string n, int v, int d, std::string s,int a) : Personaj(n, v, d), sabie(s),nivel_arma(a) {}
Erou::Erou(const Erou& other) : Personaj(other), sabie(other.sabie) {}
void swap(Erou& first, Erou& second) noexcept {
    swap(static_cast<Personaj&>(first), static_cast<Personaj&>(second));
    std::swap(first.sabie, second.sabie);
}
Erou& Erou::operator=(Erou other) { swap(*this, other); return *this; }
void Erou::afisare_impl(std::ostream& os) const {
    os << "[Erou] " << nume << " | Viata: " << viata << " | DMG: " << damage << " | Arma: " << sabie<<" , De nivel: "<<nivel_arma;
}
void Erou::castig() {
    if (nivel_arma<5) {
        nivel_arma++;
    }
}

void Erou::pierdere() {
    if (nivel_arma>1) {
        nivel_arma--;
    }
}

// === GOBLIN ===
Goblin::Goblin(std::string n, int v, int d, std::string s,int a) : Personaj(n, v, d), sulita(s) ,nivel_arma(a){}
Goblin::Goblin(const Goblin& other) : Personaj(other), sulita(other.sulita) {}
void swap(Goblin& first, Goblin& second) noexcept {
    swap(static_cast<Personaj&>(first), static_cast<Personaj&>(second));
    std::swap(first.sulita, second.sulita);
}
Goblin& Goblin::operator=(Goblin other) { swap(*this, other); return *this; }
void Goblin::afisare_impl(std::ostream& os) const {
    os << "[Goblin] " << nume << " | Viata: " << viata << " | DMG: " << damage << " | Arma: " << sulita<<" , De nivel: "<<nivel_arma;
}
void Goblin::castig()  {
    if (nivel_arma<5) {
        nivel_arma++;
    }
}
void Goblin::pierdere() {
    if (nivel_arma>1) {
        nivel_arma--;
    }
}


// === SALVARI ===
void Mag::salvare(std::ostream& os) const {
    os << 1 << "\n" << nume << "\n" << viata << "\n" << damage << "\n" << bagheta << "\n"<< nivel_arma<<"\n";
}
void Erou::salvare(std::ostream& os) const {
    os << 2 << "\n" << nume << "\n" << viata << "\n" << damage << "\n" <<sabie << "\n"<< nivel_arma<<"\n";
}
void Goblin::salvare(std::ostream& os) const {
    os << 3 << "\n" << nume << "\n" << viata << "\n" << damage << "\n" << sulita << "\n"<< nivel_arma<<"\n";
}