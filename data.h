#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <QObject>
#include <QDebug>
#include <QMessageBox>


//Klasa Data sadrzi sve podatke koji su nam potrebni

class Data: public QObject
{
    Q_OBJECT
   private:
      int _nt;//=10;
      int _nx;//=10;
      int _ny;//=10;
      double _T;//=1000.0;
      double _xmin;//=0.0;
      double _xmax;//=100.0;
      double _ymin;//=0.0;
      double _ymax;//=100.0;
      double _vx;//=1.0;
      double _vy;//=1.0;
      double _Dx;//=1.0;
      double _Dy;//=1.0;
      double _deltaX;
      double _deltaY;
      double _deltaT;

      //Source term:

      //prostorne koordinate
      double _sxmin;
      double _sxmax;
      double _symin;
      double _symax;
      //vremenske koordinate
      double _stmin;
      double _stmax;
      //vrednost source-a
      double _svalue;

      //Pocetno resenje
      double _initial;


      std::vector<bool> _granica;
      std::vector<double> _granicaVrednost;



   signals:
      void calculate();



   public:
      /*Data(size_t ant = 10, size_t anx = 5, size_t any = 5,
            double aT = 1000, double axmin = 0,
            double axmax = 100.0, double aymin = 0.0,
            double aymax = 100.0,double avx=1,
            double avy=0.0, double aDx=1e-6,
            double aDy=1e-6, std::vector<bool> agranica =
            {true, false, false, false},
            std::vector<double> abrzinautackama = {0.0})
         :_nt(ant),_nx(anx),_ny(any),_T(aT),_xmin(axmin),_ymin(aymin),
         _xmax(axmax),_ymax(aymax),_vx(avx),_vy(avy),_Dx(aDx),_Dy(aDy),
         _granica(agranica)
         {
          qDebug()<<" ovde smooo \n";

         }*/

      //Konstruktor...
      Data()
      {
          _granica.resize(4, true);
          _granicaVrednost.resize(4);
      }




      int getnt() const {
         return _nt;
      }
      int getnx() const {
         return _nx;
      }
      int getny() const {
         return _ny;
      }

      double getT() const {
         return _T;
      }
      double getxmin() const {
         return _xmin;
      }
      double getxmax() const{
         return _xmax;
      }
      double getymin() const {
         return _ymin;
      }
      double getymax() const {
         return _ymax;
      }
      double getInitial()const{
         return _initial;
      }
      double getvx() const {
         return _vx;
      }
      double getvy() const {
         return _vy;
      }
      double getDx() const {
         return _Dx;
      }
      double getDy() const {
         return _Dy;
      }

      bool getgranica(const int i) const {
         return _granica[i];
      }

      double getgranicaVred(const int i) const {
         return _granicaVrednost[i];
      }

      double sadeltaT() const{
         return 1/_deltaT;
      }

      double getsxmin() const{
         return _sxmin;
      }
      double getsxmax() const{
         return _sxmax;
      }
      double getsymin() const{
         return _symin;
      }
      double getsymax() const{
         return _symax;
      }
      double getstmin() const{
         return _stmin;
      }
      double getstmax() const{
         return _stmax;
      }
      double getsvalue() const{
         return _svalue;
      }
      double getDeltaX()const{
         return _deltaX;
      }
      double getDeltaY()const{
         return _deltaY;
      }
      double getDeltaT()const{
         return _deltaT;
      }

      void setgranica(int i, bool agranica){
         _granica[i] = agranica;
      }

      void setgranicaVred(int i, double vrednost){
          _granicaVrednost[i]=vrednost;
      }
      bool checkData() const
          {
          if(_xmin>=_xmax)
          {
             QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                   QString("ERROR"),
                   "xmax must be greater then xmin",
                   QMessageBox::Ok);
             newError->exec();
             return false;
          }
          if(_ymin>=_ymax)
          {
             QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                   QString("ERROR"),
                   "ymax must be greater then ymin",
                   QMessageBox::Ok);
             newError->exec();
             return false;
          }
             if(_nt<2)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "Number of time steps must be greater than 1!",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }
             if(_T<=0)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "Maximum time mast be greater then 0!",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }
             if(_Dx!=_Dy)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "diffusivity must be the same in every direction!",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }

             if(_sxmin>=_sxmax)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "xmax must be greater then xmin",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }
             if(_symin>=_symax)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "ymax must be greater then ymin",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }
             if(_symin<_ymin || _symax>_ymax)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "Domain must be greater or equal with the domain of the source!",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }
             if(_sxmin<_xmin || _xmax>_xmax)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "Domain must be greater or equal with the domain of the source!",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }
             if(_stmin<0 || _stmin>_T || _stmax>_T)
             {
                QMessageBox * newError = new QMessageBox(QMessageBox::Icon::Warning,
                      QString("ERROR"),
                      "Source time begin and source time end must be between 0 and maximum time!",
                      QMessageBox::Ok);
                newError->exec();
                return false;
             }
             return true;
          }

public slots:

//slotovi...

      //prosledjuje se QString jer mi unosimo podatke sa tastature
      void setnt(QString str){
         _nt = str.toInt();
         _deltaT = _T/_nt;
      }

      void setnx(QString str){
         _nx = str.toInt();
         _deltaX = (_xmax-_xmin)/(_nx-1);
      }
      void setny(QString str){
         _ny = str.toInt();
         _deltaY = (_ymax-_ymin)/(_ny-1);
      }


      void setT(QString str){
         _T = str.toDouble();
      }
      void setxmin(QString str){
         _xmin = str.toDouble();
      }
      void setxmax(QString str){
         _xmax = str.toDouble();
      }
      void setymin(QString str){
         _ymin = str.toDouble();
      }
      void setymax(QString str){
         _ymax = str.toDouble();
      }
      void setInitial(QString str){
         _initial = str.toDouble();
      }
      void setvx(QString str){
         _vx = str.toDouble();
      }
      void setvy(QString str){
         _vy = str.toDouble();
      }
      void setDx(QString str){
         _Dx = str.toDouble();
      }
      void setDy(QString str){
         _Dy = str.toDouble();
      }      

      void setsxmin(QString str){
         _sxmin = str.toDouble();
      }
      void setsxmax(QString str){
         _sxmax = str.toDouble();
      }
      void setsymin(QString str){
         _symin = str.toDouble();
      }
      void setsymax(QString str){
         _symax = str.toDouble();
      }
      void setstmin(QString str){
         _stmin = str.toDouble();
      }
      void setstmax(QString str){
         _stmax = str.toDouble();
      }
      void setsvalue(QString str){
         _svalue = str.toDouble();
      }
      //slotovi za setovanje vrednosti na granicama
      
      void setLeftBValue(QString str){
         setgranicaVred(0, str.toDouble());
      }
      
      void setRightBValue(QString str){
         setgranicaVred(1, str.toDouble());
      }

      void setDownBValue(QString str){
         setgranicaVred(2, str.toDouble());
      }
      
      void setUpBValue(QString str){
         setgranicaVred(3, str.toDouble());
      }

};





#endif // DATA_H

