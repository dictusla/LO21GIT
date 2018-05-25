#include <iostream>
#include "etats.h"



Etat1D::Etat1D(unsigned int dim ,unsigned int x): Etat(dim,x), valeur(nullptr)
{
   if(x>0)
      valeur= new unsigned int[x];
   for (unsigned int i =0; i<dimension; i++)
      valeur[i]=0;
}

int Etat1D::getCellule(unsigned int i)const
{
   if (i>=x) throw "Cellule inexistante";//AutomateException("Cellule inexistante");
   return valeur[i];
}

void Etat1D::setCellule(unsigned int i, int val)
{
   if (i>=x) throw "cellule inexistante";//AutomateException("Cellule inexistante");
   valeur[i]=val;
}

Etat2D::Etat2D(unsigned int dim ,unsigned int x, unsigned int y): Etat(dim,x), y(y),tab(nullptr)
{
   if(x>0)
      tab= new bool*[x];
   for (unsigned int i =0; i<y; i++)
      tab[i]=new bool ;
}

bool Etat2D::getCellule(unsigned int i, unsigned int j) const
{
   if (i>=x || j>=y) throw "Cellule inexistante";//AutomateException("Cellule inexistante");
   return tab[i][j];
}

void Etat2D::setCellule(unsigned int i, unsigned int j, bool val)
{
   if (i>=x || j>=y) throw "cellule inexistante";//AutomateException("Cellule inexistante");
   tab[i][j]=val;
}

