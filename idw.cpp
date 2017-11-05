#include "idw.h"

IDW::IDW()
{

}

IDW::IDW(const QVector<QPoint> &p, const QVector<QPoint> &q)
{
    mu = 2.0;
    p_points = p;
    q_points = q;
}

QPoint IDW::f(QPoint p)
{
    QPoint result = QPoint(0,0);
    double x=0,y=0;

    for(long i=0;i<p_points.size();i++)
    {
        x += f_i(p,i).x() * w_i(p,i);
        y += f_i(p,i).y() * w_i(p,i);
    }

    result.setX(x);
    result.setY(y);

    return result;
}

double IDW::w_i(QPoint p, int i)
{
    double sum = 0;

    if(p==p_points.at(i))
        return 1;

    for(long j=0; j<p_points.size(); j++)
        sum += delta(p,p_points.at(j));

    return delta(p,p_points.at(i))/sum;


}

QPoint IDW::f_i(QPoint p, int i)
{
    QPoint result = q_points.at(i);

    result.rx() += p.x() - p_points.at(i).x();
    result.ry() += p.y() - p_points.at(i).y();

    return result;
}

double IDW::delta(QPoint p, QPoint p_i)
{
    return pow(1.0/d(p,p_i),mu);
}

double IDW::d(QPoint p, QPoint p_i)
{
    return sqrt(pow(p.x()-p_i.x(),2.0) + pow(p.y()-p_i.y(),2.0) );
}
