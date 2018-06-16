#include "savemanager.h"


SaveManager* SaveManager::instance = nullptr;

SaveManager& SaveManager::getInstance(){
    if(SaveManager::instance==nullptr){
        SaveManager::instance = new SaveManager();
    }
    return *(SaveManager::instance);
}

void SaveManager::endInstance(){
    if(nullptr!=SaveManager::instance){
        delete SaveManager::instance;
        SaveManager::instance=nullptr;
    }
}

void SaveManager::writeEtat1D(Etat1D& s,QString path,QString filename){
    QDomDocument document;
    document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    QDomElement root = document.createElement("Etat1D");
    document.appendChild(root);
    QDomElement size = document.createElement("Size");
    size.setAttribute("nbcolonnes",s.getX());
    root.appendChild(size);
    QDomElement Cells = document.createElement("Cells");
    root.appendChild(Cells);

    for(unsigned int i=0; i<s.getX(); ++i) {
            QDomElement Cell = document.createElement("Cell");
            Cell.setAttribute("colonne",i);
            Cell.setAttribute("valeur",s.getCellule(i));
            Cells.appendChild(Cell);
    }

    writeDocumentInFile(path,filename,document);
}

void SaveManager::writeEtat2D(Etat2D& s,QString path,QString filename){
    QDomDocument document;
    document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    QDomElement root = document.createElement("Etat2D");
    document.appendChild(root);
    QDomElement size = document.createElement("Size");
    size.setAttribute("nbcolonnes",s.getX());
    size.setAttribute("nblignes",s.getY());
    root.appendChild(size);
    QDomElement Cells = document.createElement("Cells");
    root.appendChild(Cells);

    for(unsigned int i=0; i<s.getX(); ++i) {
        for(unsigned int j=0; j<s.getY();++j) {
            QDomElement Cell = document.createElement("Cell");
            Cell.setAttribute("colonne",i);
            Cell.setAttribute("ligne",j);
            Cell.setAttribute("valeur",s.getCellule(i,j));
            Cells.appendChild(Cell);
        }
    }
}

    void SaveManager::writeEtatFdF(EtatFdF& s,QString path,QString filename){
        QDomDocument document;
        document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
        QDomElement root = document.createElement("EtatFdF");
        document.appendChild(root);
        QDomElement size = document.createElement("Size");
        size.setAttribute("nbcolonnes",s.getX());
        size.setAttribute("nblignes",s.getY());
        root.appendChild(size);
        QDomElement Cells = document.createElement("Cells");
        root.appendChild(Cells);

        for(unsigned int i=0; i<s.getX(); ++i) {
            for(unsigned int j=0; j<s.getY();++j) {
                QDomElement Cell = document.createElement("Cell");
                Cell.setAttribute("colonne",i);
                Cell.setAttribute("ligne",j);
                Cell.setAttribute("valeur",s.getCellule(i,j));
                Cells.appendChild(Cell);
            }
        }

    writeDocumentInFile(path,filename,document);
}

Etat1D SaveManager::readEtat1D(QString path,QString filename){
    QDomDocument document;
    openFileInDocument(path,filename,document);

    QDomElement root = document.firstChildElement();
    QDomElement size  = root.firstChildElement();
    unsigned int ln = size.attribute("nbcolonnes","0").toUInt();

    Etat1D res(1,ln);

    QDomElement Cells = size.nextSiblingElement();
    QDomNodeList cellules = Cells.elementsByTagName("Cell");

    for(int i = 0; i < cellules.count(); i++){
        QDomNode cellule = cellules.at(i);
        if(cellule.isElement()){
            QDomElement element = cellule.toElement();
            unsigned int cln = element.attribute("colonne","-1").toUInt();
            unsigned int v = element.attribute("valeur","-1").toUInt();
            try{
                res.setCellule(cln,v);
            }catch (EtatException e){

            }

        }
    }

    return res;

}

Etat2D SaveManager::readEtat2D(QString path,QString filename){
    QDomDocument document;
    openFileInDocument(path,filename,document);

    QDomElement root = document.firstChildElement();
    QDomElement size  = root.firstChildElement();
    unsigned int cl = size.attribute("nbcolonnes","0").toUInt();
    unsigned int ln = size.attribute("nblignes","0").toUInt();

    Etat2D res(2,cl,ln);

    QDomElement Cells = size.nextSiblingElement();
    QDomNodeList cellules = Cells.elementsByTagName("Cell");

    for(int i = 0; i < cellules.count(); i++){
        QDomNode cellule = cellules.at(i);
        if(cellule.isElement()){
            QDomElement element = cellule.toElement();
            unsigned int ccl = element.attribute("colonne","-1").toUInt();
            unsigned int cln = element.attribute("ligne","-1").toUInt();
            unsigned int v = element.attribute("valeur","-1").toUInt();
            try{
                res.setCellule(ccl,cln,v);
            }catch (EtatException e){

            }

        }
    }

    return res;

}

