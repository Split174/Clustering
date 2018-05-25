TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    clusterclass.cpp \
    k_means.cpp \
    minspanningtree.cpp

HEADERS += \
    clusterclass.h \
    k_means.h \
    minspanningtree.h
