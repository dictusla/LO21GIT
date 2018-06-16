#include <iostream>
#include <string>
#include "Automates.h"

Cellules::Cellules(unsigned int e) : etatsPossibles(e), couleur(0){
    voisins = new QTableWidget(2,3);
    lay = new QVBoxLayout;
    voisins->setRowHeight(0,HEIGHT_CELLULE);
    voisins->setRowHeight(1,HEIGHT_CELLULE);
    voisins->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    voisins->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    voisins->horizontalHeader()->setVisible(false);
    voisins->verticalHeader()->setVisible(false);
    voisins->setSelectionMode(QAbstractItemView::NoSelection);
    voisins->setFrameShape(QFrame::NoFrame);
    //voisins->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    //voisins->setMinimumSize(60,40);
    //voisins->setIconSize(QSize(20,20));
    for (unsigned int col = 0; col<3; col++){
        voisins->setColumnWidth(col,WIDTH_CELLULE);
        for (unsigned int line = 0; line<2; line++){
            voisins->setItem(line,col,new QTableWidgetItem);
        }
    }
    voisins->item(1,0)->setBackground(QColor("lightGray"));
    voisins->item(1,0)->setTextColor("lightGray");
    voisins->item(1,1)->setBackground(QColor(couleurs[couleur]));
    voisins->item(1,1)->setTextColor(QColor(couleurs[couleur]));
    voisins->item(1,2)->setBackground(QColor("lightGray"));
    voisins->item(1,2)->setTextColor("lightGray");
    voisins->setFixedSize(WIDTH_CELLULE*3,HEIGHT_CELLULE*2);
    //voisins->setFixedSize(WIDTH_MIN*3,HEIGHT_MIN*2);
    lay->addWidget(voisins);
    lay->setContentsMargins(0,0,0,0);
    setLayout(lay);

    connect(voisins,SIGNAL(cellClicked(int,int)),this,SLOT(synch(int, int)));
}

Cellules::Cellules(unsigned int i, unsigned int j, unsigned int k, unsigned int e) : Cellules(e){
    I = i;    J = j;    K = k;
    voisins->item(0,0)->setBackground(QColor(couleurs[I]));
    voisins->item(0,1)->setBackground(QColor(couleurs[J]));
    voisins->item(0,2)->setBackground(QColor(couleurs[K]));
    voisins->item(0,0)->setTextColor(QColor(couleurs[I]));
    voisins->item(0,1)->setTextColor(QColor(couleurs[J]));
    voisins->item(0,2)->setTextColor(QColor(couleurs[K]));

}

Cellules& Cellules::operator=(const Cellules& c){
    if (this != &c){
        etatsPossibles = c.etatsPossibles; I = c.I; J = c.J; K = c.K; couleur = c.couleur;
        voisins->item(0,0)->setBackground(QColor(couleurs[I]));
        voisins->item(0,1)->setBackground(QColor(couleurs[J]));
        voisins->item(0,2)->setBackground(QColor(couleurs[K]));
        voisins->item(1,1)->setBackground(QColor(couleurs[couleur]));
        voisins->item(0,0)->setTextColor(QColor(couleurs[I]));
        voisins->item(0,1)->setTextColor(QColor(couleurs[J]));
        voisins->item(0,2)->setTextColor(QColor(couleurs[K]));
        voisins->item(1,1)->setTextColor(QColor(couleurs[couleur]));
    }
    return *this;
}

void Cellules::synch(int row, int column){
    if (1==row && 1==column){
        if (couleur == (etatsPossibles-1)) couleur = 0;
        else couleur += 1;
        voisins->item(1,1)->setBackground(QColor(couleurs[couleur]));
        voisins->item(1,1)->setTextColor(QColor(couleurs[couleur]));
        emit changed(I,J,K);
    }
}

