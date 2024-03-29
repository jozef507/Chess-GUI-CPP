#-------------------------------------------------
#
# Project created by QtCreator 2019-05-04T21:36:13
# with modified paths.
#
# Autor: Jan Holásek (xholas09)
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        logic/Board.cpp \
        logic/Field.cpp \
        logic/FigureBishop.cpp \
        logic/FigureKing.cpp \
        logic/FigureKnight.cpp \
        logic/FigurePawn.cpp \
        logic/FigureQueen.cpp \
        logic/FigureRook.cpp \
        logic/FiguresManager.cpp \
        logic/GameChess.cpp \
        logic/MovementManager.cpp \
        logic/Notation.cpp \
        logic/NotationMovement.cpp \
        logic/QtGame.cpp \
        gui/boardwidget.cpp \
        gui/chesswidget.cpp \
        gui/main.cpp \
        gui/mainwindow.cpp \
        gui/newfiguredialog.cpp

HEADERS += \
        logic/Board.h \
        logic/Field.h \
        logic/Figure.h \
        logic/FigureBishop.h \
        logic/FigureKing.h \
        logic/FigureKnight.h \
        logic/FigurePawn.h \
        logic/FigureQueen.h \
        logic/FigureRook.h \
        logic/FiguresManager.h \
        logic/Game.h \
        logic/GameChess.h \
        logic/MovementManager.h \
        logic/Notation.h \
        logic/NotationMovement.h \
        logic/QtGame.h \
        gui/boardwidget.h \
        gui/chesstypes.h \
        gui/chesswidget.h \
        gui/guiinterface.h \
        gui/mainwindow.h \
        gui/newfiguredialog.h

FORMS += \
        gui/boardwidget.ui \
        gui/chesswidget.ui \
        gui/mainwindow.ui \
        gui/newfiguredialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gui/resources.qrc
