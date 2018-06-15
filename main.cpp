#include <iostream>
#include <QApplication>
#include "configurateur.h"
#include "etats.h"

using namespace std;

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);
    try{
        Interface* fenetre = Interface::getInterface();
        Config1D* c2 = new Config1D;
        Config2D* c3 = new Config2D;
        fenetre->addAutoType(c2);
        fenetre->addAutoType(c3);
        fenetre->show();
        //QWidget* configs = new QWidget;
        //Cellules*** inRegles = new Cellules**[2];
        //QHBoxLayout* lay = new QHBoxLayout;
        //QVBoxLayout* h = new QVBoxLayout;
        //h->setContentsMargins(5,5,5,5);
        //unsigned int nb = 4;
        //unsigned int cont = 0;
        //for (unsigned int i = 0; i < nb; i++){
        //    inRegles[i] = new Cellules*[nb];
        //    for(unsigned int j =0; j < nb; j++){
        //        inRegles[i][j] = new Cellules[nb];
        //        for(unsigned int k = 0; k < nb; k++){
        //            inRegles[i][j][k] = Cellules(i,j,k,nb);
        //            if (cont == 12){
        //                lay->addLayout(h);
        //                h = new QVBoxLayout;
        //                h->setContentsMargins(5,5,5,5);
        //                cont = 0;
        //            }
        //            h->addWidget(&inRegles[i][j][k]);
        //            cont += 1;
        //        }
        //    }
        //}
        //h->addWidget(new QWidget);
        //lay->addLayout(h);
        //lay->setContentsMargins(5,5,5,5);
        //configs->setLayout(lay);
        //configs->show();
        //Cellules* cel = new Cellules(3);
        //*cel = Cellules(1,0,2,3);
        //cel->show();
    }
    catch (EtatException e){
        std::cout<< e.getInfo() << std::endl;
    }
    return app.exec();
}
