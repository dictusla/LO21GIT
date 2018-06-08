#include "autocell.h"
#include "C:\Users\dictu\Documents\UTC\Cours\GI01\LO21\LO21Projet\Automates.h"
#include "C:\Users\dictu\Documents\UTC\Cours\GI01\LO21\LO21Projet\etats.h"
#include "C:\Users\dictu\Documents\UTC\Cours\GI01\LO21\LO21Projet\simulateur.h"


AutoCell::AutoCell(QWidget *parent) : QWidget(parent) {
    num = new QSpinBox(this);
    num->setRange(0, 255);
    num->setValue(0);
    numl = new QLabel("Numéro", this);
    numc = new QVBoxLayout;
    numc->addWidget(numl);
    numc->addWidget(num);
    numeroc = new QHBoxLayout;
    numeroc->addLayout(numc);
    zeroOneValidator = new QIntValidator(this);
    zeroOneValidator->setRange(0, 1);
    numeroBitl[0] = new QLabel("111");
    numeroBitl[1] = new QLabel("110");
    numeroBitl[2] = new QLabel("101");
    numeroBitl[3] = new QLabel("100");
    numeroBitl[4] = new QLabel("011");
    numeroBitl[5] = new QLabel("010");
    numeroBitl[6] = new QLabel("001");
    numeroBitl[7] = new QLabel("000");
    for(unsigned int counter = 0; counter < 8; ++counter) {
        numeroBit[counter] = new QLineEdit(this);
        numeroBit[counter]->setFixedWidth(20); //pixels
        numeroBit[counter]->setMaxLength(1); //caractères
        numeroBit[counter]->setText("0");
        numeroBit[counter]->setValidator(zeroOneValidator);
        bitc[counter] = new QVBoxLayout;
        bitc[counter]->addWidget(numeroBitl[counter]);
        bitc[counter]->addWidget(numeroBit[counter]);
        numeroc->addLayout(bitc[counter]);
        connect(numeroBit[counter], SIGNAL(textChanged(QString)), this, SLOT(synchronizeNumBitToNum(QString)));
    }
    connect(num, SIGNAL(valueChanged(int)), this, SLOT(synchronizeNumToNumBit(int)));
    // Qestion 2
    couche = new QVBoxLayout;
    couche->addLayout(numeroc);
    unsigned int taille = 25; //pixels
    depart = new QTableWidget(1, 25, this); //1 ligne, 25 colonnes
    depart->setFixedSize(dimension*taille, taille); // largeur = nombre_cellules*taille_cellule, hauteur = taille_cellule
    depart->horizontalHeader()->setVisible(false); // masque le header horizontal
    depart->verticalHeader()->setVisible(false); // masque le header vertical
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // désactive la scroll barre
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // idem
    // création des items du QTableWidget, initialisés à "" avec un fond blanc
    for(unsigned int counter = 0; counter < dimension; ++counter) {
        depart->setColumnWidth(counter, taille);
        depart->setItem(0, counter, new QTableWidgetItem(""));
        depart->item(0, counter)->setBackgroundColor("white");
        depart->item(0, counter)->setTextColor("white");
    }
    connect(depart, SIGNAL(doubleClicked(QModelIndex)), this,
            SLOT(cellActivation(QModelIndex)));
    couche->addWidget(depart);
    // Question 3
    etats = new QTableWidget(dimension, dimension, this);
    etats->setFixedSize(dimension*taille, dimension*taille);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers); // désactive la modification par l'utilisateur
    // on va créer les items, on utilise 2 boucles car on parcourt un tableau 2 dimensions
    for(unsigned int ligne = 0; ligne < dimension; ++ligne) {
        // fixe les dimensions des lignes et des colonnes
        etats->setColumnWidth(ligne, taille);
        etats->setRowHeight(ligne, taille);
        for(unsigned int colonne = 0; colonne < dimension; ++colonne) {
            etats->setItem(ligne, colonne, new QTableWidgetItem(""));
            etats->item(ligne, colonne)->setBackgroundColor("white");
            etats->item(ligne, colonne)->setTextColor("white");
        }
    }
    simulation = new QPushButton("Simulation !", this);
    connect(simulation, SIGNAL(clicked()), this, SLOT(launchSimulation()));
    couche->addWidget(simulation);
    couche->addWidget(etats);
    page1= new QWidget;
    page2= new QWidget;
    page1->setLayout(couche);
    onglets= new QTabWidget;
    onglets->addTab(page1,"Automate 1D");
    onglets->addTab(page2,"Jeu de la vie");
    quit=new QPushButton("Quitter");
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    main=new QVBoxLayout;
    main->addWidget(onglets);
    main->addWidget(quit);
    setLayout(main);
}


void AutoCell::cellActivation(const QModelIndex& index) {
    if (depart->item(0, index.column())->text() == "") {
        depart->item(0, index.column())->setText("_");
        depart->item(0, index.column())->setBackgroundColor("black");
        depart->item(0, index.column())->setTextColor("black");
    } else {
        depart->item(0, index.column())->setText("");
        depart->item(0, index.column())->setBackgroundColor("white");
        depart->item(0, index.column())->setTextColor("white");
    }
}

void AutoCell::synchronizeNumToNumBit(int i) {
    std::string numBit = NumToNumBit(i);
    for(unsigned int counter = 0; counter < 8; ++counter) {
        numeroBit[counter]->setText(QString(numBit[counter]));
    }
}

void AutoCell::synchronizeNumBitToNum(const QString& s) {
    if (s == "") {
        return;
    }
    std::string numBit = "";
    for(unsigned int counter = 0; counter < 8; ++counter) {
        numBit += numeroBit[counter]->text().toStdString();
    }
    num->setValue(NumBitToNum(numBit));
}

void AutoCell::launchSimulation() {
    // création de l'état
    Etat1D e(1,dimension);
    // on récupère les données de l'état de l'interface graphique pour que ça corresponde à l'objet qu'on vient de créer
    for(unsigned int counter = 0; counter < dimension; ++counter) {
        if(depart->item(0, counter)->text() != "") {
                e.setCellule(counter, true);
        }
    }
    // on récupère l'automate correspondant au numéro de l'interface graphique, en utilisant l'AutomateManager
    // à noter, il n'est pas nécessaire d'instancier un objet AutomateManager, comme il s'agit d'un singleton,
    // on peut considérer que l'objet existe déjà dans le système
    const Automate1D& a = AutomateManager::getAutomateManager().getAutomate(num->value());
    // on construit l'objet simulateur correspondant
    Simulateur sim(a, e, dimension);
    // on applique les transitions au simulateur en affichant le résultat dans l'interface graphique
    for(unsigned int step = 0; step < dimension; ++step) {
        // on applique la transition
        sim.next();
        // on récupère le dernier état
        const Etat& etat = sim.dernier();
        // on l'affiche
        for(unsigned int colonne = 0; colonne < dimension; ++colonne) {
            if (dynamic_cast<const Etat1D&>(etat).getCellule(colonne) == true) {
                etats->item(step, colonne)->setText("_");
                etats->item(step, colonne)->setBackgroundColor("black");
                etats->item(step, colonne)->setTextColor("black");
            } else {
                etats->item(step, colonne)->setText("");
                etats->item(step, colonne)->setBackgroundColor("white");
                etats->item(step, colonne)->setTextColor("white");
            }
        }
        //Sleep(1000);
    }
}

