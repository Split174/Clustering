TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    clusterclass.cpp \
    k_means.cpp \
    minspanningtree.cpp \
    createclustermap.cpp

HEADERS += \
    clusterclass.h \
    k_means.h \
    minspanningtree.h \
    clusteringaccuracy.h \
    stb_image_write.h \
    generatepoint.h
