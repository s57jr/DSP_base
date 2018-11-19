#-------------------------------------------------
#
# Project created by QtCreator 2018-10-21T11:22:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport multimedia

TARGET = DSP_base
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    DSP.cpp \
    FFT.cpp \
    FIRfilter.cpp \
    main.cpp \
    mainwindow.cpp \
    SigGen.cpp \
    uimw.cpp \
    ../qcustomplot/qcustomplot.cpp \
    overlapadd.cpp \
    overlapsave.cpp \
    audiobuffer.cpp

HEADERS += \
    DSP.h \
    FFT.h \
    FIRfilter.h \
    mainwindow.h \
    SigGen.h \
    uimw.h \
    ../qcustomplot/qcustomplot.h \
    overlapadd.h \
    overlapsave.h \
    audiobuffer.h

FORMS += \
        mainwindow.ui

