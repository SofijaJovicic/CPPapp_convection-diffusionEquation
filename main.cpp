#include "qTransEq.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QLineEdit>
#include <QSplashScreen>
#include "unistd.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    a.setStyle(QStyleFactory::create("fusion"));
    QSplashScreen *splash = new QSplashScreen();  //dodat prozor na samom pocetku
    QPixmap pick("../QTransEq/resources/logo.png");
    splash->setPixmap(pick);
    splash->show();

    QTransEq w;  //glavni prozor

    a.processEvents();
    sleep(3);


    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(60,60,60));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(113,113,113));
    darkPalette.setColor(QPalette::AlternateBase, QColor(100,100,100));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::darkBlue);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, Qt::darkBlue);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, Qt::lightGray);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::lightGray);



    darkPalette.setColor(QPalette::Highlight, Qt::darkMagenta);
    darkPalette.setColor(QPalette::HighlightedText, Qt::darkBlue);


    a.setPalette(darkPalette);
    w.setWindowOpacity(0.97);
   a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
  a.setStyleSheet("background-color: rgba(255, 255, 0, 50%)");



  w.show();
  splash->finish(&w);
  delete splash;

    return a.exec();
}