EtatFdF SaveManager::readEtatFdF(QString path,QString filename){
    QDomDocument document;
    openFileInDocument(path,filename,document);

    QDomElement root = document.firstChildElement();
    QDomElement size  = root.firstChildElement();
    unsigned int cl = size.attribute("nbcolonnes","0").toUInt();
    unsigned int ln = size.attribute("nblignes","0").toUInt();

    EtatFdF res(2,cl,ln);

    QDomElement Cells = size.nextSiblingElement();
    QDomNodeList cellules = Cells.elementsByTagName("Cell");

    for(int i = 0; i < cellules.count(); i++){
        QDomNode cellule = cellules.at(i);
        if(cellule.isElement()){
            QDomElement element = cellule.toElement();
            unsigned int ccl = element.attribute("colonne","-1").toUInt();
            unsigned int cln = element.attribute("ligne","-1").toUInt();
            unsigned int v = element.attribute("valeur","-1").toUInt();
            try{
                res.setCellule(ccl,cln,v);
            }catch (EtatException e){

            }

        }
    }

    return res;
}


void SaveManager::writeAutomate1D(Automate1D& e,QString path,QString filename){
    QDomDocument document;
    document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");

    QDomElement root = document.createElement("Automate1D");

    document.appendChild(root);
    QDomElement etats = document.createElement("etatspossibles");
    etats.setAttribute("nbEtatsPossibles",e.getEtatsPossibles());
    root.appendChild(etats);

    for(int i=0; i<e.getEtatsPossibles();++i ) {

       for(int j=0; i<e.getEtatsPossibles();++i ) {
           for(int k=0; i<e.getEtatsPossibles();++i ) {
        QDomElement ruleNb = document.createElement("Rule");
    ruleNb.setAttribute("value",e.getRegles(i,j,k));
    root.appendChild(ruleNb);
            }
       }
    }

    writeDocumentInFile(path,filename,document);

}

Automate1D SaveManager::readAutomate1D(QString path,QString filename){
    QDomDocument document;
    openFileInDocument(path,filename,document);

    QDomElement root = document.firstChildElement();
    QDomElement etats  = root.firstChildElement();
    unsigned int nbEtatsPossibles = etats.attribute("nbEtatsPossibles","0").toUInt();
    Automate1D res(nbEtatsPossibles);

    for(int i=0; i<nbEtatsPossibles;++i ) {

       for(int j=0; i<nbEtatsPossibles;++i ) {
           for(int k=0; i<nbEtatsPossibles;++i )
           {

        QDomElement ruleNb = root.nextSiblingElement("Rule");
    unsigned int v=ruleNb.attribute("value","-1").toUInt();
    res.setRegles(i,j,k,v);
            }
       }
    }

    return res;
}

void SaveManager::writeAutomate2D(Automate2D& g,QString path,QString filename){
    QDomDocument document;
    document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");

    QDomElement root = document.createElement("Automate2D");

    document.appendChild(root);

    QDomElement voisins = document.createElement("VoisinageDeSurvie");
    voisins.setAttribute("min",g.getMinToNotDie());
    voisins.setAttribute("max",g.getMaxToNotDie());
    root.appendChild(voisins);

    writeDocumentInFile(path,filename,document);

}
/*
void SaveManager::writeAutomateFdF(AutomateFdF& g,QString path,QString filename){
    QDomDocument document;
    document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");

    QDomElement root = document.createElement("AutomateFdF");

    document.appendChild(root);

    QDomElement voisins = document.createElement("VoisinageDeSurvie");
    voisins.setAttribute("min",g.getMinToNotDie());
    voisins.setAttribute("max",g.getMaxToNotDie());
    root.appendChild(voisins);

    writeDocumentInFile(path,filename,document);

}
*/
Automate2D SaveManager::readAutomate2D(QString path,QString filename){
    QDomDocument document;
    openFileInDocument(path,filename,document);

    QDomElement root = document.firstChildElement();
    QDomElement VoisinageDeSurvie  = root.firstChildElement();
    unsigned int minVoisinage = VoisinageDeSurvie.attribute("min","-1").toUInt();
    unsigned int maxVoisinage = VoisinageDeSurvie.attribute("max","-1").toUInt();
    Automate2D res(minVoisinage,maxVoisinage);
    return res;
}

void SaveManager::writeDocumentInFile(QString path,QString filename,QDomDocument& document){
    QString fullName = path+"/"+filename;
    QFile file(fullName);
    if(file.exists()){
        file.remove();
    }
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        throw SaveManagerException("Impossible d'ouvrir le fichier en écriture");
    }
    else{
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
    }
}

void SaveManager::openFileInDocument(QString path,QString filename,QDomDocument& document){
    QString fullName = path+"/"+filename;;

    QFile file(fullName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw SaveManagerException("Impossible d'ouvrir le fichier");
    }
    else {
        if(!document.setContent(&file)){
            throw SaveManagerException("Erreur");
        }
        file.close();
    }
}
