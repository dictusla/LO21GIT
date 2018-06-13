#include <iostream>
#include <string>

#include "etats.h"
#include "Automates.h"
#include "simulateur.h"


Simulateur::Simulateur(const Automate& a, unsigned int buffer):
    automate(a), etats(nullptr), depart(nullptr), nbMaxEtats(buffer),rang(0)
{
	etats = new Etat*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++)
      etats[i] = nullptr;
}
Simulateur::Simulateur(const Automate& a, const Etat& dep, unsigned int buffer):
    automate(a), etats(nullptr), depart(&dep), nbMaxEtats(buffer),rang(0)
{
	etats = new Etat*[nbMaxEtats];
	if (!etats)
      throw AutomateException("bad alloc of tab etats");

	for (unsigned int i = 0; i < nbMaxEtats; i++)
      etats[i] = nullptr;

	if (typeid(dep)==typeid(Etat1D))
      etats[0] = new Etat1D(dynamic_cast<const Etat1D&>(dep));
   else if (typeid(dep)==typeid(Etat2D))
      etats[0]= new Etat2D(dynamic_cast<const Etat2D&>(dep));
   else if (typeid(dep)==typeid(EtatFdF))
      etats[0]= new EtatFdF(dynamic_cast<const EtatFdF&>(dep));
   else throw AutomateException("etat de depart incorrect");
}

void Simulateur::build(unsigned int cellule)
{
	if (cellule >= nbMaxEtats)
      throw AutomateException("erreur taille buffer");

	if (etats[cellule] == nullptr)
   {
      if (typeid(*depart)==typeid(Etat1D))
         etats[cellule] = new Etat1D(1,depart->getX());
      else if (typeid(*depart)==typeid(Etat2D))
         etats[cellule] = new Etat2D(2,depart->getX(),dynamic_cast<const Etat2D*>(depart) ->getY());
      else if (typeid(*depart)==typeid(EtatFdF))
         etats[cellule] = new EtatFdF(2,depart->getX(),dynamic_cast<const EtatFdF*>(depart) ->getY());
      else
         throw AutomateException("etat de depart incorrect");
   }
}

void Simulateur::setEtatDepart(const Etat& e) {
	depart = &e;
	reset();
}

void Simulateur::reset() {
	if (depart==nullptr) throw AutomateException("etat depart indefini");
	build(0);
	 if (typeid(*depart)==typeid(Etat1D))
      dynamic_cast<Etat1D&>(*etats[0]) = dynamic_cast<const Etat1D&>(*depart) ;
   else if (typeid(*depart)==typeid(Etat2D))
      dynamic_cast<Etat2D&>(*etats[0]) = dynamic_cast<const Etat2D&>(*depart) ;
   else if (typeid(*depart)==typeid(EtatFdF))
      dynamic_cast<EtatFdF&>(*etats[0]) = dynamic_cast<const EtatFdF&>(*depart) ;
   else
      throw AutomateException("etat de depart incorrect");

	rang = 0;
}

void Simulateur::next() {
	if (depart == nullptr)
      throw AutomateException("etat depart indefini");
   rang++;
	build(rang%nbMaxEtats);

	if (typeid(*etats[(rang-1) % nbMaxEtats])==typeid(Etat1D))
      automate.appliquerTransition(dynamic_cast<const Etat1D&>(*etats[(rang - 1) % nbMaxEtats]), *etats[rang%nbMaxEtats]);
   else if (typeid(*etats[(rang-1) % nbMaxEtats])==typeid(Etat2D))
      automate.appliquerTransition(dynamic_cast<const Etat2D&>(*etats[(rang - 1) % nbMaxEtats]), *etats[rang%nbMaxEtats]);
   else if (typeid(*etats[(rang-1) % nbMaxEtats])==typeid(EtatFdF))
      automate.appliquerTransition(dynamic_cast<const EtatFdF&>(*etats[(rang - 1) % nbMaxEtats]), *etats[rang%nbMaxEtats]);
   else
      throw AutomateException("etats non valides");
   //etats[rang%nbMaxEtats]->afficherEtat();
}

void Simulateur::run(unsigned int nb_steps) {
	for (unsigned int i = 0; i < nb_steps; i++)
      next();
}

const Etat& Simulateur::dernier() const {
	return *etats[rang%nbMaxEtats];
}

Simulateur::~Simulateur() {
	for (unsigned int i = 0; i < nbMaxEtats; i++)
      delete etats[i];
	delete[] etats;
}
