#ifndef AUTOMATES_H_INCLUDED
#define AUTOMATES_H_INCLUDED
#include "etats.h"

class AutomateException {
private:
      std::string info;
public:
      AutomateException(const std::string& message):info(message) {}
      std::string getInfo() const { return info; }

};

class Automate {

    private:

    public:
        Automate() {}
        virtual ~Automate (){}

        virtual void appliquerTransition(const Etat& dep, Etat& dest) const = 0;

};

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);

class Automate1D : public Automate {
   unsigned short int numero;
	 std::string numeroBit;

	 Automate1D(unsigned short int num);
	 Automate1D(const std::string& num);
    ~Automate1D(){}
    Automate1D(const Automate1D& a);
    Automate1D& operator=(const Automate1D& a);
	 friend class AutomateManager;
public:
	unsigned short int getNumero() const { return numero; }
	const std::string& getNumeroBit() const { return numeroBit; }
	void appliquerTransition(const Etat& dep, Etat& dest) const;
};

class Automate2D /*:  public Automate*/
{

    private:

        unsigned int minToNotDie;
        unsigned int maxToNotDie;


    public:
        Automate2D (unsigned int minNd, unsigned int maxNd) : minToNotDie (minNd), maxToNotDie (maxNd) { if(minNd>maxNd){throw AutomateException("Minimum value superior than maximum value");}}
        ~Automate2D () {}


        //void print (std::ostream& os) const;
   //public:
        void appliquerTransition (const Etat& dep, Etat& dest) const;

        unsigned int getMinToNotDie () const { return minToNotDie; }
        unsigned int getMaxToNotDie () const { return maxToNotDie; }


};

class AutomateManager
{
   Automate1D* automates[256];
   static AutomateManager* instance;

   AutomateManager();
   AutomateManager& operator= (const AutomateManager& a)=delete;
   ~AutomateManager();



public:
   const Automate1D& getAutomate(unsigned short int num);
   const Automate1D& getAutomate(std::string& num);

   static AutomateManager& getAutomateManager();
   static void freeAutomateManager();

};

#endif // AUTOMATES_H_INCLUDED
