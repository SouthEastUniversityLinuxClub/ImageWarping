#ifndef RBF_H
#define RBF_H
#include <QVector>
#include <QPoint>
#include <QtMath>

class RBF
{
public:
    RBF();
    RBF(const QVector<QPoint> &s, const QVector<QPoint> &e);
    QPoint F(QPoint p);
private:
    QVector<QPoint> startPoints,endPoints;
    QVector<double> ri,x,y;
    QVector<QVector<double>> dipj;
    double u;

    void GetDiPj();
    void GetRi();
    void GetXY();
    QVector<double> Gauss(QVector<QVector<double>> A , QVector<double> d);
};

#endif // RBF_H
