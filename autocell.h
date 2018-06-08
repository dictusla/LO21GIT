#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QtWidgets>

class AutoCell : public QWidget{
    Q_OBJECT
        QSpinBox* num; // numéro
        QLineEdit* numeroBit[8]; // un QLineEdit par bit
        QLabel* numl;
        QLabel* numeroBitl[8];
        QVBoxLayout* numc;
        QVBoxLayout* bitc[8];
        QHBoxLayout* numeroc;
        QIntValidator* zeroOneValidator;
        QTableWidget* depart;
        unsigned int dimension = 25;
        QVBoxLayout* couche;
        QTableWidget* etats;
        QPushButton* simulation;
        QPushButton* quit;
        QTabWidget* onglets;
        QWidget* page1;
        QWidget* page2;
        QVBoxLayout* main;

    public:
        explicit AutoCell(QWidget* parent = nullptr);
    private slots:
        void synchronizeNumToNumBit(int i);
        void synchronizeNumBitToNum(const QString& s);
        void cellActivation(const QModelIndex& index);
        void launchSimulation();
    };
#endif // AUTOCELL_H
