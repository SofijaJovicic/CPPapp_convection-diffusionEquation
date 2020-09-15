#include "result.h"
#include "data.h"
#include <QProgressDialog>

//Ovo je ona klasa za numeriku
Result::Result(Data * data):_data(data)
{
   _results.resize(0);
}

double Result::izvorPonor(const int i, const int j, const int k)
{//should be set

   if(_data->getxmin()+i*_data->getDeltaX() >= _data->getsxmin() && 
         _data->getxmin()+i*_data->getDeltaX() <= _data->getsxmax() &&
         _data->getymin()+j*_data->getDeltaY() >= _data->getsymin() &&
         _data->getymin()+j*_data->getDeltaY() <= _data->getsymax() &&
         k*_data->getDeltaT() >= _data->getstmin() && 
         k*_data->getDeltaT() <= _data->getstmax())
   {
      return _data->getsvalue();//*deltaT;
   }
   else
   {
      return 0.0;
   }
}

double Result::vrednostGranice(const int i, const int j)
{
	if(i==0)
	{
		if(_data->getgranica(0))
			return _data->getgranicaVred(0);
		else
			return 0.0;
	}
	else if(i==_data->getnx()-1)
	{
		if(_data->getgranica(1))
			return _data->getgranicaVred(1);
		else
			return 0.0;
	}
	else if(j==0)
	{
		if(_data->getgranica(2))
			return _data->getgranicaVred(2);
		else
			return 0.0;
	}
	else if(j==_data->getny()-1)
	{
		if(_data->getgranica(3))
			return _data->getgranicaVred(3);
		else
			return 0.0;
	}
   return 0.0;
}

void Result::dodajGranicuMatrici(Mat & mat)
{
   int centNumb;
   if (_data->getgranica(0))//granica[0] je granica x=xmin tacno je za Dirihleov granicni uslov
   {
      for (int j = 0; j < _data->getny(); j++) {
         centNumb = j * _data->getnx();
         mat.insert(centNumb, centNumb) = 1;
      }
   } else {//Nojmanov
      for (int j = 0; j < _data->getny(); j++) {
         centNumb = j * _data->getnx();
         int poxplus1 = j * _data->getnx() + 1;
         mat.insert(centNumb, centNumb) = 1/_data->getDeltaX();
         mat.insert(centNumb, poxplus1) = -1/_data->getDeltaX();
      }
   }

   if (_data->getgranica(1))//granica[1] je granica x=xmax tacno je za Dirihleov granicni uslov
   {
      for (int j = 0; j < _data->getny(); j++) {
         centNumb = j * _data->getnx();
         mat.insert(centNumb, centNumb) = 1;
      }
   } else {//Nojmanov
      for (int j = 0; j < _data->getny(); j++) {
         centNumb = j * _data->getnx()+ _data->getnx() - 1;
         int poxmin1 = j * _data->getnx() + _data->getnx() - 2;
         mat.insert(centNumb, centNumb) = 1/_data->getDeltaX();//uzima se razlika unazad
         mat.insert(centNumb, poxmin1) = -1/_data->getDeltaX();
      }
   }
   if (_data->getgranica(2))//granica[2] je granica y=ymin tacno je za Dirihleov granicni uslov
   {
      for (int i = 1; i < _data->getnx()-1; i++) {
         //centNumb = i;
         mat.insert(i, i) = 1;
      }
   } else {//Nojmanov
      for (int i = 1; i < _data->getnx()-1; i++) {
         //int centNumb = i;
         int poyplus1 = _data->getnx() + i;
         mat.insert(i, i) = 1/_data->getDeltaY();
         mat.insert(i, poyplus1) = -1/_data->getDeltaX();
      }
   }

   if (_data->getgranica(3))//granica[3] je granica y=ymax tacno je za Dirihleov granicni uslov
   {
      for (int i = 1; i < _data->getnx()-1; i++) {
         centNumb = (_data->getny()-1) * _data->getnx() + i;
         mat.insert(centNumb, centNumb) = 1;
      }
   } else {//Nojmanov
      for (int i = 1; i < _data->getnx()-1; i++) {
         int centNumb = (_data->getny()-1) * _data->getnx() + i;
         int poymin1 = (_data->getny()-2) * _data->getnx() + i;
         mat.insert(centNumb, centNumb) = 1/_data->getDeltaY();
         mat.insert(centNumb, poymin1) = -1/_data->getDeltaY();
      }
   }
}

