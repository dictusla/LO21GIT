#ifndef CONFIGURATEUR_H
#define CONFIGURATEUR_H

#include <QWidget>
#include <QMainWindow>
#include <QToolBar>
//#include <QDockWidget>
//#include <QTabWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
//#include <QLineEdit>
#include <QString>
#include "Automates.h"


class Configurateur : public QWidget{
    Q_OBJECT
    friend class Interface;
    QHBoxLayout* principal;
    QPushButton* go;
    virtual void setAutomate() = 0;
protected:
    static QString nom;
    QHBoxLayout* specifique;
    Automate* automat;
    QMdiSubWindow* ventana;
public:
    Configurateur();
    virtual ~Configurateur();
    virtual QString getNom() = 0;
private slots:
    virtual void loadAutomate() = 0;
};

class Config1D : public Configurateur{
    Q_OBJECT
    friend class Interface;
    static QString nom;
    QHBoxLayout* C;
    QSpinBox* col;
    QLabel* colors;
    Config1D(const Config1D&) {}
    Config1D& operator=(const Config1D&) = delete;
    void setAutomate();
protected:
public:
    Config1D();
    ~Config1D();
    QString getNom();
private slots:
    void loadAutomate();
};

class Config2D : public Configurateur{
    Q_OBJECT
    friend class Interface;
    static QString nom;
    QLabel* live;
    QLabel* die;
    QSpinBox* Min;
    QSpinBox* Max;
    Config2D(const Config2D&) {}
    Config2D& operator=(const Config2D&) = delete;
    void setAutomate();
protected:
public:
    Config2D();
    ~Config2D() {}
    QString getNom();
private slots:
    void loadAutomate();
    void synchMax(int);
    void synchMin(int);
};

class ConfigFdF : public Configurateur{
    Q_OBJECT
    friend class Interface;
    static QString nom;
    void setAutomate();
public:
    ConfigFdF();
    ~ConfigFdF() {}
    QString getNom();
private slots:
    void loadAutomate(){}
};

class Interface : public QMainWindow{
    Q_OBJECT
    //friend class Configurateur;
    static Interface* interfaceUnique;
    unsigned int nbTypes;
    Configurateur** types;
    QMdiSubWindow** sub;
    QToolBar* bar;
    QWidget* configBar;
    QVBoxLayout* configLay;
    QComboBox* typeAut;
    QLabel* choixtype;
    QPushButton* loadAut;
    Interface();
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
protected:
    QMdiArea* centralArea;
signals:
public:
    static Interface* getInterface();
    static void libererInterface();
    void addAutoType(Configurateur* pt);
private slots:
    void ComboSynch(int b);
    void setSubWindow();
    void load();
    void synch();
};

#endif // CONFIGURATEUR_H
