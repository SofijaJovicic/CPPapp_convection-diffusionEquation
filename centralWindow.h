#ifndef CENTRALWINDOW_H
#define CENTRALWINDOW_H

//Klasa QSplitter implementira splitter widget
//Spliter dozvoljava korisniku da kontrolise velicinu dece widget-a povlacenjem granice izmedju dece
//Jedan spliter moze da kontrolise bilo koji broj widget-a
#include <QSplitter>

//Forward deklaracija klasa
class Data;
class Result;
class InputData;
class PictureWidget;
class QStatusBar;

//CentralWindow predstavlja glavni centralni prozor
class CentralWindow : public QSplitter
{
   Q_OBJECT
   public:
    //konstruktor ove klase
      CentralWindow(QStatusBar * statusBar);
   private slots:
      //slot za racunanje rezultata
      void calculateRes();
   private:
      Data * _data;
      Result * _result;
      InputData * _inputData;
      PictureWidget * _pictureWidget;
};

#endif
