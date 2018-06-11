#ifndef ETATS_H_INCLUDED
#define ETATS_H_INCLUDED

class Etat
{
protected:
   unsigned int dimension ; // 1D ou 2D --> bool?
   int x ; // nb cellules horizontales (pour 1D et 2D)

public:
   Etat(unsigned int dim ,int x);
   unsigned int getDimension() const {return dimension;}
   int getX() const { return x; }
   virtual void afficherEtat() const =0;
   virtual ~Etat(){};
};

class Etat1D : public Etat
{
   bool* valeur; // a voir avec string pour les couleurs

public:
   Etat1D(unsigned int dim ,int x);
   bool getCellule( int i)const;
   void setCellule( int i, bool val);
   void afficherEtat() const;
   ~Etat1D();
   Etat1D(const Etat1D& e);
   Etat1D& operator=(const Etat1D& e);
};

class Etat2D : public Etat
{
   int y; //nb cellules vertical
   bool** tab;

public:
   Etat2D(unsigned int dim ,int x, int y);
   int getY() const {return y;}
   bool getCellule(int i, int j) const;
   void setCellule(int i, int j, bool val);
   void afficherEtat() const;
   ~Etat2D();
   Etat2D(const Etat2D& e);
   Etat2D& operator=(const Etat2D& e);
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
