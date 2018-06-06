TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    stb_image_write.h \
    generatepoint.h \
    cluster.h \
    minspanningtree.h \
    createclustermap.h \
    kmeans.h \
    clusteringaccuracy.h \
    generalfunc.h
