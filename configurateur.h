#ifndef CONFIGURATEUR_H
#define CONFIGURATEUR_H

#include <QWidget>
#include <QMainWindow>
#include <QToolBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QMdiArea>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include "Automates.h"


class configurateur : public QWidget{
    Q_OBJECT
    QVBoxLayout* principal;
    QHBoxLayout* commun;
    QSpinBox* dim;
    QLabel* dimension;
    QPushButton* go;
protected:
    QVBoxLayout* specifique;
    Automate* automat;
public:
    configurateur();
    virtual ~configurateur();
    virtual QString getNom();
    static configurateur* InstanceUnique;
    static QString nom;
    static configurateur* getInstance();
private slots:
    virtual void setAutomate()=0;
};

class config1D : public configurateur{
    Q_OBJECT
    QHBoxLayout* C;
    QSpinBox* col;
    QLabel* colors;
    config1D(const config1D&) = delete;
    config1D& operator=(const config1D&) = delete;
protected:
public:
    config1D();
    ~config1D();
    QString getNom();
    static QString nom;
private slots:
    void setAutomate();
};

class config2D : public configurateur{
    Q_OBJECT
    QVBoxLayout* lay1;
    QHBoxLayout* layMin;
    QHBoxLayout* layMax;
    QLabel* live;
    QLabel* die;
    QSpinBox* Min;
    QSpinBox* Max;
    config2D(const config2D&) = delete;
    config2D& operator=(const config2D&) = delete;
protected:
public:
    config2D();
    ~config2D();
    QString getNom();
    static QString nom;
private slots:
    void synchMax(int);
    void synchMin(int);
    void setAutomate();
};

class Interface : public QMainWindow{
    Q_OBJECT
    unsigned int nbTypes;
    configurateur** Types;
    QWidget* configBar;
    QVBoxLayout* configLay;
    QToolBar* Bar;
    QComboBox* typeAut;
    QLabel* choixtype;
    QPushButton* go;
signals:
public:
    Interface();
    void addAutoType(configurateur* pt);
private slots:
    void ComboSynch(int b);
};

#endif // CONFIGURATEUR_H
