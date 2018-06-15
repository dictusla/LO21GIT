#include "generateur.h"

RandGenerator1D* RandGenerator1D::InstanceUnique = nullptr;
RandGenerator2D* RandGenerator2D::InstanceUnique = nullptr;

Etat1D* RandGenerator1D::generateEtat(unsigned int dim, unsigned int etatsPossibles) const {
    Etat1D* pt = new Etat1D(0,dim);
    for (unsigned int i = 0; i < dim; i++){
        pt->setCellule(i, rand() % etatsPossibles);
    }
    return pt;
}

RandGenerator1D* RandGenerator1D::getInstance(){
    if (InstanceUnique == nullptr){
        InstanceUnique = new RandGenerator1D;
    }
    return InstanceUnique;
}

void RandGenerator1D::deleteInstance(){
    if (InstanceUnique != nullptr){
        delete InstanceUnique;
        InstanceUnique = nullptr;
    }
}

Etat2D* RandGenerator2D::generateEtat(unsigned int colonnes, unsigned int lignes, unsigned int etatsPossibles) const{
    Etat2D* pt = new Etat2D(0,colonnes, lignes);
    for (unsigned int i = 0; i < colonnes; i++){
        for (unsigned int j = 0; j < lignes; j++){
            pt->setCellule(i,j,rand() % etatsPossibles);
        }
    }
    return pt;
}

RandGenerator2D* RandGenerator2D::getInstance(){
    if (InstanceUnique == nullptr){
        InstanceUnique = new RandGenerator2D;
    }
    return InstanceUnique;
}

void RandGenerator2D::deleteInstance(){
    if (InstanceUnique != nullptr){
        delete InstanceUnique;
        InstanceUnique = nullptr;
    }
}
