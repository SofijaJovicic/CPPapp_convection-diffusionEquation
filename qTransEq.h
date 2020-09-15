#ifndef QTRANSEQ_H
#define QTRANSEQ_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QShortcut>
#include "centralWindow.h"
#include "mainMenu.h"

//nasa klasa nasledjuje QMainWindow
class QTransEq : public QMainWindow
{
   Q_OBJECT
   public:
    //konstruktor
      QTransEq()
      {
          //postavljamo naslov prozora
         setWindowTitle("QTransEq");
         //resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
         //QRect screenGeometry = QApplication::desktop()->screenGeometry();


         //status bar
         _statusBar = new QStatusBar();

         //meni bar
         _mainMenu = new MainMenu;
         setMenuBar(_mainMenu);

         //nas glavni prozor
         _centralWindow = new CentralWindow(_statusBar); //mi smo definisale da prima kao argument status bar
         setCentralWidget(_centralWindow);  //postavi

         setStatusBar(_statusBar);

         //pravim precicu za exit
         QKeySequence ks(Qt::Key_Q);
         QShortcut* shortcut = new QShortcut(ks, this);
         _mainMenu->quitAct->setShortcut(ks);

         //ova dva connecta su mi bas ovde zbog this
         connect(_mainMenu->quitAct, SIGNAL(triggered()), this, SLOT(showQuit()));  //quit
         connect(shortcut, SIGNAL(activated()), this, SLOT(showQuit()));          //x

        // show();
        // int x = (screenGeometry.width() - size().width()) / 2;
        // int y = (screenGeometry.height() - size().height()) / 2;
        // move(x,y);
      }


   private slots:

      bool showQuit()
      {
         QMessageBox exitBox;
         //ovo sam ubacila da bi prozor bio
         exitBox.setWindowOpacity(0.97);

         exitBox.setWindowTitle("Quit");
         exitBox.setText(QObject::tr("Are you sure you want to exit the program?"));
         QPixmap pic(QPixmap("../QTransEq/resources/logo1.png"));
         exitBox.setIconPixmap(pic);
         //exitBox.setIconPixmap(pic.scaledToHeight(150, Qt::SmoothTransformation));
         exitBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
         exitBox.setDefaultButton(QMessageBox::Yes);
         exitBox.setModal(false);
         if(exitBox.exec() == QMessageBox::Yes)  //ako sam kliknula yes
         {
             //this->close();
             QApplication::quit();
             QApplication::exit();
             exit(EXIT_SUCCESS);
             return true;
         }
         else
             return false;
      }

      void closeEvent(QCloseEvent* event)  //predefinisala x-ic
      {
          if(showQuit())
              event->accept();
          else
              event->ignore();
      }

   private:
      CentralWindow * _centralWindow;  //centralni prozor i main menu smo mi pravile
      QStatusBar * _statusBar;
      MainMenu * _mainMenu;

};
#endif
