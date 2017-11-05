#ifndef IDW_H
#define IDW_H
#include <QVector>
#include <QPoint>
#include <QtMath>

class IDW
{
public:
    IDW();
    IDW(const QVector<QPoint> &p,const QVector<QPoint> &q);
    QPoint f(QPoint p);

private:
    double w_i(QPoint p, int i);
    QPoint f_i(QPoint p, int i);
    double delta(QPoint p, QPoint p_i);
    double d(QPoint p, QPoint p_i);

    double mu;
    QVector<QPoint> p_points, q_points;
};

#endif // IDW_H
