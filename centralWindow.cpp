#include "centralWindow.h"
#include "data.h"
#include "result.h"
#include "inputData.h"
#include "pictureWidget.h"


CentralWindow::CentralWindow(QStatusBar * statusBar): QSplitter(Qt::Vertical)
{
    //objekat Data klase
   _data = new Data();
   //objekat klase Result (klasa rezultata)
   _result=new Result(_data);
   //objekat klase InputData (klasa ulaznih podataka)
   _inputData = new InputData(_data);

   //imam ustvari 2 dela, vidljivi-ulaz, i filmic
   //dodajem widget u centralWindow
   addWidget(_inputData);  //moze jer inputData nasledjuje QWidget

   //pictureWidget je ustvari filmic i slika nakon racunanja
   _pictureWidget = new PictureWidget(_data, _result, statusBar);
   addWidget(_pictureWidget);
   //Sakrivam pictureWidget, videce se tek kada pozovem calculate
   _pictureWidget->hide();

  //Koristimo QObject::connect() da povezemo signal i slot kao i makroe SIGNAL() i SLOT().
   //prvi argument predstavlja odakle je signal, drugi-koji signal je u pitanju, treci - odakle je slot
   //i cetvrti-koji slot je u pitanju

   connect(_data, SIGNAL(calculate()), this, SLOT(calculateRes()));
}

//metod koji racuna rezultat, on zapravo poziva calculateResult iz klase result
void CentralWindow::calculateRes()
{
    //racunamo rezultat
   _result->calculateResults();
   //ovo znaci da je onemoguceno unositi nove ulazne podatke dok se obradjuju postojeci
   _inputData->setEnabled(false);
   //Sada se prikazuje pictureWidget sa datim rezultatima
   _pictureWidget->show();
}

