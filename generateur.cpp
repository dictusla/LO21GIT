#include "generateur.h"

Etat1D* RandGenerator1D::generateEtat(unsigned int dim, unsigned int etatsPossibles) const {
    Etat1D* pt = new Etat1D(0,dim);
    for (unsigned int i = 0; i < dim; i++){
        pt->setCellule(i, rand() % etatsPossibles);
    }
    return pt;
}

Etat2D* RandGenerator2D::generateEtat(unsigned int lignes, unsigned int colonnes, unsigned int etatsPossibles) const{
    Etat2D* pt = new Etat2D(0,colonnes, lignes);
    for (unsigned int i = 0; i < colonnes; i++){
        for (unsigned int j = 0; j < lignes; i++){
            pt->setCellule(i,j,rand() % etatsPossibles);
        }
    }
    return pt;
}
