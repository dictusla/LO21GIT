#include <iostream>
#include <string>
#include "etats.h"
#include "Automates.h"

Etat::Etat(unsigned int dim ,unsigned int x): dimension(dim),x(x)
{
   if (dim<=0 || dim>=3 || x<=0)
      throw AutomateException("Dimension de l'etat non valide");
}

Etat1D::Etat1D(unsigned int dim ,unsigned int x): Etat(dim,x), valeur(nullptr)
{
   valeur= new unsigned int[x];
   for (unsigned int i =0; i<x; i++)
      valeur[i]=0;
}

Etat1D::~Etat1D()
{
   delete[] valeur;
}

Etat1D::Etat1D(const Etat1D& e): Etat(e.getDimension(),e.getX())
{
   valeur= new unsigned int[getX()];
   for(unsigned int i=0; i<getX(); ++i)
      valeur[i]=e.valeur[i];
}

Etat1D& Etat1D::operator=(const Etat1D& e)
{
   dimension=e.getDimension();
   if(getX()!=e.getX())
   {
      delete[] valeur;
      x=e.getX();
      valeur=new unsigned int[getX()];
   }
   for(unsigned int i=0; i<getX(); ++i)
      valeur[i]=e.valeur[i];
   return *this;
}

int Etat1D::getCellule(unsigned int i)const
{
   if (i>=getX()) throw AutomateException("Cellule inexistante");
   return valeur[i];
}

void Etat1D::setCellule(unsigned int i, int val)
{
   if (i>=getX()) throw AutomateException("Cellule inexistante");
   valeur[i]=val;
}

void Etat1D::afficherEtat() const
{
   std::cout<<"Etat1D :"<<std::endl;
   for(unsigned int i=0; i<getX(); ++i)
      std::cout<<valeur[i];
   std::cout<<std::endl;
}

Etat2D::Etat2D(unsigned int dim ,unsigned int x, unsigned int y): Etat(dim,x), y(y),tab(nullptr)
{
   if(y<=0)
      throw AutomateException("Dimensions de l'etat non valide");
   tab= new bool*[x];
   for (unsigned int i =0; i<x; i++)
   {
      tab[i]=new bool[y] ;
      for (unsigned int j=0; j<y; ++j)
         tab[i][j]=true;
   }
}

bool Etat2D::getCellule(unsigned int i, unsigned int j) const
{
   if (i>=getX() || j>=y) throw AutomateException("Cellule inexistante");
   return tab[i][j];
}

void Etat2D::setCellule(unsigned int i, unsigned int j, bool val)
{
   if (i>=getX() || j>=y) throw AutomateException("Cellule inexistante");
   tab[i][j]=val;
}


Etat2D::~Etat2D()
{
   for(unsigned int i=0; i<getX(); ++i)
      delete[] tab[i];
   delete[] tab;
}

void Etat2D::afficherEtat() const
{
   std::cout<<"Etat2D :"<<std::endl;
   for(unsigned int i=0; i<getX(); ++i)
   {
      for(unsigned int j=0; j<y ;++j)
      {
         if(getCellule(i,j))
            std::cout<<"X";
         else
            std::cout<<"0";
      }

      std::cout<<std::endl;
   }
}


Etat2D::Etat2D(const Etat2D& e) : Etat(e.getDimension(),e.getX())
{
   y=e.y;
   tab= new bool*[getX()];
   for (unsigned int i =0; i<getX(); i++)
   {
      tab[i]=new bool[y] ;
      for(unsigned int j=0; i<y; ++j)
         tab[i][j]=e.tab[i][j];
   }
}

Etat2D& Etat2D::operator=(const Etat2D& e)
{
   if(getX()!=e.getX())
   {
      for(unsigned int i=0; i<getX(); ++i)
         delete tab[i];
      delete[]tab;
      x=e.getX();
      tab= new bool*[getX()];
      y=e.y;
      for(unsigned int i=0; i<getX(); ++i)
         tab[i]=new bool[y];
   }
   else if (y!=e.y)
   {
      y=e.y;
      for(unsigned int i=0; i<getX(); ++i)
      {
         delete tab[i];
         tab[i]= new bool[y];
      }
   }

   for (unsigned int i =0; i<getX(); i++)
   {
      for(unsigned int j=0; i<y; ++j)
         tab[i][j]=e.tab[i][j];
   }

   return *this;
}

