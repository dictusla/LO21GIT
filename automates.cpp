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

void Automate1D::appliquerTransition(const Etat& dep, Etat& dest) const {
	if (dep.getX() != dest.getX()) dest = dep;
	for (int i = 0; i < dep.getX(); i++) {
		short int conf=0;
		if (i > 0) conf+=dynamic_cast<const Etat1D&>(dep).getCellule(i - 1) * 4;
		conf+=dynamic_cast<const Etat1D&>(dep).getCellule(i)*2;
		if (i < dep.getX()-1) conf+=dynamic_cast<const Etat1D&>(dep).getCellule(i + 1);
		dynamic_cast<Etat1D&>(dest).setCellule(i, numeroBit[7-conf]-'0');
	}
}

std::ostream& operator<<(std::ostream& f, const Automate1D& A) {
	f << A.getNumero() << " : " << A.getNumeroBit() << "\n";
	return f;
}

void Automate2D::appliquerTransition (const Etat& dep, Etat& dest) const
{
   if (dep.getX() != dest.getX() || dynamic_cast<const Etat2D&>(dep).getY()!=dynamic_cast<Etat2D&>(dest).getY()) dest = dep;
   //std::cout<<"dest dep ok, x= "<<dep.getX()<<" y= "<<dep.getY()<<std::endl;
   for (int i = 0; i < dep.getX(); i++)
   {
      for(int j=0; j<dynamic_cast<const Etat2D&>(dep).getY(); j++)
      {
         unsigned int nbVvivant=0;
         //std::cout<<"avant boucles de get cellule ok"<<std::endl;
         for(int x=i-1; x<=i+1; ++x)
         {
            for(int y=j-1; y<=j+1; ++y)
            {
               std::cout<<"x="<<x<<" y="<<y<<std::endl;
               //std::cout<<"appel get cellule avec i="<<i<<"et j="<<j<<std::endl;
               if ((x!=i || y!=j) && dynamic_cast<const Etat2D&>(dep).getCellule(x,y) )
               {
                  nbVvivant++;
                  std::cout<<"  x="<<x<<" y="<<y<<" nb voisins vivants ++ --> "<<nbVvivant<<std::endl;
               }
            }
         }
         std::cout<<"i="<<i<<" j="<<j<<" nb voisins vivants : "<<nbVvivant<<std::endl;
         if (nbVvivant<minToNotDie || nbVvivant>maxToNotDie)
            { //std::cout<<"appel set cellule avec i="<<i<<"et j="<<j<<std::endl;
               dynamic_cast<Etat2D&>(dest).setCellule(i,j, false);}
         else
            { //std::cout<<"appel set cellule avec i="<<i<<"et j="<<j<<std::endl;
               dynamic_cast<Etat2D&>(dest).setCellule(i, j, true);}
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