Automate::Automate() : nb(0), maxSize(MAX_BUFFER_SIZE){
    principal = new QHBoxLayout;
    configs =  new QVBoxLayout;
    commun = new QFormLayout;
    configuration = new QLabel("Configurations : ");
    dimension = new QLabel("Dimension");
    dimension2 = new QLabel(" - ");
    dim = new QSpinBox;
    dim2 = new QSpinBox;

    dim->setRange(DIMENSION_MIN,DIMENSION_MAX);
    dim2->setRange(DIMENSION_MIN,DIMENSION_MAX);
    dim->setFixedWidth(50);
    dim2->setFixedWidth(50);
    commun->addRow(configuration);
    commun->addRow(dimension,dim);
    commun->addRow(dimension2,dim2);
    configs->addLayout(commun);
    principal->addLayout(configs);
    setLayout(principal);

    etatInitial = nullptr;
    connect(dim,SIGNAL(valueChanged(int)),this,SLOT(synchDimension(int)));
    connect(dim2,SIGNAL(valueChanged(int)),this,SLOT(synchDimension(int)));
    grille = nullptr;
}

const Etat* Automate::getNext(){
    const Etat* pt;
    if (nb > 0) pt = buffer.front();
    else pt = etatInitial;
    if (nb == maxSize) this->buffer.pop_back();
    else nb +=1;
    //Etat* nouveau = getCopy(etatInitial);
    Etat* nouveau = appliquerTransition(pt);
    buffer.push_front(nouveau);
    return buffer.front();
}

const Etat* Automate::getPrev(){
    if (nb == 0) throw AutomateException("No previous element");
    delete buffer.front();
    buffer.pop_front();
    nb -= 1;
    if (nb == 0) return etatInitial;
    else return buffer.front();
}

const Etat* Automate::getLast(){
    if (nb > 0) return buffer.front();
    else return etatInitial;
}

void Automate::clearBuffer(){
    while (!buffer.empty()){
        delete buffer.back();
        buffer.pop_back();
    }
    nb = 0;
}

/*void Automate::setEtatInitial(const Etat* e){
    clearBuffer();
    if (etatInitial != nullptr){
        delete etatInitial;
    }
    etatInitial = getCopy(e);
}*/

Automate1D::Automate1D(unsigned int e): Automate(), etatsPossibles(e) {
    if (e > NB_COULEURS) throw AutomateException("Nombre de couleurs insuffisant");
    //lignes = new QSpinBox;
    dimension2->setText("Nº etats affichés:");
    dim2->setRange(1,DIMENSION_MAX);

    regles = new unsigned int**[etatsPossibles];
    inRegles = new Cellules**[etatsPossibles];
    QHBoxLayout* lay = new QHBoxLayout;
    QVBoxLayout* h = new QVBoxLayout;
    h->setContentsMargins(2,3,2,3);
    unsigned int cont = 0;
    for (unsigned int i = 0; i < etatsPossibles; i++){
        regles[i] = new unsigned int*[etatsPossibles];
        inRegles[i] = new Cellules*[etatsPossibles];
        for(unsigned int j =0; j < etatsPossibles; j++){
            regles[i][j] = new unsigned int[etatsPossibles];
            inRegles[i][j] = new Cellules[etatsPossibles];
            for(unsigned int k = 0; k < etatsPossibles; k++){
                regles[i][j][k] = 0;
                inRegles[i][j][k] = Cellules(i,j,k,etatsPossibles);
                connect(&inRegles[i][j][k],SIGNAL(changed(uint,uint,uint)),this,SLOT(synchRegles(uint,uint,uint)));
                if (cont == 12){
                    lay->addLayout(h);
                    h = new QVBoxLayout;
                    h->setContentsMargins(2,3,2,3);
                    cont = 0;
                }
                h->addWidget(&inRegles[i][j][k]);
                cont += 1;
            }
        }
    }
    lay->addLayout(h);
    lay->setContentsMargins(2,3,2,3);
    configs->addLayout(lay);
    //Cellules* cel = new Cellules(1,0,1,3);
    //configs->addWidget(&inRegles[1][0][1]);
    grille = new AutoCell1D(etatsPossibles, dim->value(),dim2->value(), etatsPossibles);
    setInitial();
    addEtatGenerators();
    grille->setFixedWidth(dim->value()*TAILLE_CELLULE + 20);
    principal->addWidget(grille);

    connect(grille,SIGNAL(simuler()),this,SLOT(simuler()));
}

Automate1D::~Automate1D(){
    //delete etatInitial;
    for (unsigned int i = 0; i < etatsPossibles; i++){
        for (unsigned int j = 0; j < etatsPossibles; j++){
                delete[] regles[i][j];
        }
        delete[] regles[i];
    }
    delete[] regles;
    RandGenerator1D::deleteInstance();
}

