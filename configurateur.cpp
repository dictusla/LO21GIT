#include "configurateur.h"
#include <iostream>

QString Configurateur::nom = " - ";
QString Config1D::nom = "Automate1D";
QString Config2D::nom = "Jeu de la vie";
QString ConfigFdF::nom = "Feu de Foret";

/*======================================*/

Interface* Interface::interfaceUnique = nullptr;

Configurateur::Configurateur() {
    principal = new QHBoxLayout;
    specifique = new QHBoxLayout;
    go = new QPushButton("GO");

    principal->addLayout(specifique);
    principal->addWidget(go);

    setLayout(principal);
}

Configurateur::~Configurateur(){
    delete automat;
}

Config1D::Config1D() : Configurateur() {
    col = new QSpinBox();
    colors = new QLabel("Etats possibles");

    col->setRange(2,4);

    specifique->addWidget(colors);
    specifique->addWidget(col);
}

Config1D::~Config1D() {}

QString Config1D::getNom(){return Config1D::nom;}

void Config1D::setAutomate(){
    automat = new Automate1D(col->value());
}

void Config1D::loadAutomate(){
}

Config2D::Config2D() {
    live = new QLabel("Minimum de voisins:");
    die = new QLabel("Maximum de voisins:");
    Min = new QSpinBox;
    Max = new QSpinBox;

    Min->setRange(0,8);
    Max->setRange(0,8);

    specifique->addWidget(live);
    specifique->addWidget(Min);
    specifique->addWidget(die);
    specifique->addWidget(Max);

    connect(Min,SIGNAL(valueChanged(int)),this,SLOT(synchMax(int)));
    connect(Max,SIGNAL(valueChanged(int)),this,SLOT(synchMin(int)));
}

QString Config2D::getNom(){return Config2D::nom;}

void Config2D::synchMax(int a) {if(a>Max->value()) Max->setValue(a);}

void Config2D::synchMin(int a) {if(a<Min->value()) Min->setValue(a);}

void Config2D::setAutomate(){
    automat = new Automate2D(Min->value(), Max->value());
}

void Config2D::loadAutomate(){}

ConfigFdF::ConfigFdF() : Configurateur() {}

void ConfigFdF::setAutomate(){
    automat = new AutomateFdF();
}

QString ConfigFdF::getNom(){return ConfigFdF::nom;}

Interface::Interface() : nbTypes(1){
    bar = new QToolBar;
    centralArea = new QMdiArea;
    typeAut = new QComboBox;
    configBar = new QWidget;
    QWidget* commun = new QWidget;
    configLay = new QVBoxLayout;
    QHBoxLayout* lay1 = new QHBoxLayout;
    choixtype = new QLabel("Choisir un Automate : ");
    loadAut = new QPushButton("LOAD");

    types = new Configurateur*[1];
    sub = new QMdiSubWindow*[1];
    types[0] = nullptr;
    sub[0] = nullptr;

    typeAut->addItem(" - ");
    //configBar->setContentsMargins(configBar->contentsMargins().left(),0,configBar->contentsMargins().right(),0);
    bar->setMovable(false);
    bar->setFixedHeight(70);

    lay1->addWidget(choixtype);
    lay1->addWidget(typeAut);
    commun->setLayout(lay1);
    configBar->setLayout(configLay);
    bar->addWidget(commun);
    bar->addWidget(loadAut);
    bar->addSeparator();
    bar->addWidget(configBar);

    addToolBar(Qt::TopToolBarArea, bar);
    setCentralWidget(centralArea);

    //sub = new QMdiSubWindow;
    //centralArea->addSubWindow(sub);

    connect(typeAut,SIGNAL(currentIndexChanged(int)),this,SLOT(ComboSynch(int)));
    connect(loadAut,SIGNAL(clicked()),this,SLOT(load()));
}

Interface* Interface::getInterface(){
    if (interfaceUnique == nullptr){
        interfaceUnique = new Interface();
    }
    return interfaceUnique;
}

void Interface::libererInterface(){
    delete interfaceUnique;
    interfaceUnique = nullptr;
}

void Interface::addAutoType(Configurateur* pt){
    Configurateur** newTab = new Configurateur*[nbTypes+1];
    QMdiSubWindow** newTab2 = new QMdiSubWindow*[nbTypes+1];
    for (unsigned int i = 0; i < nbTypes; i++){
        newTab[i] = types[i];
        newTab2[i] = sub[i];
    }
    newTab[nbTypes] = pt;
    pt->ventana = new QMdiSubWindow;
    newTab2[nbTypes] = centralArea->addSubWindow(pt->ventana);
    nbTypes+=1;
    Configurateur** oldTab = types;
    QMdiSubWindow** oldTab2 = sub;
    types = newTab;
    sub = newTab2;
    delete [] oldTab;
    delete [] oldTab2;

    typeAut->addItem(pt->getNom());
    configLay->addWidget(pt);
    pt->hide();
    //pt->ventana->close();

    //connect(pt->load,SIGNAL(clicked()),this,SLOT(load()));
    connect(pt->go,SIGNAL(clicked()),this,SLOT(setSubWindow()));
}

void Interface::ComboSynch(int b){
    for (unsigned int i = 1; i < nbTypes; i++){
        if ((int)i==b){
            if(types[i]->isVisible()==false) types[i]->show();
        }
        else{
            if(types[i]->isVisible()) types[i]->hide();
        }
    }
}

void Interface::setSubWindow(){
    /*
    for (unsigned int i =1; i < nbTypes; i++){
        if(types[i]->isVisible()){
            types[i]->setAutomate();
            types[i]->ventana->setWidget(types[i]->automat);
            types[i]->ventana->show();
        }
    }*/
    unsigned int index = typeAut->currentIndex();
    types[index]->setAutomate();
    types[index]->ventana->setWidget(types[index]->automat);
    types[index]->ventana->show();
}

void Interface::load(){
    for (unsigned int i =1; i < nbTypes; i++){
        if(types[i]->isVisible()){
            types[i]->loadAutomate();
            types[i]->ventana->setWidget(types[i]->automat);
            types[i]->ventana->show();
        }
    }
}

void Interface::synch(){
    /*std::cout<<"synch"<<std::endl;
    if(sub->isVisible()) sub->hide();
    else sub->show();*/
}
