Pentru functionarea corecta a programului se recomanda folosirea emularii terminalului din windows pentru in IDE , sau rularea acestuia din terminal.

Enunt

O companie de dezvoltare software are nevoie de implementarea unei aplicații C++ orientate pe obiecte pentru gestionarea unui sistem complex de combat tip RPG (Role-Playing Game). Aplicația trebuie să gestioneze entități de tip „Personaj” și „Arenă”, precum și logica unei lupte desfășurate între acestea.

Aplicația va reține o colecție de Personaje. Fiecare personaj are o denumire, o cantitate de viață de bază și o valoare de damage. Fiecare personaj deține o armă specifică cu un nivel asociat (1-5). Distingem următoarele tipuri:

    Mag, cu baghetă și abilitatea "Freeze" (blochează oponentul 2 runde).

    Erou, cu sabie și abilitatea "Parry" (anulează damage-ul primit).

    Goblin, cu suliță și abilitatea "Dezarmare" (golește mana oponentului).

Aplicația va reține și o colecție de Arene. Fiecare arenă are un nume, un nivel (1-5) și un nivel de avantaj (0-3). Arenele oferă beneficii clasei specifice (Mag, Erou sau Goblin) și aplică penalizări (sângerare, scădere de nivel armă, scădere de viață) oponenților.

Regulile luptei includ un sistem de Mană (regenerare, costuri variabile în funcție de nivelul armei) și un sistem de Avantaj de clasă (Mag > Erou > Goblin > Mag), care modifică damage-ul aplicat în timpul unei runde.

Cerințe

a) Să citească, să rețină în memorie și să afișeze colecțiile de Personaje și Arene.

b) Să permită ștergerea unui element din colecție prin identificator unic.

c) Să gestioneze asocierea unei lupte între două personaje pe o arenă aleasă, cu opțiuni de simulare sau joc interactiv.

d) Salvarea și încărcarea automată a datelor în/din fișiere text.

e) Implementarea unui "Tutorial" care explică mecanicile matematice ale jocului.

Review:

Descrierea Proiectului si Motivatia

Proiectul realizat reprezinta rezultatul aprofundarii principiilor Programarii Orientate pe Obiect in limbajul C++. Tema aleasa, dezvoltarea unui sistem de combat tip RPG turn-based, a fost selectata pentru complexitatea interactiunilor dintre obiecte si pentru posibilitatea de a aplica mai multe design patterns intr-un context logic si practic.

Scopul principal a fost crearea unui sistem extensibil si stabil, care sa depaseasca limitele unui simplu script procedural. RPG-ul creat permite utilizatorilor sa creeze entitati distincte, sa le salveze intr-un sistem de istoric bazat pe fisiere text, sa le implice in confruntari tactice unde deciziile de moment influenteaza rezultatul final, sau sa simuleze o anumita confruntare fara a necesita implicare de la tastatura din partea jucatorului.
Evolutia fata de versiunile anterioare

De la functii la clase: Fata de versiunile initiale, am trecut de la o structura care nu era scalabila si neinteractiva la una usor de marit si care implica in totalitate utilizatorul. In proiectul anterior, logica era impartita pe bucati, fiind dificil de testat sau de extins fara a introduce erori grave.

Gestionarea datelor: In acest stadiu final, am refactorizat complet modul in care datele sunt stocate si accesate in memorie. Am inlocuit vectorii simpli de date din functia main cu o clasa de tip sablon denumita Storage.

Sistemul de istoric: De asemenea, am adaugat mecanisme de persistenta care lipseau cu desavarsire inainte: sistemul de salvare si incarcare din fisiere text, implementat in header-ul de salvare, asigura acum ca progresul personajelor si configurarea arenelor raman intacte intre sesiunile de joc.

Arhitectura si Design Patterns

Succesul acestui proiect se bazeaza pe utilizarea a trei design patterns fundamentale, care asigura stabilitatea intregii aplicatii:

    Singleton Pattern: Acest pattern este utilizat de clasa Storage pentru a garanta accesul controlat la colectiile de obiecte, eliminand nevoia de a trece pointeri prin toata aplicatia. Singleton-ul este important intr-o aplicatie de tip joc pentru a evita crearea de mai multe ori a unor resurse unice, cum ar fi meniul principal sau managerul de stocare, prevenind astfel starea neuniforma a datelor in memorie.

    Command Pattern: Aceasta este baza meniului interactiv al jocului. Fiecare optiune principala (cum ar fi Creare Personaj, Aranjare Lupta, Stergere Arena) este o clasa separata ce mosteneste interfata Comanda. Am separat logica fiecarei actiuni, ceea ce a permis adaugarea usoara a unor noi functionalitati fara a modifica structura de baza a clasei Meniu. Singura exceptie este optiunea de Tutorial, unde am ales sa simplific lucrurile prin adaugarea afisarii textului direct in functia principala de rulare a meniului. Aceasta arhitectura respecta principiul Open/Closed din SOLID.

    Factory Pattern: Pentru a face codul si mai curat si la recomandarea primita, am integrat modelul Factory pentru procesul de instantiere. Am creat clasele PersonajFactory si ArenaFactory. Acestea primesc un numar (tipul clasei) si datele citite de la tastatura, returnand obiectul corect. Astfel, meniul principal nu mai este incarcat cu responsabilitatea de a decide ce fel de obiect trebuie construit cu operatorul new, ci deleaga aceasta sarcina fabricii.

Implementarea Conceptelor Avansate

