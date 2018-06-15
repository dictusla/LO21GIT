#include <iostream>
#include <QApplication>
#include "configurateur.h"
#include "etats.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Interface* fenetre = Interface::getInterface();
    Config1D* c2 = new Config1D;
    Config2D* c3 = new Config2D;
    ConfigFdF* c4 = new ConfigFdF;
    fenetre->addAutoType(c2);
    fenetre->addAutoType(c3);
    fenetre->addAutoType(c4);
    fenetre->show();
    return app.exec();
}
