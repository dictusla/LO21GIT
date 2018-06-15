#include <iostream>
#include <string>
#include "etats.h"

Etat::Etat(unsigned int dim ,unsigned int x): dimension(dim),x(x)
{
   if (/*dim<=0 || dim>=3 ||*/ x<=0)
      throw EtatException("Dimension de l'etat non valide");
}

Etat1D::Etat1D(unsigned int dim ,unsigned int x): Etat(dim,x)
{
   valeur= new unsigned int[x];
   for (unsigned int i =0; i<x; i++)
      valeur[i]=false;
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

Etat1D& Etat1D::operator=(const Etat1D& e) {
    if (this != &e){
        dimension=e.getDimension();
        if(getX()!=e.getX())
        {
           delete[] valeur;
           x=e.getX();
           valeur=new unsigned int[getX()];
        }
        for(unsigned int i=0; i<getX(); ++i)
           valeur[i]=e.valeur[i];
    }
    return *this;
}

void Etat1D::copyEtat(const Etat1D* e){
    unsigned int fin;
    if (getX() <= e->getX()) fin = getX();
    else fin = e->getX();
    for (unsigned int i = 0; i < getX(); i++){
        if (i < fin) setCellule(i,e->getCellule(i));
        else setCellule(i,0);
    }
}

unsigned int Etat1D::getCellule(unsigned int i)const {
   if (i>=getX())
       throw EtatException("Cellule inexistante Etat1D");
    return valeur[i];
}

void Etat1D::setCellule(unsigned int i, unsigned int val) {
   if (i>=getX())
       throw EtatException("Cellule inexistante1D");
   valeur[i]=val;
}
/*
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
*/

void Etat1D::afficherEtat() const {
   std::cout<<"Etat1D :"<<std::endl;
   for(unsigned int i=0; i<getX(); ++i)
      std::cout<<valeur[i];
   std::cout<<std::endl;
}

Etat2D::Etat2D(unsigned int dim ,unsigned int x, unsigned int y): Etat(dim,x), y(y)
{
   if(y<=0)
      throw EtatException("Dimensions de l'etat non valide");
   tab= new unsigned int*[x];
   for (unsigned int i =0; i<x; i++)
   {
      tab[i]=new unsigned int[y] ;
      for (unsigned int j=0; j<y; ++j)
         tab[i][j]=0;
   }
}

unsigned int Etat2D::getCellule(unsigned int i,unsigned int j) const
{
   //std::cout<<"get cellule avec i="<<i<<" et j="<<j<<std::endl;
   if (i>=getX() || j>=y)
       throw EtatException("Cellule inexistante");
   return tab[i][j];
}

void Etat2D::setCellule(unsigned int i,unsigned int j, unsigned int val)
{
   if (i>=getX() || j>=y)
       throw EtatException("Cellule inexistante set ");
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
          std::cout<<getCellule(i,j);
      }
      std::cout<<std::endl;
   }
}


Etat2D::Etat2D(const Etat2D& e) : Etat(e.getDimension(),e.getX())
{
   y=e.y;
   tab= new unsigned int*[getX()];
   for (unsigned int i =0; i<getX(); i++)
   {
      tab[i]=new unsigned int[y] ;
      for(unsigned int j=0; i<y; ++j)
         tab[i][j]=e.tab[i][j];
   }
}

Etat2D& Etat2D::operator=(const Etat2D& e)
{
   if(getX()!=e.getX()) {
      for(unsigned int i=0; i<getX(); ++i)
         delete tab[i];
      delete[]tab;
      x=e.getX();
      tab= new unsigned int*[getX()];
      y=e.y;
      for(unsigned int i=0; i<getX(); ++i)
         tab[i]=new unsigned int[y];
   }
   else if (y!=e.y) {
      y=e.y;
      for(unsigned int i=0; i<getX(); ++i) {
         delete tab[i];
         tab[i]= new unsigned int[y];
      }
   }
   for (unsigned int i =0; i<getX(); i++) {
      for(unsigned int j=0; j<y; j++)
         tab[i][j]=e.getCellule(i,j);
   }
   return *this;
}

void Etat2D::copyEtat(const Etat2D* e){
    unsigned int col;
    unsigned int ligne;
    if (getX() <= e->getX()) col = getX();
    else col = e->getX();
    if (y <= e->y) ligne = y;
    else ligne = e->y;
    for (unsigned int i = 0; i < getX(); i++){
        for (unsigned int j = 0; j < y; j++){
            if (i < col && j < ligne) tab[i][j] = e->getCellule(i,j);
            else tab[i][j] = 0;
        }
    }
}

EtatFdF::EtatFdF(unsigned int dim ,int x, int y): Etat(dim,x), y(y)
{
   if(y<=0)
      throw EtatException("Dimensions de l'etat non valide");
   tab= new int*[x];
   for (int i=0; i<x; i++)
   {
      tab[i]=new int[y] ;
      for (int j=0; j<y; ++j)
         tab[i][j]=0;
   }
}

int EtatFdF::getCellule(int i, int j) const
{
   if (i<-1 || j<-1 || i>getX() || j>y) throw EtatException("Cellule inexistante get");
   if(i==-1 || j==-1 || i==getX() || j==y)
      return 0;
   return tab[i][j];
}

void EtatFdF::setCellule(int i, int j, int val)
{
   if (i<0 || j<0 ||i>=getX() || j>=y) throw EtatException("Cellule inexistante set ");
   tab[i][j]=val;
}

EtatFdF::~EtatFdF()
{
   for(unsigned int i=0; i<getX(); ++i)
      delete[] tab[i];
   delete[] tab;
}

void EtatFdF::afficherEtat() const
{
   std::cout<<"EtatFdF :"<<std::endl;
   for(int i=0; i<getX(); ++i)
   {
      for(int j=0; j<y ;++j)
      {
         if(getCellule(i,j)==0)
            std::cout<<" ";
         else if(getCellule(i,j)==1)
            std::cout<<"T";
         else if(getCellule(i,j)==2)
            std::cout<<"F";
         else
            std::cout<<".";
      }

      std::cout<<std::endl;
   }
}


EtatFdF::EtatFdF(const EtatFdF& e) : Etat(e.getDimension(),e.getX())
{
   y=e.y;
   tab= new int*[e.getX()];
   for (unsigned int i =0; i<e.getX(); i++)
   {
      tab[i]=new int[y] ;
      for(unsigned int j=0; j<y; ++j) // ND ???
         tab[i][j]=e.tab[i][j];
   }
}

EtatFdF& EtatFdF::operator=(const EtatFdF& e)
{
   //std::cout<<"entree op ="<<std::endl;
   if(getX()!=e.getX())
   {
      for(unsigned int i=0; i<getX(); ++i)
         delete tab[i];
      delete[]tab;
      x=e.getX();
      tab= new int*[getX()];
      y=e.y;
      for(unsigned int i=0; i<getX(); ++i)
         tab[i]=new int[y];
   }
   else if (y!=e.y)
   {
      y=e.y;
      for(unsigned int i=0; i<getX(); ++i)
      {
         delete tab[i];
         tab[i]= new int[y];
      }
   }

   for (int i =0; i<getX(); i++)
   {
      for(int j=0; j<y; j++)
         tab[i][j]=e.getCellule(i,j);
   }

   return *this;
}