void Automate1D::addEtatGenerators(){
    RandGenerator1D* pt= RandGenerator1D::getInstance();
    grille->addGenerator(pt);
}

Etat* Automate1D::appliquerTransition(const Etat* dep) const {
    Etat1D* dest = new Etat1D(0,dep->getX());
    //if (dep.getX() != dest.getX()) dest = dep;
    unsigned int a, b, c;
    for (unsigned int i = 0; i < dep->getX(); i++) {
        if (i == 0) a = dynamic_cast<const Etat1D*>(dep)->getCellule(dep->getX()-1);
        else a = dynamic_cast<const Etat1D*>(dep)->getCellule(i - 1);
        b = dynamic_cast<const Etat1D*>(dep)->getCellule(i);
        if (i == (dep->getX()-1)) c = dynamic_cast<const Etat1D*>(dep)->getCellule(0);
        else c = dynamic_cast<const Etat1D*>(dep)->getCellule(i + 1);
        dest->setCellule(i, regles[a][b][c]);
        /*short int conf=0;
		if (i > 0) conf+=dynamic_cast<const Etat1D&>(dep).getCellule(i - 1) * 4;
		conf+=dynamic_cast<const Etat1D&>(dep).getCellule(i)*2;
		if (i < dep.getX()-1) conf+=dynamic_cast<const Etat1D&>(dep).getCellule(i + 1);
        dynamic_cast<Etat1D&>(dest).setCellule(i, numeroBit[7-conf]-'0');*/    
    }
    return dest;
}

/*
void Automate1D::appliquerTransition(const Etat& dep, Etat& dest) const
{
	const Etat1D& d=dynamic_cast<const Etat1D&>(dep);
   Etat1D& a=dynamic_cast<Etat1D&>(dest);
	if (d.getX() != a.getX())
      a = d;
	for (int i = 0; i < dep.getX(); i++) {
		short int conf=0;
		if (i > 0)
         conf+=d.getCellule(i - 1) * 4;
		conf+=d.getCellule(i)*2;
		if (i < dep.getX()-1)
         conf+=d.getCellule(i + 1);
		a.setCellule(i, numeroBit[7-conf]-'0');
*/

void Automate1D::synchDimension(int){
    clearBuffer();
    Etat1D* nouveau = new Etat1D(0,dim->value());
    const Etat1D* pt = dynamic_cast<const Etat1D*>(etatInitial);
    nouveau->copyEtat(pt);
    delete grille;
    grille = new AutoCell1D(etatsPossibles, dim->value(), dim2->value(), etatsPossibles);
    grille->setInitial(nouveau);
    setInitial();
    addEtatGenerators();
    grille->setFixedWidth(dim->value()*TAILLE_CELLULE + 20);
    principal->addWidget(grille);
    connect(grille,SIGNAL(simuler()),this,SLOT(simuler()));
    simuler();
}

void Automate1D::synchRegles(unsigned int i, unsigned int j, unsigned int k){
    if (regles[i][j][k]==(etatsPossibles-1)) regles[i][j][k] = 0;
    else regles[i][j][k] += 1;
}

unsigned int Automate1D::getRegles(unsigned int i,unsigned int j,unsigned int k){
    return regles[i][j][k];
}

void Automate1D::setRegles(unsigned int i, unsigned int j, unsigned int k,unsigned int v) {
    regles[i][j][k]=v;
}

unsigned int Automate1D::getEtatsPossibles(){
    return etatsPossibles;
}

void Automate1D::simuler(){
    clearBuffer();
    for (int i = 0; i < dim2->value(); i++){
        const Etat* pt = getNext();
        grille->actualize(pt);
    }
}

Automate2D::Automate2D(Automate2D &a) : Automate2D(a.getMinToNotDie(),a.getMaxToNotDie())
{
}

Automate2D::Automate2D (unsigned int minNd, unsigned int maxNd) : minToNotDie (minNd), maxToNotDie (maxNd) {
    if(minNd>maxNd) throw AutomateException("Minimum value superior than maximum value");
    dimension2->setText("Lignes : ");
    dimension->setText("Colonnes : ");
    grille = new AutoCell2D(DIMENSION_MIN,DIMENSION_MIN,2);
    setInitial();
    addEtatGenerators();
    principal->addWidget(grille);
    connect(grille,SIGNAL(simuler()),this,SLOT(simuler()));
    connect(grille,SIGNAL(reset()),this,SLOT(reset()));
}

