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
    virtual Etat2D* generateEtat(unsigned int colonnes, unsigned int lignes, unsigned int etatsPossibles) const = 0;
};

class RandGenerator1D : public EtatGenerator1D {//->singletons
    const QString name = QString("Aléatoire");
    static RandGenerator1D* InstanceUnique;
    RandGenerator1D(){}
    RandGenerator1D(const RandGenerator1D&) = delete;
    RandGenerator1D& operator=(const RandGenerator1D&) = delete;
public:
    const QString getName() const {return name;}
    static RandGenerator1D* getInstance();
    static void deleteInstance();
    Etat1D* generateEtat(unsigned int dim, unsigned int etatsPossibles) const ;
};

class RandGenerator2D : public EtatGenerator2D {
    const QString name = QString("Aléatoire");
    static RandGenerator2D* InstanceUnique;
    RandGenerator2D(){}
    RandGenerator2D(const RandGenerator2D&) = delete;
    RandGenerator2D& operator=(const RandGenerator2D&) = delete;
public:
    const QString getName() const {return name;}
    static RandGenerator2D* getInstance();
    static void deleteInstance();
    Etat2D* generateEtat(unsigned int colonnes, unsigned int lignes, unsigned int etatsPossibles) const ;
};

#endif // GENERATEUR_H
