#ifndef ETATS_H_INCLUDED
#define ETATS_H_INCLUDED

class Etat
{
protected:
   unsigned int dimension ; // 1D ou 2D --> bool?
   unsigned int x ; // nb cellules horizontales (pour 1D et 2D)

public:
   Etat(unsigned int dim ,unsigned int x): dimension(dim),x(x){}
   unsigned int getDimension() const {return dimension;}
   unsigned int getX() const {return x;}


};

class Etat1D : public Etat
{
   unsigned int* valeur; // a voir avec string pour les couleurs

public:
   Etat1D(unsigned int dim ,unsigned int x);
   int getCellule(unsigned int i)const;
   void setCellule(unsigned int i, int val);
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

};
#endif // ETATS_H_INCLUDED
