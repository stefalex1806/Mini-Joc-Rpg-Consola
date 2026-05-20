Enunț

O companie de dezvoltare software are nevoie de implementarea unei aplicații C++ orientate pe obiecte pentru gestionarea unui sistem complex de combat tip RPG (Role-Playing Game). Aplicația trebuie să gestioneze entități de tip „Personaj” și „Arenă”, precum și logica unei lupte desfășurate între acestea.

Aplicația va reține o colecție de Personaje. Fiecare personaj are o denumire, o cantitate de viață de bază și o valoare de damage. Fiecare personaj deține o armă specifică cu un nivel asociat (1-5). Distingem următoarele tipuri:

    Mag, cu baghetă și abilitatea "Freeze" (blochează oponentul 2 runde).

    Erou, cu sabie și abilitatea "Parry" (anulează damage-ul primit).

    Goblin, cu suliță și abilitatea "Dezarmare" (golește mana oponentului).

Aplicația va reține și o colecție de Arene. Fiecare arenă are un nume, un nivel (1-5) și un nivel de avantaj (0-3). Arenele oferă beneficii clasei specifice (Mag, Erou sau Goblin) și aplică penalizări (sângerare, scădere de nivel armă, scădere de viață) oponenților.

Regulile luptei includ un sistem de Mană (regenerare, costuri variabile în funcție de nivelul armei) și un sistem de Avantaj de clasă (Mag > Erou > Goblin > Mag), care modifică damage-ul aplicat în timpul unei runde.

Cerințe

a) Să citească, să rețină în memorie și să afișeze colecțiile de Personaje și Arene. b) Să permită ștergerea (rezilierea) unui element din colecție prin identificator unic. c) Să gestioneze asocierea unei lupte între două personaje pe o arenă aleasă, cu opțiuni de simulare sau joc interactiv. d) Salvarea și încărcarea automată a datelor în/din fișiere text.
e) Implementarea unui "Tutorial" care explică mecanicile matematice ale jocului.