Pe langa design patterns, codul sursa contine mai multe tehnici avansate de programare:

    Template-uri (Sabloane): Am integrat tehnici avansate precum Templates pentru a reduce duplicarea codului. Clasa Storage permite gestionarea generica a oricarui tip de entitate, fie un obiect de tip Personaj, fie de tip Arena. Functia sablon printeaza_lista elimina nevoia de a scrie bucle de afisare repetitive in fiecare clasa in parte.

    Interfata Non-Virtuala (NVI): O componenta importanta este utilizarea tehnicii NVI. In ierarhiile de clase pentru Personaj si Arena, am facut functii publice pentru afisare care, la randul lor, apeleaza metode protejate de tip implementare. Aceasta tehnica ofera un control foarte bun asupra modului in care afisarea este executata in mod general, permitand verificari sigure inainte ca implementarea specifica a derivatei sa fie apelata.

    Polimorfism si Dynamic Cast: Am utilizat functia dynamic_cast in modulul de lupte pentru a verifica efectiv tipul arenei la momentul rularii. Acest lucru demonstreaza polimorfismul dinamic, deoarece imi permite sa aplic castiguri sau pierderi procentuale de damage in functie de arena pe care pica jucatorii.

Sistemul de Lupta si Mecanicile de Joc

Sistemul de lupta reprezinta cea mai complexa componenta a proiectului, depasind cu mult operatiile aritmetice simple de scadere a vietii:

    State Machine: Gestionarea mecanicii de inghetare (Freeze), de blocare (Parry) sau dezarmare (Disarm) se face printr-o structura numita gestionare_lupta. Aceasta retine tura curenta, cantitatea de mana si un istoric al actiunilor anterioare, fiind o abordare de tip state machine, foarte importanta pentru un joc turn-based.

    Mana si Progresie: Cantitatea de mana necesara abilitatilor este calculata dinamic in functie de nivelul armei. Nivelul armei creste cu un punct la o lupta castigata si scade cu un punct la o lupta pierduta, generand o bucla de progres care il face pe jucator sa fie atent la decizii.

    Abstractizarea claselor: In procesul de dezvoltare am descoperit ca utilizarea claselor abstracte pentru a defini comportamentele comune ale personajelor a fost o decizie foarte buna. Aceasta a permis tratarea uniforma a unor obiecte total diferite, cum ar fi Mag, Erou si Goblin, direct in vectorul de stocare.

    Influentarea arenelor: Provocarea de a gestiona starea arenelor, care pot aplica penalizari sub forma de sangerare la fiecare tura in arena Eroului sau pot scadea din start nivelul armei oponentului in arena Goblinului, a demonstrat o utilizare utila a interacțiunilor dintre obiecte.

Dificultati Intampinate si Modul de Rezolvare

Implementarea proiectului nu a fost lipsita de provocari tehnice reale:

    Probleme cu controlul versiunilor (Git): O alta situatie a aparut atunci cand am adaugat din greseala fisiere text temporare (pe care le foloseam pentru a tine minte idei) in repository-ul central. Fisierul ramanea vizibil pe site chiar si dupa ce modificam codul. A trebuit sa invat comenzi de terminal specifice pentru a scoate acel document din sistemul de tracking al memoriei sistemului Git fara a-l sterge efectiv de pe unitatea mea de stocare, pastrand astfel istoricul proiectului curat si profesionist.

    Gestiunea memoriei dinamice: Initial, am avut pierderi de memorie constante din cauza alocarii dinamice cu new in cadrul buclei principale de joc. Am corectat complet acest aspect prin utilizarea metodelor de curatare in destructori. Destructorul clasei Storage parcurge acum lista de elemente si apeleaza operatiunea de delete pentru fiecare pointer in parte la inchiderea programului.

    Validarea input-ului defensiv: O alta provocare a fost citirea datelor. Am invatat ca simpla citire de la tastatura poate deveni instabila daca utilizatorul introduce litere sau caractere invalide in loc de cifre. Pentru meniuri, am rezolvat situatia implementand citirea unui singur caracter folosind functii speciale care preiau o singura tasta de pe tastatura, evitand blocarea programului in asteptarea valorii si curatand situatiile neprevazute. Pentru blocaje tehnice la creare, am adaugat clase de exceptii personalizate si blocuri try-catch care prind mesajele de eroare generate de Factory si le afiseaza curat. Aceasta experienta mi-a demonstrat pe deplin importanta conceptului de programare defensiva.
Concluzii Finale

Consider ca am parcurs toti pasii practici si teoretici necesari pentru a livra o aplicatie stabila, care nu doar ca raspunde tuturor cerintelor complexe ale laboratorului, dar este si o baza de invatare foarte buna pentru dezvoltari ulterioare, cum ar fi adaugarea unei interfete grafice in viitor. In plus, am descoperit in sfarsit beneficiile documentarii constante a codului, o practica de baza pe care am inceput sa o integrez foarte natural in procesul meu zilnic de scriere. Fiecare functie a fost gandita pentru a avea un rol unic in toata masinaria programului, ceea ce a transformat cautarea erorilor intr-un proces mai putin frustrant si mult mai usor de urmarit logic.












Biblliografie: Stackoverflow + Youtube:
https://www.youtube.com/watch?v=wN0x9eZLix4
https://www.youtube.com/watch?v=PPup1yeU45I
https://www.youtube.com/watch?v=usmdZniV_Yw
https://stackoverflow.com/questions/17434/when-should-you-use-friend-in-c
https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std
https://stackoverflow.com/questions/5590381/how-can-i-convert-int-to-string-in-c
https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors