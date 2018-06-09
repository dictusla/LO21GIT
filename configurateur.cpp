#include "configurateur.h"
#include <iostream>

#define DIMENSION_MAX 25
#define DIMENSION_MIN 10

QString configurateur::nom = " - ";
QString config1D::nom = "Automate1D";
QString config2D::nom = "Jeu de la vie";

configurateur::configurateur() {
    principal = new QVBoxLayout;
    specifique = new QVBoxLayout;
    commun = new QHBoxLayout;
    dimension = new QLabel("Dimension");
    dim= new QSpinBox();
    go = new QPushButton("GO");
    dim->setRange(DIMENSION_MIN,DIMENSION_MAX);

    commun->addWidget(dimension);
    commun->addWidget(dim);
    principal->addLayout(commun);
    principal->addLayout(specifique);
    principal->addWidget(go);

    setLayout(principal);

    connect(go,SIGNAL(clicked()),this,SLOT(setAutomate()));
}

configurateur::~configurateur(){
    delete automat;
}

QString configurateur::getNom() {return configurateur::nom;}

void configurateur::setAutomate(){
    automat = nullptr;
}

config1D::config1D() : configurateur() {
    C = new QHBoxLayout;
    col = new QSpinBox();
    colors = new QLabel("Etats possibles");

    col->setRange(2,4);

    C->addWidget(colors);
    C->addWidget(col);
    specifique->addLayout(C);
}

config1D::~config1D() {}

QString config1D::getNom(){return config1D::nom;}

void config1D::setAutomate(){
    automat = new Automate1D();
}

config2D::config2D() {
    lay1 = new QHBoxLayout;
    qwea = new QLabel("-completer-");

    lay1->addWidget(qwea);
    specifique->addLayout(lay1);
}

config2D::~config2D() {}

QString config2D::getNom(){return config1D::nom;}

void config2D::setAutomate(){
    automat = new Automate2D;
}

Interface::Interface() : nbTypes(1){
    Bar = new QToolBar;
    QMdiArea* area = new QMdiArea;
    typeAut = new QComboBox;
    configBar = new QWidget;
    QWidget* commun = new QWidget;
    configLay = new QVBoxLayout;
    QVBoxLayout* lay1 = new QVBoxLayout;
    choixtype = new QLabel("Choisir un Automate");
    go = new QPushButton("GO");

    Types = new configurateur*[1];
    Types[0] = nullptr;
    typeAut->addItem(configurateur::nom);

    Bar->setMovable(false);
    Bar->setFixedWidth(200);

    lay1->addWidget(choixtype);
    lay1->addWidget(typeAut);
    commun->setLayout(lay1);
    configBar->setLayout(configLay);
    Bar->addWidget(commun);
    Bar->addSeparator();
    Bar->addWidget(configBar);
    this->addToolBar(Qt::LeftToolBarArea, Bar);
    this->setCentralWidget(area);

    connect(typeAut,SIGNAL(currentIndexChanged(int)),this,SLOT(ComboSynch(int)));
}

void Interface::addAutoType(configurateur* pt){
    configurateur** newTab = new configurateur*[nbTypes+1];
    for (unsigned int i = 0; i < nbTypes; i++){
        newTab[i] = Types[i];
    }
    newTab[nbTypes] = pt;
    nbTypes+=1;
    configurateur** oldTab = Types;
    Types = newTab;
    delete [] oldTab;

    typeAut->addItem(pt->getNom());
    configLay->addWidget(pt);
    pt->hide();
}

void Interface::ComboSynch(int b){
    for (unsigned int i = 1; i < nbTypes; i++){
        if ((int)i==b){
            if(Types[i]->isVisible()==false) Types[i]->show();
        }
        else{
            if(Types[i]->isVisible()) Types[i]->hide();
        }
    }
}
