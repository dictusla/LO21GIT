#include "autocell.h"

AutoCell::AutoCell(unsigned int x, unsigned int y, unsigned int e, unsigned int eg, QWidget *parent) :
    dimX(x), dimY(y), etatsPossibles(e), etatsPossiblesGeneration(eg), QWidget(parent), nbGenerators(0) {
    principal = new QVBoxLayout;
    commun = new QHBoxLayout;
    specifique = new QVBoxLayout;
    bouttons = new QHBoxLayout;
    grille = new QVBoxLayout;
    generateurs =  new QComboBox;
    generer =  new QPushButton("Générer");
    simulation = new QPushButton("Simulation !", this);

    commun->addWidget(generateurs);
    commun->addWidget(generer);
    bouttons->addWidget(simulation);
    principal->addLayout(commun);
    principal->addLayout(specifique);
    principal->addLayout(bouttons);
    principal->addLayout(grille);
    setLayout(principal);

    setFixedWidth(dimX*TAILLE_CELLULE+20);
    etats = new QTableWidget(dimY, dimX, this);
    etats->setFixedSize(dimX*TAILLE_CELLULE, dimY*TAILLE_CELLULE);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // désactive la modification par l'utilisateur
    // on va créer les items, on utilise 2 boucles car on parcourt un tableau 2 dimensions
    for (unsigned int i = 0; i < dimX; i++){
        etats->setColumnWidth(i, TAILLE_CELLULE);
    }
    for(unsigned int line = 0; line < dimY; ++line) {
        // fixe les dimensions des lignes et des colonnes
        etats->setRowHeight(line, TAILLE_CELLULE);
        for(unsigned int column = 0; column < dimX; ++column) {
            etats->setItem(line, column, new QTableWidgetItem(""));
            etats->item(line, column)->setBackgroundColor("white");
            etats->item(line, column)->setTextColor("white");
        }
    }
    grille->addWidget(etats);

    generators = nullptr;
    connect(simulation, SIGNAL(clicked()), this, SLOT(launchSimulation()));
}

void AutoCell::synchronizeNumToNumBit(int i) {
//    std::string numBit = NumToNumBit(i);
//    for(unsigned int counter = 0; counter < 8; ++counter) {
//        numeroBit[counter]->setText(QString(numBit[counter]));
//    }
}

void AutoCell::synchronizeNumBitToNum(const QString& s) {
//    if (s == "") {
//        return;
//    }
//    std::string numBit = "";
//    for(unsigned int counter = 0; counter < 8; ++counter) {
//        numBit += numeroBit[counter]->text().toStdString();
//    }
//    num->setValue(NumBitToNum(numBit));
}

void AutoCell::launchSimulation() {
    emit simuler();
    //emit simuler();

    // création de l'état
    //Etat1D e(1,dimX);
    // on récupère les données de l'état de l'interface graphique pour que ça corresponde à l'objet qu'on vient de créer
//    for(unsigned int counter = 0; counter < dimX; ++counter) {
//        if(depart->item(0, counter)->text() != "") {
//                initial.setCellule(counter,true );
//        }
//    }
//    // on récupère l'automate correspondant au numéro de l'interface graphique, en utilisant l'AutomateManager
//    // à noter, il n'est pas nécessaire d'instancier un objet AutomateManager, comme il s'agit d'un singleton,
//    // on peut considérer que l'objet existe déjà dans le système
//    const Automate1D& a = AutomateManager::getAutomateManager().getAutomate(num->value());
//    // on construit l'objet simulateur correspondant
//    Simulateur sim(a, e, dimX);
//    // on applique les transitions au simulateur en affichant le résultat dans l'interface graphique
//    for(unsigned int step = 0; step < dimX; ++step) {
//        // on applique la transition
//        sim.next();
//        // on récupère le dernier état
//        const Etat& etat = sim.dernier();
//        // on l'affiche
//        for(unsigned int colonne = 0; colonne < dimX; ++colonne) {
//            if (dynamic_cast<const Etat1D&>(etat).getCellule(colonne) == true) {
//                etats->item(step, colonne)->setText("_");
//                etats->item(step, colonne)->setBackgroundColor("black");
//                etats->item(step, colonne)->setTextColor("black");
//            } else {
//                etats->item(step, colonne)->setText("");
//                etats->item(step, colonne)->setBackgroundColor("white");
//                etats->item(step, colonne)->setTextColor("white");
//            }
//        }
//        //Sleep(1000);
//    }
}

