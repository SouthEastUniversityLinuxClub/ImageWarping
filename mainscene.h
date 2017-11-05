#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QGraphicsScene>
#include <QVector>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QFileDialog>
#include <QGraphicsItemGroup>
#include <QMessageBox>
#include "idw.h"

class MainScene : public QGraphicsScene
{
public:
    MainScene();
    void press(QMouseEvent* event);//鼠标点击处理函数
    void moving(QMouseEvent* event);//鼠标移动处理函数
    void release(QMouseEvent* event);//鼠标释放处理函数

    void open();
    void save();
    void invert();
    void grayscale();
    void restore();
    void mirrorH();
    void mirrorV();
    void deleteALL();
    void idwFunc();


    QPoint start,end;
    QVector<QPoint> starts,ends;
    QVector<QGraphicsItem*> items;//装有父类指针的QVector，指向的是不同的子类对象。
    QGraphicsPixmapItem* pixmapItem;
    QImage image;
    QGraphicsItemGroup* group;
    QString path;
    IDW idw;
    bool editable;
};

#endif // MAINSCENE_H
