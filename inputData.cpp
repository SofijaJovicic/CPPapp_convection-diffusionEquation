#include "inputData.h"
#include "data.h"
#include "result.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

InputData::InputData(Data * data):_data(data)
{
    //Horizontal Box layout-slaze komponente jedne ispod druge-horizontalno
    //To ce nam biti neki inptLouoyt u koji cemo ubaciti ulazne podatke
   QHBoxLayout * inputLayout = new QHBoxLayout; 

   //QFrame koristim samo da bi mi lepo napravilo okvir oko grupisanih podataka
   QFrame * spatialFrame = new QFrame;

   //QGridLayot- u svakom Frame-u imacu ovaj layout
   QGridLayout * spatialLayout = new QGridLayout;
   //labela "Domain"
   QLabel * spatial = new QLabel(tr("Domain"));

   //Do sada smo samo inicijalizovali gornje objekte, nismo ih nigde ubacili
   //Na ovaj nacin u spatialLayout ubacujem labelu na poziciji (0,0) - gornji levi ugao
   spatialLayout->addWidget(spatial, 0, 0);

   //zatim pravim novu labelu i nju ubacujem odmah ispod prethodne - pozicija (1,0)
   QLabel * xmin = new QLabel(tr("xmin"));
   xmin->setToolTip("meters [m]");
   spatialLayout->addWidget(xmin, 1, 0);

   //analogno sa prethodnim pravim i ubacijem labelu ymin na poziciju (1,1)
   QLabel * ymin = new QLabel(tr("ymin"));
   spatialLayout->addWidget(ymin, 1, 1); 
   ymin->setToolTip("meters [m]");

   //polje za unos QLineEdit ubacujem na poziciju (2,0) i tako analogno za ymin...
   QLineEdit * xminLineEdit = new QLineEdit;
   spatialLayout->addWidget(xminLineEdit, 2, 0);
   QLineEdit * yminLineEdit = new QLineEdit;
   spatialLayout->addWidget(yminLineEdit, 2, 1);


   //Analogno prethodnom pravim labele xmax i ymax i odgovrajuca polja za unos i ubacujem ih u spatialLayout
   QLabel * xmax = new QLabel(tr("xmax"));
   spatialLayout->addWidget(xmax, 3, 0);
   xmax->setToolTip("meters [m]");
   QLabel * ymax = new QLabel(tr("ymax"));
   spatialLayout->addWidget(ymax, 3, 1); 
   ymax->setToolTip("meters [m]");
   QLineEdit * xmaxLineEdit = new QLineEdit;
   spatialLayout->addWidget(xmaxLineEdit, 4, 0);
   QLineEdit * ymaxLineEdit = new QLineEdit;
   spatialLayout->addWidget(ymaxLineEdit, 4, 1);

   //Analogno prethodnom za nx, ny...

   QLabel * nx = new QLabel(tr("nx"));
   spatialLayout->addWidget(nx, 5, 0);
   nx->setToolTip("division");
   QLabel * ny = new QLabel(tr("ny"));
    ny->setToolTip("division");
   spatialLayout->addWidget(ny, 5, 1); 
   QLineEdit * nxLineEdit = new QLineEdit;
   spatialLayout->addWidget(nxLineEdit, 6, 0);
   QLineEdit * nyLineEdit = new QLineEdit;
   spatialLayout->addWidget(nyLineEdit, 6, 1);


   //QGridLayout * timeLayout = new QGridLayout;

   //Labela za ukupno vreme takodje se smesta u spatialLayout kao i odgovarajuce polje za unos,
   //analogno se radi i za vremenski kroak...-
   QLabel * timeEnd = new QLabel(tr("Tend"));
    timeEnd->setToolTip("maximum time");
   spatialLayout->addWidget(timeEnd, 7, 0);
   QLineEdit * timeEndLineEdit = new QLineEdit;
   spatialLayout->addWidget(timeEndLineEdit, 8, 0);
   QLabel * nt = new QLabel(tr("nt"));
    nt->setToolTip("time step");
   spatialLayout->addWidget(nt, 7, 1);
   QLineEdit * ntLineEdit = new QLineEdit;
   spatialLayout->addWidget(ntLineEdit, 8, 1);

   //setujem layout koji smo upravo napravili
   spatialFrame->setLayout(spatialLayout);
   

   //Ovo postavljam da bi frame imao okvir-ovo je cisto dizajna radi
   spatialFrame->setFrameShape(QFrame::StyledPanel);

   //na kraju u nas inputLayout dodajem napravljeni spatialFrame
   inputLayout->addWidget(spatialFrame);




   //Sada pravim novi okvir (Frame) za podatke koji sadrze informacije o granici

   //Ovo je analogno prethodnom
   QFrame * boundFrame = new QFrame;
   QGridLayout * boundLayout = new QGridLayout;
   QLabel * bound = new QLabel(tr("Boundary"));
   boundLayout->addWidget(bound,0,0);

   //QComboBox koristim jer hocu da mogu da izaberem tip granice..dalje se sve slicno formira kao kot prethodnog okvira
   QComboBox * leftCombo = new QComboBox;
   leftCombo->addItem("Dirichlet");
   leftCombo->addItem("Neumann");
   boundLayout->addWidget(leftCombo,3,0);
   _leftLineEdit = new QLineEdit;
   boundLayout->addWidget(_leftLineEdit,4,0);
   QComboBox * rightCombo = new QComboBox;
   rightCombo->addItem("Dirichlet");
   rightCombo->addItem("Neumann");
   boundLayout->addWidget(rightCombo,3,2);
   _rightLineEdit = new QLineEdit;
   boundLayout->addWidget(_rightLineEdit,4,2);

   QComboBox * upCombo = new QComboBox;
   upCombo->addItem("Dirichlet");
   upCombo->addItem("Neumann");
   boundLayout->addWidget(upCombo,1,1);
   _upLineEdit = new QLineEdit;
   boundLayout->addWidget(_upLineEdit,2,1);

   QComboBox * downCombo = new QComboBox;
   downCombo->addItem("Dirichlet");
   downCombo->addItem("Neumann");   
   boundLayout->addWidget(downCombo,5,1);
   _downLineEdit = new QLineEdit;
   boundLayout->addWidget(_downLineEdit,6,1);


   //novi okvir-centralni koji se nalazi izmedju cetiri QComboBox-a
   //on  je prazan i tu je samo estetski
   QFrame * centralFrame = new QFrame;
   centralFrame->setFrameShape(QFrame::StyledPanel);
   //ovo znaci da se taj centralni okvir nalazi na poziciji (3,1) i da je mu je x koordinata dugacka 2 a y 1
   boundLayout->addWidget(centralFrame,3,1,2,1);


   boundFrame->setLayout(boundLayout);
   
   boundFrame->setFrameShape(QFrame::StyledPanel);

   inputLayout->addWidget(boundFrame);


   //Formiram Vertical box koji ce da sadrzi tri okvira (QFrame)

   QVBoxLayout * diffVelLayout=new QVBoxLayout;  //ovde necemo gridlayout

   //prvi okvir...sadrzi jednu labelu (initial) i jedno polje za unos
   QFrame * iniFrame = new QFrame;
   QGridLayout * iniLayout = new QGridLayout;
   QLabel * initial = new QLabel(tr("Initial value"));
   initial->setToolTip("Initial value of mass (energy) concetracion [kg/m^3]");

   iniLayout->addWidget(initial,0,0);
   QLineEdit * initialLineEdit = new QLineEdit;
   iniLayout->addWidget(initialLineEdit,1,0);
   iniFrame->setLayout(iniLayout);
   iniFrame->setFrameShape(QFrame::StyledPanel); 
   diffVelLayout->addWidget(iniFrame);

   //drugi okvir-sadrzi tri labele (velocity, vx i vy) i dva polja za unos
   QFrame * velFrame = new QFrame;
   QGridLayout * velLayout = new QGridLayout;
   QLabel * vel = new QLabel(tr("Velocity"));
   velLayout->addWidget(vel, 0, 0);
   QLabel * vx = new QLabel(tr("Vx"));
    vx->setToolTip("[m/s]");
   velLayout->addWidget(vx, 1, 0);
   QLineEdit * vxLineEdit = new QLineEdit;
   velLayout->addWidget(vxLineEdit, 2, 0);
   QLabel * vy = new QLabel(tr("Vy"));
    vy->setToolTip("[m/s]");
   velLayout->addWidget(vy, 1, 1);
   QLineEdit * vyLineEdit = new QLineEdit;
   velLayout->addWidget(vyLineEdit, 2, 1);

   velFrame->setLayout(velLayout);
   
   velFrame->setFrameShape(QFrame::StyledPanel);

   diffVelLayout->addWidget(velFrame);

   //treci okvir-sadrzi takodje tri labele (diffusivity i Dx i Dy) i dva polja za unos
   QFrame * diffFrame = new QFrame;
   QGridLayout * diffLayout = new QGridLayout;
   QLabel * diff = new QLabel(tr("Diffusivity"));
   diffLayout->addWidget(diff, 0, 0);
   QLabel * Dx = new QLabel(tr("Dx"));
    Dx->setToolTip("first coordinate of mass (termal) diffusivity [m^2/s]");
   diffLayout->addWidget(Dx, 1, 0);
   QLineEdit * dxLineEdit = new QLineEdit;
   diffLayout->addWidget(dxLineEdit, 2, 0);
   QLabel * Dy = new QLabel(tr("Dy"));
   Dy->setToolTip("second coordinate of mass (termal) diffusivity [m^2/s]");

   diffLayout->addWidget(Dy, 1, 1);
   QLineEdit * dyLineEdit = new QLineEdit;
   diffLayout->addWidget(dyLineEdit, 2, 1);

   diffFrame->setLayout(diffLayout);
   
   diffFrame->setFrameShape(QFrame::StyledPanel);

   diffVelLayout->addWidget(diffFrame);

   //dodajem ceo layout u nas inputLayout
   inputLayout->addLayout(diffVelLayout);


   //Novi vertical box koji ce sadrzati jedan okvir za source term i ispod toga dugme calculate
   QVBoxLayout * sourceCalcLayout = new QVBoxLayout;

   //Okvir-sadrzi sledece labele : labelu za naslov-Source
   //xmin, ymin, xmax, ymax, time begin, time end i value kao i njima odgovarajuca polja za unos
   QFrame * sourceFrame = new QFrame;
   QGridLayout * sourceLayout = new QGridLayout;
   QLabel * source = new QLabel(tr("Source"));
   sourceLayout->addWidget(source, 0, 0);
   QLabel * xminS = new QLabel(tr("xmin"));
   xminS->setToolTip("meters [m]");

   sourceLayout->addWidget(xminS, 1, 0);
   QLabel * yminS = new QLabel(tr("ymin"));
    yminS->setToolTip("meters [m]");
   sourceLayout->addWidget(yminS, 1, 1); 
   QLineEdit * xminSLineEdit = new QLineEdit;
   sourceLayout->addWidget(xminSLineEdit, 2, 0);
   QLineEdit * yminSLineEdit = new QLineEdit;
   sourceLayout->addWidget(yminSLineEdit, 2, 1);
   
   QLabel * xmaxS = new QLabel(tr("xmax"));
    xmaxS->setToolTip("meters [m]");
   sourceLayout->addWidget(xmaxS, 3, 0);
   QLabel * ymaxS = new QLabel(tr("ymax"));
    ymaxS->setToolTip("meters [m]");
   sourceLayout->addWidget(ymaxS, 3, 1); 
   QLineEdit * xmaxSLineEdit = new QLineEdit;
   sourceLayout->addWidget(xmaxSLineEdit, 4, 0);
   QLineEdit * ymaxSLineEdit = new QLineEdit;
   sourceLayout->addWidget(ymaxSLineEdit, 4, 1);
   
   QLabel * timeBegin = new QLabel(tr("Time begin"));
   sourceLayout->addWidget(timeBegin, 5, 0);
    timeBegin->setToolTip("source time begin");
   QLineEdit * tminSLineEdit = new QLineEdit;
   sourceLayout->addWidget(tminSLineEdit, 6, 0);
   QLabel * timeEndS = new QLabel(tr("Time end"));
    timeEndS->setToolTip("source time end");
   sourceLayout->addWidget(timeEndS, 5, 1);
   QLineEdit * tmaxSLineEdit = new QLineEdit;
   sourceLayout->addWidget(tmaxSLineEdit, 6, 1);
   QLabel * value = new QLabel(tr("Value"));
    value->setToolTip("source value");
   sourceLayout->addWidget(value, 7, 0);
   QLineEdit * valueLineEdit = new QLineEdit;
   sourceLayout->addWidget(valueLineEdit, 7, 1);

   sourceFrame->setLayout(sourceLayout);
   
   sourceFrame->setFrameShape(QFrame::StyledPanel);

   //dodajem u VBox nas okvir za source
   sourceCalcLayout->addWidget(sourceFrame);

   //Pravim dugme calculate
   QPushButton * calcButton = new QPushButton(tr("Calculate"));

   sourceCalcLayout->addWidget(calcButton);

   inputLayout->addLayout(sourceCalcLayout);



   //setujem ceo inputLayout da bi bilo vidljivo sve sto smo do sada napravili
   setLayout(inputLayout);


   //Sada povezujemo sve odgovarajuce signale i slotove
   //signal textChanged iz xminLineEdit povezujem sa slotom setxmin iz _data
   connect(xminLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setxmin(QString)));
   connect(xmaxLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setxmax(QString)));
   
   connect(yminLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setymin(QString)));
   connect(ymaxLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setymax(QString)));
   
   connect(nxLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setnx(QString)));
   connect(nyLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setny(QString)));
   
   connect(timeEndLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setT(QString)));
   connect(ntLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setnt(QString)));

   connect(initialLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setInitial(QString)));

   connect(vxLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setvx(QString)));
   connect(vyLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setvy(QString)));
   
   connect(dxLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setDx(QString)));
   connect(dyLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setDy(QString)));

   connect(leftCombo, SIGNAL(currentIndexChanged(int)), this,
         SLOT(setBoundL(int)));
   connect(_leftLineEdit, SIGNAL(textChanged(QString)), _data, 
         SLOT(setLeftBValue(QString)));
   connect(rightCombo, SIGNAL(currentIndexChanged(int)), this,
         SLOT(setBoundR(int)));
   connect(_rightLineEdit, SIGNAL(textChanged(QString)), _data, 
         SLOT(setRightBValue(QString)));
   
   connect(downCombo, SIGNAL(currentIndexChanged(int)), this,
         SLOT(setBoundD(int)));
   connect(_downLineEdit, SIGNAL(textChanged(QString)), _data, 
         SLOT(setDownBValue(QString)));
   connect(upCombo, SIGNAL(currentIndexChanged(int)), this,
         SLOT(setBoundU(int)));
   connect(_upLineEdit, SIGNAL(textChanged(QString)), _data, 
         SLOT(setUpBValue(QString)));

   connect(xminSLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setsxmin(QString)));
   connect(xmaxSLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setsxmax(QString)));
   
   connect(yminSLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setsymin(QString)));
   connect(ymaxSLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setsymax(QString)));
   
   connect(tminSLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setstmin(QString)));
   connect(tmaxSLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setstmax(QString)));
   
   connect(valueLineEdit, SIGNAL(textChanged(QString)), _data,
         SLOT(setsvalue(QString)));



   connect(calcButton, SIGNAL(clicked()), this, SLOT(calculate()));


}

