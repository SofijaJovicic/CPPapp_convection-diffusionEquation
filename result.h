#ifndef RESULT_H
#define RESULT_H
#include <QVector>
#include <QWidget>
#include "/usr/include/eigen3/Eigen/Sparse"



class Data;

//klasa rezultata
class Result : public QWidget
{
   Q_OBJECT
    //matrica iz eigen biblioteke
   typedef Eigen::SparseMatrix<double> Mat;
   public:
    //konstruktor
      Result(Data * data);
      //metod koji racuna rezultat
      void calculateResults();

      QVector<QVector<double> > getResultsTime(const int i) const
      {return _results[i];}
      int getColor(const int i, const int j, const int k) const
      {return _col[k][j][i];}
      double minRes() const {return _min;}
      double maxRes() const {return _max;}

   private:
      //term izvora i ponora
      double izvorPonor(const int i, const int j, const int k);
      //vrednosti granice
      double vrednostGranice(const int i, const int j);

      void dodajGranicuMatrici(Mat & mat);
      //kreiranje matrice
      void kreirajMatricu(Mat & mat);
      //kreiranje desne strane sistema
      void kreirajDesnuStranu(Eigen::VectorXd & b, Eigen::VectorXd & prethodni,
            const int k);
      void napraviBoje();

      QVector<QVector<double> > napraviMatrOdVekt(Eigen::VectorXd & x);

      Data * _data;

      QVector<QVector<QVector<double> > > _results;
      QVector<QVector<QVector<int> > > _col;
      double _max=std::numeric_limits<double>::min();
      double _min=std::numeric_limits<double>::max();
};


#endif
