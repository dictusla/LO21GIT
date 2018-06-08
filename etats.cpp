#include <iostream>
#include <string>
#include "etats.h"
#include "Automates.h"

Etat::Etat(unsigned int dim ,int x): dimension(dim),x(x)
{
   if (dim<=0 || dim>=3 || x<=0)
      throw AutomateException("Dimension de l'etat non valide");
}

Etat1D::Etat1D(unsigned int dim ,int x): Etat(dim,x)
{
   valeur= new bool[x];
   for (unsigned int i =0; i<x; i++)
      valeur[i]=false;
}

Etat1D::~Etat1D()
{
   delete[] valeur;
}

Etat1D::Etat1D(const Etat1D& e): Etat(e.getDimension(),e.getX())
{
   valeur= new bool[getX()];
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
      valeur=new bool[getX()];
   }
   for(int i=0; i<getX(); ++i)
      valeur[i]=e.valeur[i];
   return *this;
}
bool Etat1D::getCellule(int i)const
{
   if (i>=getX()) throw AutomateException("Cellule inexistante Etat1D");
   return valeur[i];
}

void Etat1D::setCellule(int i, bool val)
{
   if (i>=getX()) throw AutomateException("Cellule inexistante1D");
   valeur[i]=val;
}

void Etat1D::afficherEtat() const
{
   std::cout<<"Etat1D :"<<std::endl;
   for(int i=0; i<getX(); ++i)
      std::cout<<valeur[i];
   std::cout<<std::endl;
}

Etat2D::Etat2D(unsigned int dim ,int x, int y): Etat(dim,x), y(y)
{
   if(y<=0)
      throw AutomateException("Dimensions de l'etat non valide");
   tab= new bool*[x];
   for (int i =0; i<x; i++)
   {
      tab[i]=new bool[y] ;
      for (int j=0; j<y; ++j)
         tab[i][j]=false;
   }
}

bool Etat2D::getCellule(int i, int j) const
{
   //std::cout<<"get cellule avec i="<<i<<" et j="<<j<<std::endl;
   if (i<-1 || j<-1 || i>getX() || j>y) throw AutomateException("Cellule inexistante");
   if(i==-1 || j==-1 || i==getX() || j==y)
      {std::cout<<"false\n";
      return false;}
   return tab[i][j];
}

void Etat2D::setCellule(int i, int j, bool val)
{
   if (i<0 || j<0 ||i>=getX() || j>=y) throw AutomateException("Cellule inexistante set ");
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
   for(int i=0; i<getX(); ++i)
   {
      for(int j=0; j<y ;++j)
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

   for (int i =0; i<getX(); i++)
   {
      for(int j=0; j<y; j++)
         tab[i][j]=e.getCellule(i,j);
   }

   return *this;
}