void AutoCell::addGenerator(const EtatGenerator* g){
    const EtatGenerator** newTab = new const EtatGenerator*[nbGenerators+1];
    for (unsigned int i = 0; i < nbGenerators; i++){
        newTab[i] = generators[i];
    }
    newTab[nbGenerators] = g;
    generateurs->addItem(g->getName());
    nbGenerators += 1;
    const EtatGenerator** oldTab = generators;
    generators = newTab;
    delete[] oldTab;
}

AutoCell1D::AutoCell1D(unsigned int e, unsigned int dim, unsigned int l, unsigned int eg) : AutoCell(dim, l, e, eg), r(0) {
    initial = new Etat1D(0,dimX);
    /*num = new QSpinBox(this);
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
//    couche = new QVBoxLayout;
    specifique->addLayout(numeroc);
    unsigned int taille = 25; //pixels*/
    depart = new QTableWidget(1, dimX, this);                  //1 ligne, 'dimX' colonnes
    depart->setFixedSize(dimX*TAILLE_CELLULE, TAILLE_CELLULE); // largeur = nombre_cellules*taille_cellule, hauteur = taille_cellule
    depart->horizontalHeader()->setVisible(false);                  // masque le header horizontal
    depart->verticalHeader()->setVisible(false);                    // masque le header vertical
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     // désactive la scroll barre
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // idem
    // création des items du QTableWidget, initialisés à "" avec un fond blanc
    depart->setRowHeight(0,TAILLE_CELLULE);
    for(unsigned int counter = 0; counter < dimX; ++counter) {
        depart->setColumnWidth(counter, TAILLE_CELLULE);
        depart->setItem(0, counter, new QTableWidgetItem(""));
        depart->item(0, counter)->setBackgroundColor("white");
        depart->item(0, counter)->setTextColor("white");
    }
    connect(depart, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(cellActivation(QModelIndex)));
    specifique->addWidget(depart);
    // Question 3
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*page1= new QWidget;
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
    setLayout(main);*/
    connect(generer,SIGNAL(clicked()),this,SLOT(genererEtat()));
}

void AutoCell1D::actualize(const Etat* e){
    unsigned int currentColor;
    if (r < dimY){
        for (unsigned int i = 0; i < dimX; i++){
            currentColor = (dynamic_cast<const Etat1D*>(e))->getCellule(i);
            etats->item(r,i)->setBackground(QColor(couleurs[currentColor]));
        }
        r += 1;
    }
    if (r == dimY) r = 0;
}

void AutoCell1D::setInitial(const Etat* e){
    if (e->getX() != dimX)
        throw EtatException("wrong size");
    const Etat1D* pt =dynamic_cast<const Etat1D*>(e);
    if (pt == nullptr)
        throw EtatException("wrong type");
    for (unsigned int i = 0; i < dimX; i++){if (pt->getCellule(i)>=etatsPossibles) throw EtatException("Color(s) out of range"); }
    for (unsigned int i = 0; i < dimX; i++){
        depart->item(0,i)->setBackground(QColor(couleurs[pt->getCellule(i)]));
        dynamic_cast<Etat1D*>(initial)->setCellule(i,pt->getCellule(i));
    }
    *initial = *pt;
}

void AutoCell1D::addGenerator(const EtatGenerator* g){
    const EtatGenerator1D* pt= dynamic_cast<const EtatGenerator1D*>(g);
    if (pt == nullptr)
        throw EtatException("wrong EtatGenerator type");
    AutoCell::addGenerator(g);
}

void AutoCell1D::cellActivation(const QModelIndex& index) {
    /*if (depart->item(0, index.column())->text() == "") {
        depart->item(0, index.column())->setText("_");
        depart->item(0, index.column())->setBackgroundColor("black");
        depart->item(0, index.column())->setTextColor("black");
    } else {
        depart->item(0, index.column())->setText("");
        depart->item(0, index.column())->setBackgroundColor("white");
        depart->item(0, index.column())->setTextColor("white");
    }*/
    unsigned int prev = (dynamic_cast<Etat1D*>(initial))->getCellule(index.column());
    if (prev == etatsPossibles-1){
        depart->item(0, index.column())->setBackground(QColor(couleurs[0]));
        (dynamic_cast<Etat1D*>(initial))->setCellule(index.column(),0);
    }
    else {
        depart->item(0, index.column())->setBackground(QColor(couleurs[prev+1]));
        (dynamic_cast<Etat1D*>(initial))->setCellule(index.column(),prev+1);
    }
}

