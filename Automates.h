#ifndef AUTOMATES_H_INCLUDED
#define AUTOMATES_H_INCLUDED
#include "etats.h"

#include <iostream>
#include <list>
#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QColor>
#include "etats.h"
#include "autocell.h"

#define MAX_BUFFER_SIZE 20

#define HEIGHT_CELLULE 30
#define WIDTH_CELLULE 49

class AutomateException {
private:
      std::string info;
public:
      AutomateException(const std::string& message):info(message) {}
      std::string getInfo() const { return info; }
};

class Cellules : public QWidget{
    Q_OBJECT
    unsigned int etatsPossibles;
    unsigned int I;
    unsigned int J;
    unsigned int K;
    unsigned int couleur;
    QTableWidget* voisins;
    QVBoxLayout* lay;
public:
    Cellules (unsigned int i, unsigned int j, unsigned int k, unsigned int e = NB_COULEURS);
    Cellules (unsigned int e = NB_COULEURS);
    Cellules& operator=(const Cellules& c);
    unsigned int getColor() {return couleur;}
signals:
    void changed(unsigned int i, unsigned int j, unsigned int k);
private slots:
    void synch(int row, int column);
};

class Automate : public QWidget{
    Q_OBJECT
    friend class Configurateur;
    QLabel* configuration;
protected:
    AutoCell* grille;
    const Etat* etatInitial;
    std::list<Etat*> buffer;
    unsigned int nb;
    unsigned int maxSize;
    QHBoxLayout* principal;
    QVBoxLayout* configs;
    QFormLayout* commun;
    QSpinBox* dim;
    QLabel* dimension;
    QSpinBox* dim2;
    QLabel* dimension2;
    //virtual Etat* getCopy(const Etat* e) = 0;
    const Etat* getNext();
    const Etat* getPrev();
    virtual void addEtatGenerators() = 0;
public:
    Automate();
    virtual ~Automate() {}
    unsigned int getDimension() { return dim->value(); }
    const Etat* getInitial() const { return etatInitial; }
    void setInitial() { etatInitial = grille->getInitial(); }
    const Etat* getLast();
    void clearBuffer();
    virtual Etat* appliquerTransition(const Etat* dep) const = 0;
signals:
    //void inEtatInitial();
private slots:
    virtual void synchDimension(int d) = 0;
    virtual void synchDimension2(int d) = 0;
    //void setEtatInitial(const Etat* e);
    virtual void simuler() = 0;
};
/*
class Automate {

    public:
        Automate() {}
        virtual ~Automate (){}
        virtual void appliquerTransition(const Etat& dep, Etat& dest) const = 0;
};*/

class Automate1D : public Automate {
    Q_OBJECT
    friend class Config1D;
    friend class AutomateManager;
    const unsigned int etatsPossibles;
    unsigned int*** regles;
    Cellules*** inRegles;
    /*unsigned short int numero;
    std::string numeroBit;
    Automate1D(unsigned short int num);
    Automate1D(const std::string& num);
    ~Automate1D(){}*/
protected:
    Automate1D(unsigned int e);
    //Automate1D(unsigned short int num): numero(num),numeroBit(NumToNumBit(num)) {}
    //Automate1D(const std::string& num): numero(NumBitToNum(num)),numeroBit(num) {}
    ~Automate1D();
    void addEtatGenerators();
    Automate1D(const Automate1D& a);
    Automate1D& operator=(const Automate1D& a);
	 friend class AutomateManager;
public:
    //unsigned short int getNumero() const { return numero; }
    //const std::string& getNumeroBit() const { return numeroBit; }
    Etat* appliquerTransition(const Etat* dep) const;
private slots:
    void synchDimension(int d);
    void synchDimension2(int d);
    void synchRegles(unsigned int i, unsigned int j, unsigned int k);
    void simuler();
};

class Automate2D : public Automate {
    Q_OBJECT
    friend class Config2D;
private:
    unsigned int minToNotDie;
    unsigned int maxToNotDie;
    //Etat* getCopy(const Etat* e);
protected:
    Automate2D (unsigned int minNd, unsigned int maxNd);
    ~Automate2D () {}
    void addEtatGenerators(){}
public:
    //void print (std::ostream& os) const;
    //public:
    Etat* appliquerTransition (const Etat* dep) const;
    unsigned int getMinToNotDie () const { return minToNotDie; }
    unsigned int getMaxToNotDie () const { return maxToNotDie; }
private slots:
    void synchDimension(int colonnes);
    void synchDimension2(int lignes){}
    void simuler() {}
};
/*
class Automate2D :  public Automate
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
*/

class AutomateFdF : public Automate
{
public:
    AutomateFdF() {}
    ~AutomateFdF () {}
    void appliquerTransition (const Etat& dep, Etat& dest) const;
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

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);

#endif // AUTOMATES_H_INCLUDED
