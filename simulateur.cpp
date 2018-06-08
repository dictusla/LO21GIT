#include <iostream>
#include <string>
#include "etats.h"
#include "Automates.h"
#include "simulateur.h"


Simulateur::Simulateur(const Automate1D& a, unsigned int buffer):
    automate(a), etats(nullptr), depart(nullptr), nbMaxEtats(buffer),rang(0) {
	etats = new Etat*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++) etats[i] = nullptr;
}
Simulateur::Simulateur(const Automate1D& a, const Etat1D& dep, unsigned int buffer):
    automate(a), etats(nullptr), depart(&dep), nbMaxEtats(buffer),rang(0) {
	etats = new Etat*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++) etats[i] = nullptr;
	etats[0] = new Etat1D(dep);
}

void Simulateur::build(unsigned int cellule) {
	if (cellule >= nbMaxEtats) throw AutomateException("erreur taille buffer");
	if (etats[cellule] == nullptr) etats[cellule] = new Etat1D(1,depart->getX());
}

void Simulateur::setEtatDepart(const Etat& e) {
	depart = &e;
	reset();
}

void Simulateur::reset() {
	if (depart==nullptr) throw AutomateException("etat depart indefini");
	build(0); *etats[0] = *depart;
	rang = 0;
}

void Simulateur::next() {
	if (depart == nullptr) throw AutomateException("etat depart indefini");
   rang++;
	build(rang%nbMaxEtats);
	automate.appliquerTransition(dynamic_cast<const Etat1D&>(*etats[(rang - 1) % nbMaxEtats]), *etats[rang%nbMaxEtats]);
}

void Simulateur::run(unsigned int nb_steps) {
	for (unsigned int i = 0; i < nb_steps; i++) next();
}

const Etat& Simulateur::dernier() const {
	return *etats[rang%nbMaxEtats];
}

Simulateur::~Simulateur() {
	for (unsigned int i = 0; i < nbMaxEtats; i++) delete etats[i];
	delete[] etats;
}
