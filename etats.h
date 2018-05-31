#ifndef ETATS_H_INCLUDED
#define ETATS_H_INCLUDED

class Etat
{
protected:
   unsigned int dimension ; // 1D ou 2D --> bool?
   unsigned int x ; // nb cellules horizontales (pour 1D et 2D)

public:
   Etat(unsigned int dim ,unsigned int x).
   unsigned int getDimension() const {return dimension;}
   unsigned int getX() const {return x;}
   virtual void afficherEtat() const =0;

};

class Etat1D : public Etat
{
   unsigned int* valeur; // a voir avec string pour les couleurs

public:
   Etat1D(unsigned int dim ,unsigned int x);
   int getCellule(unsigned int i)const;
   void setCellule(unsigned int i, int val);
   void afficherEtat() const;
   ~Etat1D();
   Etat1D(const Etat1D& e);
   Etat1D& operator=(const Etat1D& e); //est ce qu'on a besoin d'un constructeur de recopie et une surcharge de operateur = ? Ou bien on les mets en privé et on ne les defini pas

};

class Etat2D : public Etat
{
   unsigned int y; //nb cellules vertical
   bool** tab;

public:
   Etat2D(unsigned int dim ,unsigned int x, unsigned int y);
   unsigned int getY() const {return y;}
   bool getCellule(unsigned int i, unsigned int j) const;
   void setCellule(unsigned int i, unsigned int j, bool val);
   void afficherEtat() const;
   ~Etat2D();
   Etat2D(const Etat2D& e);
   Etat2D& operator=(const Etat2D& e); //besoin ou pas?

};
#endif // ETATS_H_INCLUDED
