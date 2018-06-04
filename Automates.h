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

        virtual void applyTransition (Etat& currentEtat) const;
        unsigned int getRuleNumber () const{ return this->ruleNumber; }
        void setRule (int ruleN);
        virtual void print (std::ostream& os) const;


    protected:    
};
#endif // AUTOMATES_H_INCLUDED
