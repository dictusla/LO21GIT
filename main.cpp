#include <iostream>
#include <QApplication>
#include "configurateur.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Interface* fenetre = new Interface();
    config1D* c2 = new config1D;
    config2D* c3 = new config2D;
    fenetre->addAutoType(c2);
    fenetre->addAutoType(c3);
    fenetre->show();
    return app.exec();
}