void Result::kreirajMatricu(Mat & mat)
{
   dodajGranicuMatrici(mat);
   QProgressDialog progress("Creating matrix...", "Cancel", 0, _data->getny());
   progress.setWindowModality(Qt::ApplicationModal);
   progress.setMinimumDuration(0);
   progress.setValue(1);

	for(int j=1;j<_data->getny()-1;j++)
	{
      progress.setValue(j);
		for(int i=1; i<_data->getnx()-1;i++)
		{
			int centNumb=j*_data->getnx()+i;
			int poxplus1=j*_data->getnx()+i+1;
			int poxmin1=j*_data->getnx()+i-1;
			int poyplus1=(j+1)*_data->getnx()+i;
			int poymin1=(j-1)*_data->getnx()+i;
			mat.insert(centNumb,centNumb)=1/_data->getDeltaT()
            + 2*_data->getDx()/(_data->getDeltaX()*_data->getDeltaX()) 
            + 2*_data->getDy()/(_data->getDeltaY()*_data->getDeltaY());
			mat.insert(centNumb, poxmin1)=-_data->getDx()/
            (_data->getDeltaX()*_data->getDeltaX());
			mat.insert(centNumb, poxplus1)=-_data->getDx()/
            (_data->getDeltaX()*_data->getDeltaX());
			mat.insert(centNumb, poymin1)=-_data->getDy()/
            (_data->getDeltaY()*_data->getDeltaY());
			mat.insert(centNumb, poyplus1)=-_data->getDy()/
            (_data->getDeltaY()*_data->getDeltaY());
			if(_data->getvx()/*[centNumb]*/>0.0)
			{
				mat.coeffRef(centNumb,centNumb)+=_data->getvx()/_data->getDeltaX();
				mat.coeffRef(centNumb, poxmin1)-=_data->getvx()/_data->getDeltaX();
			}else{
				mat.coeffRef(centNumb,centNumb)-=_data->getvx()/_data->getDeltaX();
				mat.coeffRef(centNumb, poxplus1)+=_data->getvx()/_data->getDeltaX();
			}
			if(_data->getvy()/*[centNumb]*/>0.0)
			{
				mat.coeffRef(centNumb,centNumb)+=_data->getvy()/_data->getDeltaY();
				mat.coeffRef(centNumb, poymin1)-=_data->getvy()/_data->getDeltaY();
			}else{
				mat.coeffRef(centNumb,centNumb)+=_data->getvy()/_data->getDeltaY();
				mat.coeffRef(centNumb, poyplus1)-=_data->getvy()/_data->getDeltaY();
			}
		}
	}
}

void Result::kreirajDesnuStranu(Eigen::VectorXd & b, Eigen::VectorXd & prethodni, const int k)
{//
	for(int j=0;j<_data->getny();j++)
	{
		for(int i=0; i<_data->getnx();i++)
		{
			int centNumb=j*_data->getnx()+i;
			if(i==0 || j==0 || i==_data->getnx()-1 || j==_data->getny()-1)
				b(centNumb)=vrednostGranice(i,j);
			else
         {
				b(centNumb)=prethodni[centNumb]/_data->getDeltaT() 
               + izvorPonor(i,j,k+1);
            //k+1 jer je shema implicitna
         }
		}
	}
}

QVector<QVector<double> > Result::napraviMatrOdVekt(Eigen::VectorXd & x)
{
   QVector<QVector<double> > matr(_data->getny());
   for(int jy=0;jy<_data->getny();jy++)
   {
      matr[jy].resize(_data->getnx());
      for(int ix=0; ix<_data->getnx(); ix++)
      {
         matr[jy][ix]=x(jy*_data->getnx()+ix);
         if(x(jy*_data->getnx()+ix)>_max)
            _max=x(jy*_data->getnx()+ix);
         if(x(jy*_data->getnx()+ix)<_min)
            _min=x(jy*_data->getnx()+ix);         
      }
   }
   return matr;
}

void Result::napraviBoje()
{
   _col.resize(_data->getnt()+1);
   //,QVector<QVector<int> >(_data->getny(),QVector<int>(_data->getnx())));
   for(int k=0;k<=_data->getnt();k++)
   {
      _col[k].resize(_data->getny());
      for(int j=0;j<_data->getny();j++)
      {
         _col[k][j].resize(_data->getnx());
         for(int i=0;i<_data->getnx();i++)
         {
            _col[k][j][i]=(_results[k][j][i]-_min)*255/(_max-_min);
         }
      }
   }
}

void Result::calculateResults()
{
   QProgressDialog progress("Calculating...", "Cancel", 0, _data->getnt());
   progress.setWindowModality(Qt::ApplicationModal);
   progress.setMinimumDuration(0);

   int dim = _data->getnx()*_data->getny();
   Mat mat(dim,dim);
	Eigen::VectorXd x(dim), b(dim), pocetni(dim);
   _results.resize(_data->getnt()+1);

   kreirajMatricu(mat);
	pocetni = Eigen::ArrayXd::Constant(dim, _data->getInitial());
   _results[0]=napraviMatrOdVekt(pocetni);
   x=pocetni;
   Eigen::BiCGSTAB<Mat> solver;
	solver.compute(mat);
  /* for(size_t i=0;i<dim;i++)
   {
      qDebug()<<i;
      for(size_t j=0;j<dim;j++)
         qDebug()<<" "<<mat(i,j);
      qDebug()<<"\n";
   }*/
 
   for(int k=0; k<_data->getnt(); k++)
   {
      kreirajDesnuStranu(b, x, k);
      x = solver.solve(b);
      _results[k+1]=napraviMatrOdVekt(x);
      progress.setValue(k+1);
   }
   napraviBoje();

}