void AutoCell1D::genererEtat(){
    unsigned int index = generateurs->currentIndex();
    const Etat1D* pt =(dynamic_cast<const EtatGenerator1D*>(generators[index]))->generateEtat(dimX, etatsPossiblesGeneration);
    setInitial(pt);
    delete pt;
}

AutoCell2D::AutoCell2D(unsigned int lines, unsigned int columns, unsigned int e, unsigned int eg) : AutoCell(columns, lines, e, eg){
    initial = new Etat2D(0, dimX, dimY);
    connect(etats, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(cellActivation(QModelIndex)));
    connect(generer,SIGNAL(clicked()),this,SLOT(genererEtat()));
}

void AutoCell2D::actualize(const Etat* e){
    unsigned int currentColor;
    for (unsigned int i = 0; i < dimX; i++){
        for (unsigned int j = 0; j < dimY; j++){
            currentColor = (dynamic_cast<const Etat2D*>(e))->getCellule(i,j);
            etats->item(j,i)->setBackground(QColor(couleurs[currentColor]));
        }
    }
}

void AutoCell2D::setInitial(const Etat* e){
    const Etat2D* pt =dynamic_cast<const Etat2D*>(e);
    if (pt == nullptr)
        throw EtatException("wrong type");
    if (pt->getX() != dimX || pt->getY() != dimY)
        throw EtatException("wrong size");
    for (unsigned int i = 0; i < dimX; i++){
        for (unsigned int j = 0; j < dimY; j++){
            if (pt->getCellule(i,j)>=etatsPossibles)
                throw EtatException("Color(s) out of range");
        }
    }
    for (unsigned int i = 0; i < dimX; i++){
        for (unsigned int j = 0; j < dimY; j++){
        etats->item(j,i)->setBackground(QColor(couleurs[pt->getCellule(i,j)]));
        dynamic_cast<Etat2D*>(initial)->setCellule(i,j,pt->getCellule(i,j));
        }
    }
    *initial = *pt;
}

void AutoCell2D::addGenerator(const EtatGenerator* g){
    const EtatGenerator2D* pt= dynamic_cast<const EtatGenerator2D*>(g);
    if (pt == nullptr)
        throw EtatException("wrong EtatGenerator type");
    AutoCell::addGenerator(g);
}

void AutoCell2D::synchDimension(unsigned int X, unsigned int Y){
    dimX = X;
    dimY = Y;
    Etat2D* temp = dynamic_cast<Etat2D*>(initial);
    initial = new Etat2D(0,dimX,dimY);
    (dynamic_cast<Etat2D*>(initial))->copyEtat(temp);
    delete temp;
    delete etats;
    etats = new QTableWidget(dimY, dimX, this);
    setFixedWidth(dimX*TAILLE_CELLULE+20);
    etats->setFixedSize(dimX*TAILLE_CELLULE, dimY*TAILLE_CELLULE);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for (unsigned int i = 0; i < dimX; i++){
        etats->setColumnWidth(i, TAILLE_CELLULE);
    }
    for(unsigned int line = 0; line < dimY; ++line) {
        etats->setRowHeight(line, TAILLE_CELLULE);
        for(unsigned int column = 0; column < dimX; ++column) {
            etats->setItem(line, column, new QTableWidgetItem(""));
            etats->item(line, column)->setBackgroundColor("white");
            etats->item(line, column)->setTextColor("white");
        }
    }
    grille->addWidget(etats);
    actualize(initial);
}

void AutoCell2D::cellActivation(const QModelIndex& index){
    unsigned int prev = (dynamic_cast<Etat2D*>(initial))->getCellule(index.column(),index.row());
    if (prev == etatsPossibles-1){
        etats->item(index.column(), index.row())->setBackground(QColor(couleurs[0]));
        (dynamic_cast<Etat2D*>(initial))->setCellule(index.column(),index.row(),0);
    }
    else {
        etats->item(index.column(), index.row())->setBackground(QColor(couleurs[prev+1]));
        (dynamic_cast<Etat2D*>(initial))->setCellule(index.column(),index.row(),prev+1);
    }
    emit reset();
}

void AutoCell2D::genererEtat(){
    unsigned int index = generateurs->currentIndex();
    Etat2D* pt =(dynamic_cast<const EtatGenerator2D*>(generators[index]))->generateEtat(dimX, dimY, etatsPossiblesGeneration);
    setInitial(pt);
    delete pt;
    emit reset();
}
