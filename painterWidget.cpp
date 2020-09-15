#include "painterWidget.h"
#include "data.h"
#include "result.h"
#include <QPainter>
#include <QStatusBar>
#include <QMouseEvent>
#include <QDebug>


PainterWidget::PainterWidget(Data * data, Result * result, 
      QStatusBar * statusBar):_data(data), _result(result),
   _statusBar(statusBar)
{
   setMouseTracking(true);
}

//Ovaj metod omogucava prikaz vrednosti koncentracije u fluidu prelaskom misa preko slike u status baru
void PainterWidget::mouseMoveEvent(QMouseEvent * event)
{
   if(inverseTransformX(event->pos().x())<_data->getxmax())
   {
      double xpos=inverseTransformX(event->pos().x());
      double ypos=inverseTransformY(event->pos().y());
      QString str="X: "+QString::number((xpos), 'f', 2)+"; Y: "+QString::number((ypos), 'f', 2)+") --- ";
      int i=(int) xpos/_data->getDeltaX()+0.5;
      int j=(int) ypos/_data->getDeltaY()+0.5;

      str+=QString::number(_result->getResultsTime(_timeStep)[j][i]);
      _statusBar->showMessage(str);
   }
}

//Klasa QSize definise velicinu dvodimenzionog objekta
QSize PainterWidget::minimumSizeHint() const
{
    //ovo sam stavila proizvoljno, da na bi bio manji od toga
    return QSize(1050,150);
}

//setRatio mi podesava odnos izmedju x ose i y ose
//jer mi to treba da bih formirala sliku, dakle ne trebaju mi vrednosti nego razmera

void PainterWidget::setRatio()
{
    //povecala sam odnos za 20% nego sto je slika zapravo da bi imalo
    //mesta i za legendu sa strane
   _ratio=1.20*(_data->getxmax()-_data->getxmin())/(_data->getymax()-_data->getymin());
}

//koordinatna transformacija pravougaonika (domena) u sliku u pikselima
double PainterWidget::transformX(double x) const
{
   return _transform_a*x+_transform_b;
}

double PainterWidget::transformY(double y) const
{
   return _transform_c*y+_transform_d;
}


//inverzne transformacije...
double PainterWidget::inverseTransformX(double x) const
{
   return (1/_transform_a)*x-_transform_b/_transform_a;
}

double PainterWidget::inverseTransformY(double y) const
{
   return (1/_transform_c)*y-_transform_d/_transform_c;
}

//postavljanje transformacija g-_sirina i h-_visina u pikselima
void PainterWidget::setTransform(const double g, const double h)
{
   _transform_a=g/(_data->getxmax()-_data->getxmin());
   _transform_b=-_transform_a*_data->getxmin();
   _transform_c=-h/(_data->getymax()-_data->getymin());
   _transform_d=h-_transform_c*_data->getymin();
}

//ponovo iscrtava sliku (da bih imala filmic)
void PainterWidget::repaint()
{
   update(0,0,width(),height());
}

void PainterWidget::resizeEvent(QResizeEvent * event)
{
    //_sirina i _visina u pikselima
   //width() funkcija koja vraca sirinu painterWidgeta-a (ugradjena)
   if(width()/_ratio<height())
   {
      _sirina=width();
      _visina=_sirina/_ratio;
   }else{
      _visina=height();
      _sirina=_visina*_ratio;
   }


   setTransform(_sirina-_sirina/6,_visina);
   setGeometry(5,5,_sirina,_visina);
}

//overload-ujem funkciju paintEvent
void PainterWidget::paintEvent(QPaintEvent * event)
{
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing, true);

  

   //crtam pravougaonike...
   for(int i=0;i<_data->getnx();i++)
   {
      for(int j=0;j<_data->getny();j++)
      {
	//delim domen na pravougaonike i bojim na osnovu rezultata
         int leftx=(int) (transformX(_data->getxmin()+
                  (i-0.5)*_data->getDeltaX())+0.5);
         int lefty=(int) (transformY(_data->getymin()+
                  (j+0.5)*_data->getDeltaY())+0.5);
         int width=(int) (transformX(_data->getxmin()+
                  (i+0.5)*_data->getDeltaX())-leftx+0.5);
         int height=(int) (transformY(_data->getymin()+
                  (j-0.5)*_data->getDeltaY())-lefty+0.5);
         if(width+leftx>_sirina-_sirina/6)
            width=_sirina-_sirina/6-leftx;
         //col-boja crvena ( R u RGB)
        // int col=(_result->getResultsTime(_timeStep)[j][i]-_result->minRes())*255/(_result->maxRes()-_result->minRes());
        //ovo je da ne bih imala ivicu pravougaonika koje iscrtavam
         painter.setPen(QPen(Qt::black,1,Qt::NoPen));
         //postavljam boju
         painter.setBrush(QBrush(QColor(_result->getColor(i,j,_timeStep),0,255)));
         painter.drawRect(leftx,lefty,width,height);
      //   qDebug()<<" crtas pravougaonik ("<<leftx<<";"<<lefty<<") tj ("<<_data->getxmin()+(i-0.5)*deltaX<<";"<<_data->getymin()+(j+0.5)*deltaY<<") "<<"_sirina "<<width<<" i _visina "<<height<<"\n";
        // qDebug()<<" i "<<i<<" j "<<j<<" k "<<_timeStep<<" rezultat "<<_result->getResultsTime(_timeStep)[j][i]<<"\n";

              /* transformX(_data->getxmin()+(i-0.5)*deltaX), 
                  transformY(_data->getymin()+(j+0.5)*deltaY), 
                  transformX(_data->getxmin()+(i+0.5)*deltaX)-transformX(_data->getxmin()+(i-0.5)*deltaX),
                  transformY(_data->getymin()+(j+0.5)*deltaY)-transformY(_data->getymin()+(j-0.5)*deltaY));*/
      }
   }

//   painter.drawRect(transformX(0), transformY(sadeltaY), transformX(sadeltaX),
 //        transformY(0));

   //crtanje legende...
   QLinearGradient grad(_sirina-_sirina/10,0,_sirina-_sirina/10,_visina);
   grad.setColorAt(0, QColor(255,100,255));
   grad.setColorAt(1, QColor(0,100,255));

   painter.setBrush(QBrush(grad));
   painter.drawRect(_sirina-_sirina/10,0,_sirina/20, _visina);
   painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
   painter.drawText(_sirina-_sirina/20+1, 10, 
         QString::number(_result->maxRes(), 'f', 2));
   painter.drawText(_sirina-_sirina/20+1, _visina, 
         QString::number(_result->minRes(), 'f', 2));
  // qDebug()<<_result->maxRes()<<" imas da je _sirina "<<_sirina<<" "<<_visina<<" skala ("<<_sirina-_sirina/10<<";0) _sirina "<<_sirina/20<<" i _visina "<<_visina<<"\n";
/*   painter.drawRect(0,150,75,75);*/
   
   
  /* painter.setPen(palette().dark().color());
   painter.setBrush(Qt::NoBrush);
   painter.drawRect(QRect(0, 0, width() - 1, height() - 1));*/
}
