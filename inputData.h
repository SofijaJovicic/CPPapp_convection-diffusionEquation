#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <QWidget>

//forward deklaracija klase-da bismo mogli da prosledimo objekat date klase nekoj funkciji ili metodu u ovoj klasi
class Data;
class QLineEdit;

//Klasa ulaznih podataka koja nasledjuje QWidget
class InputData : public QWidget
{
   Q_OBJECT
   public:
    //konstruktor
      InputData(Data * data);
   public slots:
      //slotovi za setovanje vrednosti na granicama i calculate
      void setBoundL(int);
      void setBoundR(int);
      void setBoundD(int);
      void setBoundU(int);
      void calculate();
   private:
      //objekat klase Data
      Data * _data;
      //QLineEdit-polja preko kojih ce se unositi ulazni podaci, znaci samo za nojmana i dirihlea
      QLineEdit * _leftLineEdit;
      QLineEdit * _rightLineEdit;
      QLineEdit * _upLineEdit;
      QLineEdit * _downLineEdit;
};



#endif



