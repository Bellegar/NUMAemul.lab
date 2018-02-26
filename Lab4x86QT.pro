#-------------------------------------------------
#
# Project created by QtCreator 2017-05-21T20:19:18
#
#-------------------------------------------------

QT      += core gui
QT      += svg
CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Lab4x86QT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    tgraph.cpp \
    tnode.cpp \
    tproc.cpp \
    tbus.cpp \
    tmachine.cpp \
    tfiletograph.cpp \
    axisform.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    tgraph.h \
    tnode.h \
    tproc.h \
    tbus.h \
    tmachine.h \
    tfiletograph.h \
    axisform.h \
    qcustomplot.h \
    structs.h

FORMS    += mainwindow.ui \
    axisform.ui
#QMAKE_CXXFLAGS+= -openmp
#QMAKE_LFLAGS +=  -openmp
CONFIG += c++11;


win32:CONFIG(release, debug|release): LIBS += -LE:/Progi/OGDF3/Build/release/ -lOGDF
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/Progi/OGDF3/Build/debug/ -lOGDF
else:unix:!macx: LIBS += -LE:/Progi/OGDF3/Build/ -lOGDF

INCLUDEPATH += E:/Progi/OGDF3/include
DEPENDPATH += E:/Progi/OGDF3/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/release/libOGDF.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/debug/libOGDF.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/release/OGDF.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/debug/OGDF.lib
else:unix:!macx: PRE_TARGETDEPS += E:/Progi/OGDF3/Build/libOGDF.a

win32:CONFIG(release, debug|release): LIBS += -LE:/Progi/OGDF3/Build/release/ -lCOIN
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/Progi/OGDF3/Build/debug/ -lCOIN
else:unix:!macx: LIBS += -LE:/Progi/OGDF3/Build/ -lCOIN

INCLUDEPATH += E:/Progi/OGDF3/Build/include
DEPENDPATH += E:/Progi/OGDF3/Build/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/release/libCOIN.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/debug/libCOIN.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/release/COIN.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += E:/Progi/OGDF3/Build/debug/COIN.lib
else:unix:!macx: PRE_TARGETDEPS += E:/Progi/OGDF3/Build/libCOIN.a

RC_FILE = icn.rc