Automate2D::~Automate2D(){
    RandGenerator2D::deleteInstance();
}

void Automate2D::addEtatGenerators(){
    RandGenerator2D* pt= RandGenerator2D::getInstance();
    grille->addGenerator(pt);
}

Etat* Automate2D::appliquerTransition (const Etat* dep) const {
    const Etat2D* pt = dynamic_cast<const Etat2D*>(dep);
    Etat2D* dest = new Etat2D(0, dep->getX(), pt->getY());
   //if (dep.getX() != dest.getX() || dynamic_cast<const Etat2D&>(dep).getY()!=dynamic_cast<Etat2D&>(dest).getY()) dest = dep;
   //std::cout<<"dest dep ok, x= "<<dep.getX()<<" y= "<<dep.getY()<<std::endl;
    unsigned int left, up, right, down;
    for (unsigned int i = 0; i < dep->getX(); i++)
    {
        for(unsigned int j = 0; j<pt->getY(); j++)
        {
            unsigned int nbVvivant=0;
            //std::cout<<"avant boucles de get cellule ok"<<std::endl;
            if (i == 0) left = pt->getX() - 1;
            else left = i - 1;
            if (j == 0) up = pt->getY() - 1;
            else up = j - 1;
            if (i == (pt->getX() - 1)) right = 0;
            else right = i + 1;
            if (j == (pt->getY() - 1)) down = 0;
            else down = j + 1;
            /*
            for(unsigned int x=i-1; x<=i+1; ++x)
            {
                for(unsigned int y=j-1; y<=j+1; ++y)
                {
                    //std::cout<<"x="<<x<<" y="<<y<<std::endl;
                    //std::cout<<"appel get cellule avec i="<<i<<"et j="<<j<<std::endl;
                    if ((x!=i || y!=j) && dynamic_cast<const Etat2D*>(dep)->getCellule(x,y) )
                    {
                        nbVvivant++;}
                  }
            }*/
            nbVvivant = pt->getCellule(left,up) + pt->getCellule(i,up) + pt->getCellule(right,up);
            nbVvivant += pt->getCellule(left,j) + pt->getCellule(right,j);
            nbVvivant += pt->getCellule(left,down) + pt->getCellule(i,down) + pt->getCellule(right,down);
            if (nbVvivant<minToNotDie || nbVvivant>maxToNotDie)
            { //std::cout<<"appel set cellule avec i="<<i<<"et j="<<j<<std::endl;
                dest->setCellule(i, j, 0);}
            else
            { //std::cout<<"appel set cellule avec i="<<i<<"et j="<<j<<std::endl;
                dest->setCellule(i, j, 1);}
        }
    }
    return dest;
}


/*
void Automate2D::appliquerTransition (const Etat& dep, Etat& dest) const
{
   const Etat2D& d=dynamic_cast<const Etat2D&>(dep);
   Etat2D& a=dynamic_cast<Etat2D&>(dest);

   if (dep.getX() != dest.getX() || d.getY()!= a.getY())
      a=d;

   for (int i = 0; i < dep.getX(); i++)
   {
      for(int j=0; j < d.getY(); j++)
      {
         unsigned int nbVvivant=0;
         for(int x=i-1; x<=i+1; ++x)
         {
            for(unsigned int y=j-1; y<=j+1; ++y)
            {
               if ((x!=i || y!=j) && d.getCellule(x,y) )
                  nbVvivant++;
            }
         }
         if (nbVvivant<minToNotDie || nbVvivant>maxToNotDie)
            {
               a.setCellule(i,j, false);}
         else
            {
               a.setCellule(i, j, true);}
      }
	}
}*/

void Automate2D::synchDimension(int){
    clearBuffer();
    dynamic_cast<AutoCell2D*>(grille)->synchDimension(dim->value(),dim2->value());
    setInitial();
}

void Automate2D::simuler(){
    const Etat* pt = getNext();
    grille->setInitial(pt);
    grille->actualize(pt);
}

