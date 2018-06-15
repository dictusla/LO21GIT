#ifndef ETATS_H_INCLUDED
#define ETATS_H_INCLUDED

//#include "Automates.h"
#include <iostream>
#include <string>

class EtatException {
private:
      std::string info;
public:
      EtatException(const std::string& message):info(message) {}
      std::string getInfo() const { return info; }
};

class Etat {
protected:
   unsigned int dimension ; // 1D ou 2D --> bool?
   unsigned int x ; // nb cellules horizontales (pour 1D et 2D)

public:
   Etat(unsigned int dim, unsigned int x);
   unsigned int getDimension() const {return dimension;}
   unsigned int getX() const { return x; }
   virtual void afficherEtat() const =0;
   virtual ~Etat(){}
};

class Etat1D : public Etat
{
   unsigned int* valeur; // a voir avec string pour les couleurs
public:
   Etat1D(unsigned int dim , unsigned int x);
   ~Etat1D();
   Etat1D(const Etat1D& e);
   Etat1D& operator=(const Etat1D& e);
   void copyEtat(const Etat1D* e);
   unsigned int getCellule(unsigned int i)const;
   void setCellule(unsigned int i, unsigned int val);
   void afficherEtat() const;
};

class Etat2D : public Etat {
   unsigned int y; //nb cellules vertical
   unsigned int** tab;
public:
   Etat2D(unsigned int dim , unsigned int x, unsigned int y);
   ~Etat2D();
   Etat2D(const Etat2D& e);
   Etat2D& operator=(const Etat2D& e);
   void copyEtat(const Etat2D* e);
   unsigned int getY() const {return y;}
   unsigned int getCellule(unsigned int i, unsigned int j) const;
   void setCellule(unsigned int i, unsigned int j, unsigned int val);
   void afficherEtat() const;
};

class EtatFdF : public Etat
{
   int y;//nb cellules vertical
   int** tab; // 0:vide , 1:foret , 2:feu , 3:cendre

public:
   EtatFdF(unsigned int dim ,int x, int y);
   int getY() const {return y;}
   int getCellule(int i, int j) const;
   void setCellule(int i, int j, int val);
   void afficherEtat() const;
   ~EtatFdF();
   EtatFdF(const EtatFdF& e);
   EtatFdF& operator=(const EtatFdF& e);
};

#endif // ETATS_H_INCLUDED
