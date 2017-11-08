#include "rbf.h"

RBF::RBF()
{

}

RBF::RBF(const QVector<QPoint> &s, const QVector<QPoint> &e)
{
    this->startPoints = s;
    this->endPoints = e;
    this->u = -1.0;
    GetDiPj();
    GetRi();
    GetXY();
}

void RBF::GetDiPj()
{
    dipj = QVector<QVector<double>>();
    for(int i=0; i < startPoints.size(); i++)
    {
        QVector<double> dp = QVector<double>();
        for(int j = 0; j < startPoints.size(); j++)
        {
            dp.push_back( (startPoints.at(i).x() - startPoints.at(j).x())*(startPoints.at(i).x() - startPoints.at(j).x())
                       +  (startPoints.at(i).y() - startPoints.at(j).y())*(startPoints.at(i).y() - startPoints.at(j).y()) );
        }
        dipj.push_back(dp);
    }
}

void RBF::GetRi()
{
    ri = QVector<double>();
    ri.push_back(dipj.at(0).at(1));
    for(int j = 1; j < startPoints.size() ; j++)
    {
        if(dipj.at(0).at(j) < ri.at(0))
        {
            ri.replace(0,dipj.at(0).at(j));
        }
    }
    for( int i= 1 ; i < startPoints.size() ; i++)
    {
        ri.push_back(dipj.at(i).at(0));
        for(int j = 1 ; j<startPoints.size() ; j++)
        {
            if(dipj.at(i).at(j) < ri.at(i) && i != j)
                ri.replace(i,dipj.at(i).at(j));
        }
    }
    for( int i= 0 ; i < startPoints.size() ; i++)
    {
        for(int j = 0 ; j<startPoints.size() ; j++)
        {
            double temp = pow(dipj.at(i).at(j) + ri.at(j) , u) ;
            dipj[i].replace(j,temp);
        }
    }
}

void RBF::GetXY()
{
    x = QVector<double>();
    y = QVector<double>();
    for(int i=0; i<startPoints.size(); i++)
    {
        x.push_back(endPoints.at(i).x() - startPoints.at(i).x());
        y.push_back(endPoints.at(i).y() - startPoints.at(i).y());
    }
    x = Gauss(dipj,x);
    y = Gauss(dipj,y);
}

QVector<double> RBF::Gauss(QVector<QVector<double>> A, QVector<double> d)
{
    QVector<QVector<double>> B = QVector<QVector<double>>();

    for (int i=0; i < A.size() ; i++)
    {
        QVector<double> temp = QVector<double>();
        for(int j =0; j<A.at(i).size() ; j++)
        {
            temp.push_back(A.at(i).at(j));
        }
        B.push_back(temp);
    }

    for (int k = 0; k< d.size()-1; k++)
    {
        if(B.at(k).at(k) == 0)
        {
            return d;
        }
        else
        {
            for(int i=k+1 ; i<d.size() ; i++)
            {
//                B[i].replace(k, B.at(i).at(k) / B.at(k).at(k));
                B[i][k] = B[i][k] / B[k][k];
                for(int j = k+1 ; j<d.size(); j++)
                {
//                    d.replace(i, d.at(i) - d.at(k)*B.at(i).at(k));
                    d[i] = d[i] - d[k] * B[i][k];
//                    B[i].replace(j , B.at(i).at(j) - B.at(k).at(j)*B.at(i).at(k));
                    B[i][j] = B[i][j] - B[k][j] * B[i][k];
                }
            }
        }
    }

    if(B.at(d.size()-1).at(d.size()-1) == 0)
        return d;

    d.replace(d.size()-1, d.at(d.size()-1) / B.at(d.size()-1).at(d.size()-1));
    double sum = 0;
    for(int k =d.size()-2 ; k>=0 ; k--)
    {
        sum = 0;
        for(int i=k+1;i<d.size() ; i++)
        {
            sum += B.at(k).at(i) * d.at(i);
        }
        d.replace(k, ( d.at(k)-sum ) / B.at(k).at(k));
    }
    return d;
}

QPoint RBF::F(QPoint p)
{
    QVector<double> dp = QVector<double>();
    for(int k = 0;k<startPoints.size();k++)
    {
        dp.push_back(pow((p.x() - startPoints.at(k).x()),2) + pow((p.y() - startPoints.at(k).y()),2));
    }
    double mx1 = 0,my1 = 0;
    for(int i =0;i<startPoints.size();i++)
    {
        mx1 += x.at(i) * pow((dp.at(i)*dp.at(i) + ri.at(i)*ri.at(i)),u/2.0);
        my1 += y.at(i) * pow((dp.at(i)*dp.at(i) + ri.at(i)*ri.at(i)),u/2.0);
    }
    mx1 += p.x();
    my1 += p.y();
    long x1 = mx1 + 0.5;
    long y1 = my1 + 0.5;
    QPoint result = QPoint();
    result.rx() = x1 > INT32_MAX ? INT32_MAX : x1;
    result.ry() = y1 > INT32_MAX ? INT32_MAX : y1;
    return result;
}
