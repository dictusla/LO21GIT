#include <iostream>
#include <string>
#include "Automates.h"

short unsigned int NumBitToNum(const std::string& num) {
	if (num.size() != 8) throw AutomateException("Numero d'automate indefini");
	int puissance = 1;
	short unsigned int numero = 0;
	for (int i = 7; i >= 0; i--) {
		if (num[i] == '1') numero += puissance;
		else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
		puissance *= 2;
	}
	return numero;
}

std::string NumToNumBit(short unsigned int num) {
	std::string numeroBit;
	if (num > 256) throw AutomateException("Numero d'automate indefini");
	unsigned short int p = 128;
	int i = 7;
	while (i >= 0) {
		if (num >= p) {
			numeroBit.push_back('1');
			num -= p;
		}
		else { numeroBit.push_back('0'); }
		i--;
		p = p / 2;
	}
	return numeroBit;
}

Automate1D::Automate1D(unsigned short int num): numero(num),numeroBit(NumToNumBit(num)){
}

Automate1D::Automate1D(const std::string& num) : numero(NumBitToNum(num)),numeroBit(num) {
}

void Automate1D::appliquerTransition(const Etat& dep, Etat& dest) const
{
	const Etat1D& d=dynamic_cast<const Etat1D&>(dep);
   Etat1D& a=dynamic_cast<Etat1D&>(dest);
	if (d.getX() != a.getX())
      a = d;
	for (int i = 0; i < dep.getX(); i++) {
		short int conf=0;
		if (i > 0)
         conf+=d.getCellule(i - 1) * 4;
		conf+=d.getCellule(i)*2;
		if (i < dep.getX()-1)
         conf+=d.getCellule(i + 1);
		a.setCellule(i, numeroBit[7-conf]-'0');
	}
}

std::ostream& operator<<(std::ostream& f, const Automate1D& A) {
	f << A.getNumero() << " : " << A.getNumeroBit() << "\n";
	return f;
}

void Automate2D::appliquerTransition (const Etat& dep, Etat& dest) const
{
   const Etat2D& d=dynamic_cast<const Etat2D&>(dep);
   Etat2D& a=dynamic_cast<Etat2D&>(dest);

   if (dep.getX() != dest.getX() || d.getY()!= a.getY())
      a=d;

   for (int i = 0; i < dep.getX(); i++)
   {
      for(int j=0; j < d.getY(); j++)
      {
         unsigned int nbVvivant=0;
         for(int x=i-1; x<=i+1; ++x)
         {
            for(int y=j-1; y<=j+1; ++y)
            {
               if ((x!=i || y!=j) && d.getCellule(x,y) )
                  nbVvivant++;
            }
         }
         if (nbVvivant<minToNotDie || nbVvivant>maxToNotDie)
            {
               a.setCellule(i,j, false);}
         else
            {
               a.setCellule(i, j, true);}
      }
	}
}

void AutomateFdF::appliquerTransition (const Etat& dep, Etat& dest) const
{
   const EtatFdF& d=dynamic_cast<const EtatFdF&>(dep);
   EtatFdF& a=dynamic_cast<EtatFdF&>(dest);

   if (d.getX() != a.getX() || d.getY()!=a.getY())
      a=d;

   for (int i = 0; i < dep.getX(); i++)
   {
      for(int j=0; j < d.getY(); j++)
      {
         if (d.getCellule(i,j)==0)
            a.setCellule(i,j,0);
         else if (d.getCellule(i,j)==2)
            a.setCellule(i,j,3);
         else if (d.getCellule(i,j)==3)
            a.setCellule(i,j,3);
         else
         {
            if ( d.getCellule(i,j-1)==2 || d.getCellule(i,j+1)==2 || d.getCellule(i-1,j)==2 || d.getCellule(i+1,j)==2 )
               a.setCellule(i,j,2);
            else
               a.setCellule(i,j,1);
         }
      }
	}
}

AutomateManager::AutomateManager()
{
   for (unsigned int i=0; i<256; i++)
      automates[i]=nullptr;
}

AutomateManager::~AutomateManager()
{
   for (unsigned int i=0; i<256; i++)
      delete automates[i];
}

AutomateManager* AutomateManager::instance=nullptr;

AutomateManager& AutomateManager::getAutomateManager()
{
   if (!instance)
      instance =new AutomateManager;
   return *instance;
}

void AutomateManager::freeAutomateManager()
{
   delete instance;
   instance=nullptr;
}

const Automate1D& AutomateManager::getAutomate(unsigned short int num)
{
   if(!automates[num])
      automates[num]=new Automate1D(num);
   return *automates[num];
}

const Automate1D& AutomateManager::getAutomate(std::string& num)
{
   return getAutomate(NumBitToNum(num));
}

