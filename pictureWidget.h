#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>

class PainterWidget;
class Data;
class Result;
class QAction;
class QToolBar;
class QLabel;
class QSpinBox;
class QStatusBar;

class PictureWidget : public QWidget
{
   Q_OBJECT   
   public:
    //konstruktor (prima objekat tipa Data, Result i QStatusBar zato sto mi trebaju
    //i ulazni podaci i rezultati i status bar za ispis na slici)
      PictureWidget(Data * data, Result * result, QStatusBar * statusBar);
   private slots:
      //slotovi za akcije (QAction) ispod slike
      void first();
      void previous();
      void play();
      void next();
      void last();
      void setEverything();
   private:
      void createToolBars();
      void createActions();

      Data * _data;
      PainterWidget * _painterWidget;
      QAction * _firstAct;
      QAction * _prevAct;
      QAction * _playAct;
      QAction * _nextAct;
      QAction * _lastAct;

      //ToolBar gde ce biti ispisano vreme
      QToolBar * _timeToolBar;
      QLabel * _time;

      //vremenski korak
      QSpinBox * _timeStep;
};


#endif
