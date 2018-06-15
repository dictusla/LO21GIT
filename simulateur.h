#ifndef SIMULATEUR_H_INCLUDED
#define SIMULATEUR_H_INCLUDED

#include <typeinfo>
#include "etats.h"
#include "Automates.h"

#include "automates.h"

class Simulateur {
    const Automate& automate;
    Etat** etats;
    const Etat* depart;
     unsigned int nbMaxEtats;
    unsigned int rang;
     void build(unsigned int c);
    Simulateur(const Simulateur& s);
    Simulateur& operator=(const Simulateur& s);

public:
    Simulateur(const Automate& a, unsigned int buffer = 2);
    Simulateur(const Automate& a, const Etat& dep, unsigned int buffer = 2);
    void setEtatDepart(const Etat& e);
    void run(unsigned int nbSteps); // g�n�re les n prochains �tats
    void next(); // g�n�re le prochain �tat
    const Etat& dernier() const;
    unsigned int getRangDernier() const { return rang; }
    void reset(); // revenir � l'�tat de d�part
    ~Simulateur();
};

#endif // SIMULATEUR_H_INCLUDED
