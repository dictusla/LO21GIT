#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QtWidgets>
#include <QComboBox>
//#include "Automates.h"
#include "etats.h"
#include "generateur.h"
//#include "simulateur.h"

#define DIMENSION_MAX 15
#define DIMENSION_MIN 10

#define TAILLE_CELLULE 49

const QString couleurs[] = {"white",  "darkGreen", "black", "red", "darkBlue", "yellow"};
#define NB_COULEURS 6

class AutoCell : public QWidget{
    Q_OBJECT
    QVBoxLayout* principal;
    QHBoxLayout* commun;        //layout pour les bouttons (Load Etat initial, Save etat)
    QPushButton* simulation;
protected:
    Etat* initial;      //pour completer l'affichage dans les constructeurs des classe heritees
    unsigned int etatsPossibles;
    unsigned int etatsPossiblesGeneration;
    unsigned int dimX;
    unsigned int dimY;      //nombre de lignes en 2D et d'etats a afficher en 1D
    unsigned int nbGenerators;
    const EtatGenerator** generators;
    QVBoxLayout* specifique;        //layout pour afficher au DESSUS du bouton simuler
    QHBoxLayout* bouttons;
    QVBoxLayout* grille;       //layout pour afficher au DESSOUS du bouton simuler
    QComboBox* generateurs;
    QPushButton* generer;
    QTableWidget* etats;
public:
    explicit AutoCell(unsigned int x, unsigned int y, unsigned int e, unsigned int eg = 2, QWidget* parent = nullptr);
    virtual void actualize(const Etat* e) = 0;
    const Etat* getInitial() {return initial;}
    virtual void setInitial(const Etat* e) = 0;
    virtual void addGenerator(const EtatGenerator* g);
signals:
    //void giveEtatInitial(const Etat* e);
    void simuler();
    void reset();
private slots:
    void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);
    virtual void cellActivation(const QModelIndex& index) = 0;
    void launchSimulation();
    virtual void genererEtat() = 0;
public slots:
    //void EtatInitial() { emit giveEtatInitial(initial);}
};

class AutoCell1D : public AutoCell{
    Q_OBJECT
    unsigned int r;
    //QSpinBox* num; // numéro
    //QLineEdit* numeroBit[8]; // un QLineEdit par bit
    //QLabel* numl;
    //QLabel* numeroBitl[8];
    //QVBoxLayout* numc;
    //QVBoxLayout* bitc[8];
    //QHBoxLayout* numeroc;
    //QIntValidator* zeroOneValidator;
    QTableWidget* depart;
    //QVBoxLayout* couche;
    //QPushButton* quit;
    //QTabWidget* onglets;
    //QWidget* page1;
    //QWidget* page2;
    //QVBoxLayout* main;
public:
    AutoCell1D(unsigned int e, unsigned int dim, unsigned int l, unsigned int eg = 2);
    void actualize(const Etat* e);
    void setInitial(const Etat* e);
    void addGenerator(const EtatGenerator* g);
private slots:
    void cellActivation(const QModelIndex& index);
    void genererEtat();
};

class AutoCell2D : public AutoCell{
    Q_OBJECT

public:
    AutoCell2D(unsigned int lines, unsigned int columns, unsigned int e, unsigned int eg = 2);
    void actualize(const Etat* e) ;
    void setInitial(const Etat* e) ;
    void addGenerator(const EtatGenerator* g);
    void synchDimension(unsigned int X, unsigned int Y);
private slots:
    void cellActivation(const QModelIndex& index);
    void genererEtat();
};

#endif // AUTOCELL_H
