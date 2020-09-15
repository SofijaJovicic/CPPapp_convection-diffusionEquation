#include "pictureWidget.h"
#include "painterWidget.h"
#include "data.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QToolBar>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTime>
#include <QCoreApplication>

PictureWidget::PictureWidget(Data * data, Result * result, 
      QStatusBar * statusBar):_data(data)
{
    //u Vertical Box ubacujem painterWidget (koji je zapravo nasa slika sa rezultatima)
   QVBoxLayout * pictureLayout = new QVBoxLayout;
   _painterWidget = new PainterWidget(data, result, statusBar);
   pictureLayout->addWidget(_painterWidget);
   //zatim kreiram akcije za play. next itd.
   createActions();
   //zatim kreiram ToolBars i dodajem _timeToolBar u nas Layout
   createToolBars();
   pictureLayout->addWidget(_timeToolBar);
   //setujem Layout...
   setLayout(pictureLayout);

   //signal calculate iz data vezujem sa slotom setEvrything iz ove klase
   connect(_data, SIGNAL(calculate()), this, SLOT(setEverything()));


}


void PictureWidget::createToolBars()
{
    //ispod slike je tool bar koji sadrzi:
    _timeToolBar = new QToolBar;
    //labelu time i 0
   QLabel * timeLabel=new QLabel(tr("Time  "));
   _timeToolBar->addWidget(timeLabel);
   _time = new QLabel(tr("0"));
   _timeToolBar->addWidget(_time);
   //zatim labelu Time step
   QLabel * timeStepLabel = new QLabel(tr("  Time step  "));
   _timeToolBar->addWidget(timeStepLabel);
   //i na kraju QSpinBox u kome redom vidimo kako ide vreme
   _timeStep = new QSpinBox;
   _timeToolBar->addWidget(_timeStep);
   //u tool bar dodajemo i sve potrebne akcije, za play, prev, next itd...
   _timeToolBar->addAction(_firstAct);
   _timeToolBar->addAction(_prevAct);
   _timeToolBar->addAction(_playAct);
   _timeToolBar->addAction(_nextAct);
   _timeToolBar->addAction(_lastAct);
}

//kreiramo pomenute akcije
void PictureWidget::createActions()
{
    //Ubacila sam slicicu QIcon(putanja) kao ono sto hocu da mi pretstavlja akciju,
        //ovo tr("tekst") je -sta se prikaze kada misem prodjem preko slicice i treci
        //argument predstavlja klasu u kojoj se akcija nalazi (parent klasa)
       _firstAct = new QAction(QIcon("../QTransEq/resources/go-first-view.png"), tr("&First"), this);
      // signal triggered() akcije _firstAct povezujemo sa slotom first() iz parent klase
       connect(_firstAct, SIGNAL(triggered()), this, SLOT(first()));

       //dalje je analogno prethodnom samo za ostale akcije...
       _prevAct = new QAction(QIcon("../QTransEq/resources/go-first-5.png"), tr("&Previous"), this);
       connect(_prevAct, SIGNAL(triggered()), this, SLOT(previous()));

       _playAct = new QAction(QIcon("../QTransEq/resources/go-next-view.png"), tr("&Play"), this);
       connect(_playAct, SIGNAL(triggered()), this, SLOT(play()));

       _nextAct = new QAction(QIcon("../QTransEq/resources/go-last-4.png"), tr("&Next"), this);
       connect(_nextAct, SIGNAL(triggered()), this, SLOT(next()));

       _lastAct = new QAction(QIcon("../QTransEq/resources/go-last-view.png"),tr("&Last"), this);
       connect(_lastAct, SIGNAL(triggered()), this, SLOT(last()));
    }

//sada definisemo slotove first(), last(), previous(), play() i next()
void PictureWidget::first()
{
    //vremenski korak=0
   _timeStep->setValue(0);
   //menjam labelu time (tj. trenutno je 0)
   _time->setText(QString::number(0));
   //setujem vreme u painterWidget
   _painterWidget->setTimeStep(0);
}
void PictureWidget::previous()
{
   //vremenski koraj je trenutno vreme
   int timeStep=_timeStep->value();
   //ako nije 0...
   if(timeStep!=0)
   {
       //smanjujem ga za 1
      _timeStep->setValue(timeStep-1);
      //menjam i labelu
      _time->setText(QString::number((timeStep-1)*_data->getDeltaT()));
      _painterWidget->setTimeStep(timeStep-1);
   }
}
void PictureWidget::play()
{
    //dalje je analogno prethidnom

    //razlika je sto ovde ulazim u petlju koja za dati vremenski korak i maximalno vreme
    //redom ocitava rezultate...
   for(int i=0;i<=_data->getnt();i++)
   {
      _timeStep->setValue(i);
      _time->setText(QString::number(i*_data->getDeltaT()));
      _painterWidget->setTimeStep(i);
      _painterWidget->repaint();
      //ceo play treba da traje 30 sekundi, sa 1000 mnozim jer je time step u milisek.
      int timestep=1000*30.0/_data->getnt();
      QTime moveOn = QTime::currentTime().addMSecs(timestep);
      //sve dok je trenutno vreme manje od moveOn...
      while(QTime::currentTime()<moveOn)
      {
          //posto ceo play mora da traje 35s sledeci metod omogucava da
          //se slajd zadrzi (da se petlja ne zavrsi pre tih 30s)
         QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
      }

   }

}
void PictureWidget::next()
{
   int timeStep=_timeStep->value();
   if(timeStep!=_timeStep->maximum())
   {
      _timeStep->setValue(timeStep+1);
      _time->setText(QString::number((timeStep+1)*_data->getDeltaT()));
      _painterWidget->setTimeStep(timeStep+1);
   }
}
void PictureWidget::last()
{
   _timeStep->setValue(_timeStep->maximum());
   _time->setText(QString::number(_timeStep->maximum()*_data->getDeltaT()));
   _painterWidget->setTimeStep(_timeStep->maximum());
}

//ovim metodom se setuju na pocete vrednosti svi podaci koji su nam potrebni za kretanje
void PictureWidget::setEverything()
{
   _painterWidget->setTimeStep(0);
   _timeStep->setMaximum(_data->getnt());
   _timeStep->setValue(0);
   _painterWidget->setRatio();
}
