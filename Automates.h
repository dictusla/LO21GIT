#ifndef AUTOMATES_H_INCLUDED
#define AUTOMATES_H_INCLUDED

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
        virtual ~Automate () = 0; 

        virtual void applyTransition (Etat& currentEtat) const = 0;
        virtual void print (std::ostream& os) const = 0;

    protected:

};
 
class Automate1D : public Automate {
     private:
        static const unsigned int etatMaxNbColumn = 10;
        static const  short unsigned int maxNbEtats = 7; // Nombre d'etat max que peuvent prendre les cellules à ne pas confondre avec l'état d'un automate entre deux transitions
        unsigned int ruleNumber; // Regle de transition
       

    public:
        Automate1D (unsigned int ruleN); 
        Automate1D (const Automate1D& a);
        virtual ~Automate1D () {}

        static unsigned int getMaxNbEtat () { return maxNbEtats; }
        static unsigned int getStateMaxNbColumn () { return etatMaxNbColumn; }

        virtual void applyTransition (Etat1D& currentEtat) const;
        unsigned int getRuleNumber () const{ return this->ruleNumber; }
        void setRule (int ruleN);
        virtual void print (std::ostream& os) const;


    protected:    
};

class Automate2D : public Automate
{

    private:
        static const short unsigned int etatMaxNbLine = 10;
        static const short unsigned int etatMaxNbColumn = 10;
        static const unsigned int nbToBorn = 3;

        unsigned int minToNotDie;
        unsigned int maxToNotDie;

        




    public:
        Automate2D (unsigned int minNd, unsigned int maxNd) : minToNotDie (minNd), maxToNotDie (maxNd) { if(minNd>maxNd){throw AutomateException("Minimum value superior than maximum value");}}
        virtual ~Automate2D () {}

        bool isNotInRange(const Etat& currentEtat) const;

        virtual void print (std::ostream& os) const;
        virtual void applyTransition (Etat2D& currentEtat) const;
        virtual bool willBeBorn (unsigned int line, unsigned int column,Etat2D& s) const;
        virtual bool willDie (unsigned int line, unsigned int column,Etat2D& s) const;

        unsigned int getMinToNotDie () const { return this->minToNotDie; }
        unsigned int getMaxToNotDie () const { return this->maxToNotDie; }

        static unsigned int getNbToBorn () { return nbToBorn; }
        static unsigned int getEtatMaxNbLine () { return etatMaxNbLine; }
        static unsigned int getEtatMaxNbColumn () { return etatMaxNbColumn; }
        
    protected:

};


#endif // AUTOMATES_H_INCLUDED
