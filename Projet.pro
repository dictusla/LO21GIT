QT += widgets
QT += xml
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11


HEADERS += \
    autocell.h \
    Automates.h \
    configurateur.h \
    etats.h \
    generateur.h \
    simulateur.h \
    savemanager.h

SOURCES += \
    autocell.cpp \
    automates.cpp \
    configurateur.cpp \
    etats.cpp \
    generateur.cpp \
    simulateur.cpp \
    main.cpp \
    mainqt.cpp \
    savemanager.cpp
