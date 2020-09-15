TEMPLATE = app
CONFIG += qt
CONFIG += c++11 

QT       += core gui
QT       += webkit
QT       += webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = qTransEq

SOURCES += main.cpp \
           centralWindow.cpp \
           inputData.cpp \
           pictureWidget.cpp \
           painterWidget.cpp \
           result.cpp

HEADERS += centralWindow.h \
           inputData.h \
           qTransEq.h\
           data.h\
           pictureWidget.h \
           painterWidget.h \
           result.h \
           mainMenu.h

OTHER_FILES += opis.htm \
               go-first-5.png \
               go-first-view.png \
               go-last-4.png \
               go-last-view.png \
               go-next-view.png \
               logo.png




