#ifndef GENERATEUR_H
#define GENERATEUR_H

#include <QString>
#include "etats.h"

class EtatGenerator{
    const QString name = " - ";
public:
    virtual const QString getName() const = 0;
};

class EtatGenerator1D : public EtatGenerator{
    const QString name = QString("1D");
public:
    //const QString getName() const {return name;}
    virtual Etat1D* generateEtat(unsigned int dim, unsigned int etatsPossibles) const = 0;
};

class EtatGenerator2D : public EtatGenerator{
    const QString name = QString("2D");
public:
    //const QString getName() const {return name;}
    virtual Etat2D* generateEtat(unsigned int lignes, unsigned int colonnes, unsigned int etatsPossibles) const = 0;
};

class RandGenerator1D : public EtatGenerator1D {//->singletons
    const QString name = QString("Aléatoire");
public:
    const QString getName() const {return name;}
    Etat1D* generateEtat(unsigned int dim, unsigned int etatsPossibles) const ;
};

class RandGenerator2D : public EtatGenerator2D {
    const QString name = QString("Aléatoire");
public:
    const QString getName() const {return name;}
    Etat2D* generateEtat(unsigned int lignes, unsigned int colonnes, unsigned int etatsPossibles) const ;
};

#endif // GENERATEUR_H
