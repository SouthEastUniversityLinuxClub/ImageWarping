#include "mainview.h"

MainView::MainView(MainScene *s)
{
    this->scene = s;
    setScene(s);
}

void MainView::mousePressEvent(QMouseEvent *event)
{
    scene->press(event);
}

void MainView::mouseMoveEvent(QMouseEvent *event)
{
    scene->moving(event);
}

void MainView::mouseReleaseEvent(QMouseEvent *event)
{
    scene->release(event);
}
