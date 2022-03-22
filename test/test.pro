TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH=../thirdparty ../src

SOURCES += \
        main.cpp \
        mytests.cpp \
        ../src/bishop.cpp \
        ../src/chessboard.cpp \
        ../src/chessfield.cpp \        
        ../src/king.cpp \
        ../src/knight.cpp \
        ../src/pawn.cpp \
        ../src/piece.cpp \
        ../src/queen.cpp \
        ../src/rook.cpp

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

DESTDIR=bin #Target file directory
OBJECTS_DIR=build/test #Intermediate object files directory
MOC_DIR=build/test #Intermediate moc files directory
UI_DIR=build/test