void Automate2D::reset(){
    clearBuffer();
    setInitial();
    grille->actualize(etatInitial);
}

AutomateFdF::AutomateFdF(){
    dimension2->setText("Lignes : ");
    dimension->setText("Colonnes : ");
    grille = new AutoCell2D(DIMENSION_MIN,DIMENSION_MIN,4);
    setInitial();
    addEtatGenerators();
    principal->addWidget(grille);
    connect(grille,SIGNAL(simuler()),this,SLOT(simuler()));
    connect(grille,SIGNAL(reset()),this,SLOT(reset()));
}

void AutomateFdF::addEtatGenerators(){
    RandGenerator2D* pt= RandGenerator2D::getInstance();
    grille->addGenerator(pt);
}

void AutomateFdF::synchDimension(int){
    clearBuffer();
    dynamic_cast<AutoCell2D*>(grille)->synchDimension(dim->value(),dim2->value());
    setInitial();
}

void AutomateFdF::simuler(){
    const Etat* pt = getNext();
    grille->setInitial(pt);
    grille->actualize(pt);
}

void AutomateFdF::reset(){
    clearBuffer();
    setInitial();
    grille->actualize(etatInitial);
}

Etat* AutomateFdF::appliquerTransition (const Etat* dep) const
{
   const Etat2D* pt=dynamic_cast<const Etat2D*>(dep);
   Etat2D* dest = new Etat2D(0, pt->getX(), pt->getY());
   unsigned int left, up, right, down;

   for (unsigned int i = 0; i < pt->getX(); i++)
   {
      for(unsigned int j=0; j < pt->getY(); j++)
      {
         if (pt->getCellule(i,j)==0)
            dest->setCellule(i,j,0);
         else if (pt->getCellule(i,j)==3)
            dest->setCellule(i,j,2);
         else if (pt->getCellule(i,j)==2)
            dest->setCellule(i,j,2);
         else
         {
            if (i == 0) left = pt->getX() - 1;
            else left = i - 1;
            if (j == 0) up = pt->getY() - 1;
            else up = j - 1;
            if (i == (pt->getX() - 1)) right = 0;
            else right = i + 1;
            if (j == (pt->getY() - 1)) down = 0;
            else down = j + 1;
            if ( pt->getCellule(i,up)==3 || pt->getCellule(left,j)==3 || pt->getCellule(right,j)==3 || pt->getCellule(i,down)==3 )
               dest->setCellule(i,j,3);
            else
               dest->setCellule(i,j,1);
         }
      }
    }
   return dest;
}

/*
std::ostream& operator<<(std::ostream& f, const Automate1D& A) {
    f << A.getNumero() << " : " << A.getNumeroBit() << "\n";
    return f;
}
*/

AutomateManager::AutomateManager()
{
   for (unsigned int i=0; i<256; i++)
      automates[i]=nullptr;
}

AutomateManager::~AutomateManager()
{
   for (unsigned int i=0; i<256; i++)
      delete automates[i];
}

AutomateManager* AutomateManager::instance=nullptr;

AutomateManager& AutomateManager::getAutomateManager()
{
   if (!instance)
      instance =new AutomateManager;
   return *instance;
}

void AutomateManager::freeAutomateManager()
{
   delete instance;
   instance=nullptr;
}

const Automate1D& AutomateManager::getAutomate(unsigned short int num)
{
   if(!automates[num])
      automates[num]=new Automate1D(num);
   return *automates[num];
}

const Automate1D& AutomateManager::getAutomate(std::string& num)
{
   return getAutomate(NumBitToNum(num));
}

short unsigned int NumBitToNum(const std::string& num) {
    if (num.size() != 8) throw AutomateException("Numero d'automate indefini");
    int puissance = 1;
    short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
        puissance *= 2;
    }
    return numero;
}

std::string NumToNumBit(short unsigned int num) {
    std::string numeroBit;
    if (num > 256) throw AutomateException("Numero d'automate indefini");
    unsigned short int p = 128;
    int i = 7;
    while (i >= 0) {
        if (num >= p) {
            numeroBit.push_back('1');
            num -= p;
        }
        else { numeroBit.push_back('0'); }
        i--;
        p = p / 2;
    }
    return numeroBit;
}
