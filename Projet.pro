QT += widgets
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11


HEADERS += \
    ../Automates.h \
    ../etats.h \
    ../simulateur.h \
    autocell.h

SOURCES += \
    ../automates.cpp \
    ../etats.cpp \
    ../simulateur.cpp \
    autocell.cpp \
    main.cpp
