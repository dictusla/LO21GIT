#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QtXml>
#include <QString>
#include "etats.h"
#include "Automates.h"

class SaveManagerException {
    public:

        SaveManagerException (const std::string& message) : info(message) {}

        std::string getInfo () const { return info; }

    private:
        std::string info;
};

class SaveManager
{
private:

    SaveManager(){}

    ~SaveManager(){}

    SaveManager(const SaveManager& sm){}

    SaveManager& operator=(const SaveManager& sm){}

    static SaveManager* instance;

    void openFileInDocument(QString path,QString filename,QDomDocument& document);

    void writeDocumentInFile(QString path,QString filename,QDomDocument& document);

public:

    static SaveManager& getInstance();

    static void endInstance();

    void writeEtat1D(Etat1D& s,QString path,QString filename);

    void writeEtat2D(Etat2D& s,QString path,QString filename);

    void writeEtatFdF(EtatFdF& s,QString path,QString filename);

    Etat1D readEtat1D(QString path,QString filename);

    Etat2D readEtat2D(QString path,QString filename);

    EtatFdF readEtatFdF(QString path,QString filename);

    void writeAutomate1D(Automate1D& e,QString path,QString filename);

    void writeAutomate2D(Automate2D& g,QString path,QString filename);

    void writeAutomateFdF(AutomateFdF& g,QString path,QString filename);

    Automate1D readAutomate1D(QString path,QString filename);

    Automate2D readAutomate2D(QString path,QString filename);

    AutomateFdF readAutomateFdF(QString path,QString filename);

};

#endif // SAVEMANAGER_H
