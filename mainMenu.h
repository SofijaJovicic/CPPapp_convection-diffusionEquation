#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QDialog>
#include <QWebView>
#include <QUrl>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPlainTextEdit>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QPalette>
#include <QStyle>
#include <QStyleFactory>

class MainMenu : public QMenuBar
{
   Q_OBJECT
   public:

   QAction * quitAct;  //imamo je ovde jer nam je u drugoj klasi


   MainMenu()
   {



      QMenu * fileMenu = addMenu(tr("File"));
      quitAct = new QAction(tr("Quit"), this);
      QMenu * helpMenu = addMenu(tr("Help"));
      QAction * helpAct = new QAction(tr("Help"), this); //o prozoru
      QAction * aboutTAct = new QAction(tr("About Transport Eq"), this); //o projektu
      QAction * aboutGAct = new QAction(tr("GitHub"), this); //o GitHub-u
      QAction * aboutQAct = new QAction(tr("About Qt"), this); //o qt-u

      //stavljam ikonice pored
      QIcon iconhelp("../QTransEq/resources/help.png");
      helpAct->setIcon(iconhelp);
      QIcon icongithub("../QTransEq/resources/github.png");
      aboutGAct->setIcon(icongithub);
      QIcon iconqt("../QTransEq/resources/qt.png");
      aboutQAct->setIcon(iconqt);
      QIcon iconexit("../QTransEq/resources/exit.png");
      quitAct->setIcon(iconexit);

      fileMenu->addAction(quitAct);
      helpMenu->addAction(helpAct);
      helpMenu->addAction(aboutTAct);
      helpMenu->addAction(aboutGAct);
      helpMenu->addAction(aboutQAct);

      connect(helpAct, SIGNAL(triggered()), this, SLOT(showHelp()));
      connect(aboutTAct, SIGNAL(triggered()), this, SLOT(showTAbout()));
      connect(aboutGAct, SIGNAL(triggered()), this, SLOT(showGAbout()));
      connect(aboutQAct, SIGNAL(triggered()), this, SLOT(showQAbout()));

   }
   private slots:
   void showHelp()
   {
       QPalette p;
       p.setColor(QPalette::Window, Qt::white);
       p.setColor(QPalette::WindowText, Qt::black);
       p.setColor(QPalette::Base, Qt::white);
       p.setColor(QPalette::Text, Qt::black);

       QDialog* myDialog = new QDialog(this);
       myDialog->setGeometry(0,0,1000,650);
       myDialog->setWindowOpacity(0.97);

       QVBoxLayout* myVBox = new QVBoxLayout(myDialog);  //sve cemo redjati jedno ispod drugog, text ispod slike

       QPixmap myImage("../QTransEq/resources/shot.png");
       QLabel* myLabel = new QLabel();
       myLabel->setPixmap(myImage);
       myLabel->setAlignment(Qt::AlignHCenter);  //poravnam sliku
       myVBox->addWidget(myLabel);
       myLabel->show();

       QHBoxLayout* myHBox = new QHBoxLayout();  //pravimo hbox u donjem vboxu, da bismo stavili sliku pored texta

       QPlainTextEdit* myPlainTextEdit = new QPlainTextEdit();
       myPlainTextEdit->setReadOnly(true);  //ne zelim da pisem u njemu direktno
       //myPlainTextEdit->setStyleSheet("background-color: pink");

       //ucitavanje texta iz fajla i ispisivanje na plaintextedit
       QFile fajl("../QTransEq/resources/help.txt");
       if(!fajl.open(QIODevice::ReadOnly))
       {
           qDebug() << "error opening file: " << fajl.error();
       }
       else
       {
           QTextStream in(&fajl);
           while (!in.atEnd())
           {
              QString line = in.readLine();  //citam liniju po liniju
              myPlainTextEdit->appendPlainText(line);
           }
           fajl.close();
       }

       myHBox->addWidget(myPlainTextEdit);

       QPixmap image("../QTransEq/resources/logo1.png");
       QLabel* label = new QLabel();
       label->setPixmap(image);
       myHBox->addWidget(label);

       myVBox->addLayout(myHBox);  //dodajem u donji deo vboxa hbox
       myPlainTextEdit->setWindowOpacity(0.97);
       myPlainTextEdit->setPalette(p);

       myPlainTextEdit->show();
       label->show();

       myDialog->setModal(true);

       myDialog->setPalette(p);
       myDialog->setWindowOpacity(0.97);

       myDialog->exec();
   }

   void showTAbout()
   {
       QPalette p;
       p.setColor(QPalette::Window, Qt::white);
       p.setColor(QPalette::WindowText, Qt::black);
       p.setColor(QPalette::Base, Qt::white);
       p.setColor(QPalette::Text, Qt::black);
      QDialog* myDialog = new QDialog(this);
      myDialog->setGeometry(0,0,1000,650);

      myDialog->setWindowOpacity(0.97);

      QWebView * myWebView = new QWebView(myDialog);
      myWebView->setGeometry(0,0,1000,650);
      myWebView->setPalette(p);

      myWebView->setWindowOpacity(0.97);

      QString path = QDir().absoluteFilePath("../QTransEq/resources/aboutTransportEq.htm");
      QString string("file:///");
      myWebView->load(QUrl(string+path));
      myWebView->show();
      myDialog->setModal(true);
      myDialog->exec();

      qDebug()<<" hej hej \n";
   }

   void showGAbout()
   {
       QString id = "https://github.com/MATF-RS16/rs16-11";
       bool b = QDesktopServices::openUrl(QUrl(id, QUrl::StrictMode));
       if(!b)
       {
           QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,QString("ERROR"),
                                                    "Check your internet connection or browser settings.",QMessageBox::Ok);

           newError->exec();
       }
   }

   void showQAbout()
   {
      QApplication::aboutQt();
   }

};


#endif