//Postavjanje leve granice
void InputData::setBoundL(int i)
{
   if (i==1) //Ako je Nojmanov onda postavi na 0 i onemoguci kliktanje
   {
      _leftLineEdit->setText("0");
      _leftLineEdit->setEnabled(false);
      _data->setgranica(0, false);
      _data->setgranicaVred(0,0.0);
   }else //ako je Dirihleov...
   {
      _leftLineEdit->setEnabled(true);
      _data->setgranica(0, true);
   }

}


//analogno za desnu, gornju i donju granicu
void InputData::setBoundR(int i)
{
   if (i==1)
   {
      _rightLineEdit->setText("0");
      _rightLineEdit->setEnabled(false);
      _data->setgranica(1, false);
      _data->setgranicaVred(1,0.0);
   }else
   {
      _rightLineEdit->setEnabled(true);
      _data->setgranica(1, true);
   }

}

void InputData::setBoundD(int i)
{
   if (i==1)
   {
      _downLineEdit->setText("0");
      _downLineEdit->setEnabled(false);
      _data->setgranica(2, false);
      _data->setgranicaVred(2,0.0);
   }else
   {
      _downLineEdit->setEnabled(true);
      _data->setgranica(2, true);
   }

}

void InputData::setBoundU(int i)
{
   if (i==1)
   {
      _upLineEdit->setText("0");
      _upLineEdit->setEnabled(false);
      _data->setgranica(3, false);
      _data->setgranicaVred(3,0.0);
   }else
   {
      _upLineEdit->setEnabled(true);
      _data->setgranica(3, true);
   }
}

//calculate...

void InputData::calculate()
{
   if(!_data->checkData())
         return;
   //before emit everything in data should be checked
   emit _data->calculate();
}
