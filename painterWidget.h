#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>

class Data;
class Result;
class QStatusBar;
class QMouseEvent;


class PainterWidget : public QWidget
{
   Q_OBJECT
   public:
      //konstruktor
      PainterWidget(Data * data, Result * result, QStatusBar * statusBar);
      
      void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
      QSize minimumSizeHint() const Q_DECL_OVERRIDE;
      void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;
      
      void setRatio();
      //transformacije i inverzne transformacije
      double transformX(const double x) const;
      double transformY(const double y) const;
      double inverseTransformX(const double x) const;
      double inverseTransformY(const double y) const;
      void setTransform(const double g, const double h);
      void setTimeStep(const int i) 
      {
         _timeStep=i;
      }
      void repaint();

   protected:
       void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
   private:
       double _transform_a;
       double _transform_b;
       double _transform_c;
       double _transform_d;
       double _ratio;
       double _sirina;
       double _visina;
       int _timeStep;
       Data * _data;
       Result * _result;
       QStatusBar * _statusBar;
};


#endif
