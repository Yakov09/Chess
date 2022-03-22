QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_EXTRA_TARGETS += clean *.o
QMAKE_CLEAN += *.o
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    chessboard.cpp \
    chessfield.cpp \
    king.cpp \
    knight.cpp \
    main.cpp \
    mainwindow.cpp \
    mygraphicsview.cpp \
    pawn.cpp \
    piece.cpp \
    queen.cpp \
    rook.cpp
HEADERS += \
    bishop.h \
    chessboard.h \
    chessfield.h \
    king.h \
    knight.h \
    mainwindow.h \
    mygraphicsview.h \
    pawn.h \
    piece.h \
    queen.h \
    rook.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
DESTDIR=bin #Target file directory
OBJECTS_DIR=build/src #Intermediate object files directory
MOC_DIR=build/src #Intermediate moc files directory
UI_DIR=build/src
