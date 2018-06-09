#ifndef AUTOMATES_H_INCLUDED
#define AUTOMATES_H_INCLUDED

#include <iostream>
#include "etats.h"

class AutomateException {
private:
      std::string info;
public:
      AutomateException(const std::string& message):info(message) {}
      std::string getInfo() const { return info; }

};

class Automate {
    friend class configurateur;
public:
    Automate() {}
    virtual ~Automate() {}
    virtual void transition(const Etat*, Etat*) const =0;
};

class Automate1D : public Automate {
    friend class config1D;
protected:
    Automate1D() : Automate() {}
    ~Automate1D();
public:
    void transition(const Etat*, Etat*) const { return; }
};

class Automate2D : public Automate{
    friend class config2D;
protected:
    Automate2D() : Automate() {}
    ~Automate2D();
public:
    void transition(const Etat* , Etat*) const { return; }
};

#endif // AUTOMATES_H_INCLUDED
